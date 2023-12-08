#include "STM32F4xx_intmash_MBfilesCommands.h"
#include "Intmash_bastypes.h"
#include "crc16.h"


/*
���� ��� ������ � ����������� mdll � sd ������ ����� ������ � adjaster_mdll
������������ ����� ����������� � ������� mdll � �������� ������� ������� ������ � sd ������
� main ���������� ������ FilesOperateProc(). ����� ����������� ���������, 
��� � ����� ������� � command_decod ���������:
switch (cmd){
	case ....//���� �������

        case 0x20://������ ������� ����� � ���������� �����
        case 0x21://��������� ������ ������ � �������� ��������
        case 0x22://��������� ����
        case 0x23://��������� ���� � ��������� ������
        case 0x24://������� ���� � ��������� ������
        case 0x25://������� ���� � ��������� ������ ��� ����������
        case 0x26://�������� ��� ��������� ���������������� ����                       
*/

bool FindFileFirst(FILINFO *fno, DIR *dir);
bool FindFileNext(FILINFO *fno, DIR *dir);

#define CRC_SIZE 2 //������ crc-2 �����
#define MB_HEAD_SIZE 2 //������ ��������� ������
#define DISK_ERROR 0x80 //������ ����� - ����������� ��� �� ���������������
#define FILE_ERROR 0xC0 //������ ����� - �����������, �� ������� �������
#define FAT_ERROR 0xC0 //������ �������� �������
#define FIND_NEXT_FILE 0xFF //�����  ������ ���������� �����, � �� ������ ������� �� SD 

//��������� �� ��������� ��� ������ � �������
FileOperationsStructType* CurrentFileOperationsStruct;


//������� ������ ������� ����� �� SD �����
bool FindFileFirst(FILINFO *fno, DIR *dir){
  FRESULT res;
  bool r = FALSE;
    if (FSReady == FAT_READY) //�������� ������� ������, ����� ��������
    {      
      res = f_opendir(dir, "0:"); //������� ������ ������
      if (res == FR_OK) //�������� ������� ������
      {
        res=f_readdir(dir, fno);
        if (res == FR_OK) r = TRUE; //��� ����� ��������
      }
    }
   return (r);
}
//������� ������ ���������� ����� �� SD �����
bool FindFileNext(FILINFO *fno, DIR *dir){
  FRESULT res;
  bool r = FALSE;
    if (FSReady == FAT_READY) //�������� ������� ������, ����� ��������
    {
      res=f_readdir(dir, fno);
      if (res == FR_OK) r = TRUE; //��� ����� ��������
    }
   return (r);
}

/*
  0x20 ������ ������� ����� � ���������� �����
  ������ 01.20.�RC
  ����� 01.20.SSSSSSSS.FFFFFFFF.CRC
  SSSSSSSS - ����� ������� �����
  FFFFFFFF - ��������� ������������ �� �����
  ������
  0x20 | 0x00 = 0010.0000 - �� �������
  0x20 | 0x80 = 1010.0000 - ���� �� ��������������� ��� �����������
  0x20 | 0xC0 = 1110.0000 - ������ �������� ������� ��� ����������� ������� �����
*/
tU8 ModbusGetDiskSpace(ModbusSlaveType* Slave)
{
  tU32Union fre_clust; //���������� ��������� ��������� �� �����
  tU32Union fre_sect; //������ ��������� ������� ����� � ��
  tU32Union tot_sect; //����� ������ ����� � ��
  tU8 DataLength = MB_HEAD_SIZE; //������ ������������ �������
      
  if (FSReady == FAT_READY) //���� �������� ������� ������, ����� �������� ������ �����
  {
    if (f_getfree("/", (DWORD*)&fre_clust.I, &pFS) == 0)
    { 
      //������ ����� �����������
      tot_sect.I = ((pFS->n_fatent - 2) * pFS->csize) >> 1; //fs->
      fre_sect.I = (fre_clust.I * pFS->csize) >> 1; //fs->
      
      //����� ������� �����
      Slave->Buffer[2] = tot_sect.B[3];//Size[0]
      Slave->Buffer[3] = tot_sect.B[2];//Size[1]
      Slave->Buffer[4] = tot_sect.B[1];//Size[2]
      Slave->Buffer[5] = tot_sect.B[0];//Size[3]
      //��������� ������������ �� �����
      Slave->Buffer[6] = fre_sect.B[3];//Free[0]
      Slave->Buffer[7] = fre_sect.B[2];//Free[1]
      Slave->Buffer[8] = fre_sect.B[1];//Free[2]
      Slave->Buffer[9] = fre_sect.B[0];//Free[3]
      DataLength +=8; //����� �������

    } 
    else Slave->Buffer[1] |= FAT_ERROR; //cmd (20) + error code //������ �������� ������� ��� ����������� ������� �����
  }
  else Slave->Buffer[1] |= DISK_ERROR; //cmd (20) + error code //�������� ������� �� ������
  
  DataLength += CRC_SIZE;//��������� ����� crc
  FrameEndCrc16((tU8*)Slave->Buffer, DataLength);
  return DataLength;

}

/*
  0x21 ��������� ������ ������ � �������� �������� (����������� �� �������������)
  ������ 01.21.00.�RC
    01-�����
    21-�������
    00-����� (00-�������� ������� ������ - ����� �������� ������������ �  �������/ FF-�������� ��� ���������� �����)
  ����� 01.21.CN.FILE.CRC
    �N - ���-�� ���� � ����� �����
    FILE - ��� ����� � ������� 8.3(������ ���� filename.rec)
  ������/���������
  0x21 | 0x00 = 0010.0001 - �� �������
  0x21 | 0x80 = 1010.0001 - ���� �� ��������������� ��� �����������
  CN=0 - � ���������� ������ �������� ��� ���������� � ������ �����
*/
tU8 ModbusGetFilesList(ModbusSlaveType* Slave)
{
  tU8 DataLength = MB_HEAD_SIZE; //������ ������������ ������� - ����� ��������� ����+�������
  tU8 NextFile = Slave->Buffer[2]; //00 - ���� ������������� � ������� 0xff - �������� ��������� ����
  bool ValidFile = FALSE; //true - ��� ���� �����, false - ������ ��� ������
  tU8 FnameSize = 0;
  
  if (FSReady == FAT_READY) //���� �������� ������� ������, ����� ��������
  {        
    if (NextFile == FIND_NEXT_FILE)  ValidFile = FindFileNext(&CurrentFileOperationsStruct->fno, &CurrentFileOperationsStruct->dir); //Options = 0x0FF �������� ��������� ����
    else  ValidFile = FindFileFirst(&CurrentFileOperationsStruct->fno, &CurrentFileOperationsStruct->dir);//Options = 0x00 �������� ������� ������ (����� �������� ������������ �  �������)
    if (ValidFile) //��� ������� ����� ��������
    {
      Slave->Buffer[2] = FnameSize = strlen(CurrentFileOperationsStruct->fno.fname);//���-�� �������� � �������� �����
      //������� �������� ����� � ������ �����
      
      for(tU8 i=0; i< FnameSize; i++)
      {
        Slave->Buffer[3+i] = CurrentFileOperationsStruct->fno.fname[i];
      }
    }
    else Slave->Buffer[2] = 0; //��� ����� �� �������� - ������ ������ ���
    DataLength += FnameSize + 1; //���� ������� ������� ��������, �� ��� ������ ������ - CN=0, FnameSize = 0
  }
  else Slave->Buffer[1] |= DISK_ERROR; //cmd (21) + error code //�������� ������� �� ������

  DataLength += CRC_SIZE;//��������� ����� crc
  FrameEndCrc16((tU8*)Slave->Buffer, DataLength);
  return DataLength;

}

/*
  0x22 ��������� ����
  ������ 01.22.OFFSETxx.FILE.CRC
    01-�����
    22-�������
    OFFSETxx - 4����� - �������� � ����� (seek) �������� ������� �� 128 ����
    CN - ����� ����� �����
    FILE - ��� ����� � ������� 8.3(������ ���� filename.rec)
  ����� 01.22.CN.DATA[CN].CRC
    �N - ���-�� ������������ ���� (���� ���� ������  ����, �� CN ��������� ������ �����. ���� ����������� ����� �� ������ 128����, �� ��������� �����, ���� ����� ������ 128 ����)
    DATA[CN] - ������ ������ ������������ CN
  ������/���������
  0x22 | 0x00 = 0010.0010 - �� �������
  0x22 | 0x80 = 1010.0010 - ���� �� ��������������� ��� �����������
  CN=0 - ���� ��������!
  �N<128 - �������� ��������� ����
*/
tU8 ModbusReadFile(ModbusSlaveType* Slave)
{    
  volatile FRESULT res;
  volatile UINT  ByteRead;   // ���-�� ����������� ���� �� �����
  volatile tU32Union offs; //�������� � �����
  tU8 DataLength = MB_HEAD_SIZE; //������ ������������ ������� - ����� ��������� 
   
  if (FSReady == FAT_READY) //�������� ������� ������, ����� ��������
  { 
    res = f_open(&CurrentFileOperationsStruct->f, (char const*)&Slave->Buffer[6], FA_OPEN_EXISTING |FA_READ);// Open an existing file
    if (res == FR_OK) //���� ������ � ������ �� ������
    {     
      //���������� ��������, ������� ������ ���� �� ����� ������� �����
      offs.B[0] = Slave->Buffer[2];
      offs.B[1] = Slave->Buffer[3];
      offs.B[2] = Slave->Buffer[4];
      offs.B[3] = Slave->Buffer[5];
      if (offs.I >= f_size(&CurrentFileOperationsStruct->f)) //���� ��������� �������� ������ ��� ������ �����
      {       
        Slave->Buffer[2] = 0;//CN = 0 //����� ��������, ��� ���� ��������
        DataLength += 1; // ������ ������ 01.22.CN.CRC
      }
      else //���, �������� ������������
      {    
        res = f_lseek(&CurrentFileOperationsStruct->f, offs.I);       
        //������ ��� ����� ���������. ������ ������ 01.22.CN.DATA[CN].CRC
        res = f_read(&CurrentFileOperationsStruct->f, &Slave->Buffer[3], 230, (UINT *)&ByteRead);          
        if (res == FR_OK) //���-�� ����������� � �� �����
        {
          //���������� ����������� ������ ���������� � br      
          Slave->Buffer[2] = ByteRead;//������ ���-�� ������������ ����
          //��������� ����� ��� �������� �������
          DataLength += 1 + ByteRead;
          //����� 
        }
        else Slave->Buffer[1] |= DISK_ERROR; //cmd (22) + error code //������ ����������� �������� // ������ ������ 01.22|0x80.CRC
      }     
      f_close(&CurrentFileOperationsStruct->f);// Close open files
    }
    else Slave->Buffer[1] |= DISK_ERROR; //cmd (24) + error code //�� ������ �������/�������� ������ ����
  }
  else Slave->Buffer[1] |= DISK_ERROR; //cmd (24) + error code //�������� ������� �� ������

  DataLength += CRC_SIZE;//��������� ����� crc
  FrameEndCrc16((tU8*)Slave->Buffer, DataLength);
  return DataLength;
 
}


/*
  0x23 �������� ���� (�� microSD ����� ���������)
  ������ 01.23.OFFSETxx.FILE#0.CN.DATA[CN].CRC
    01-�����
    23-�������
    OFFSETxx - 4����� - �������� � ����� (seek) ���� ������������ ������� �� ������� (����� ����� ������ � CN)
    FILE# - ��� ����� � ������� 8.3("0-������������" ������ ���� filename.rec)
    CN - ���-�� ������������ ���� � �����. CN - ��� �������� �����, ������ ����� ������������ ��������, 
         ��� ������� ����� ����� ������� �� ��������� 255���� (������ �� ������ ���� � ������ ����� �����, 230 ���� ������������ ����� ������������).
	!���� ������ CN = 0 - ��������� ������� ����! (������� ����� �����)
  ����� 01.23.CN.CRC
    �N - ���-�� �������� ����
  ������/���������
  0x23 | 0x00 = 0010.0011 - �� �������
  0x23 | 0x80 = 1010.0011 - ���� �� ��������������� ��� �����������
  0x23 | 0x�0 = 1110.0011 - ���� �� ������ (�� ������� �������)
  CN=0 - ���� ������� ��������� � ������!
*/
tU8 ModbusWriteFile(ModbusSlaveType* Slave)
{   
  tU8 shift = 0; //����� ��� ������ ������ ������ �����
  volatile FRESULT res;
  tU8 DataLength = MB_HEAD_SIZE; //������ ������������ ������� - ����� ��������� ����+�������
  volatile UINT  ByteWrite;     // ���-�� ���������� ���� �� �����
  volatile tU32Union offs; //�������� � �����
  bool try_trunc = FALSE;//���� ����� lseek ���� ����� ������ ��� ���� � ��, ������� ���� �� ��������������� �������
 
  if (FSReady == FAT_READY) //�������� �������  ������
  {
    res = f_open(&CurrentFileOperationsStruct->f, (char const*)&Slave->Buffer[6], FA_OPEN_ALWAYS |FA_WRITE);
    if (res == FR_OK) 
    {
      //���� ������ (��� ������) � ������ �� ������
      //���������� ��������, ������� ������ ���� �� ����� ������� �����
      offs.B[0] = Slave->Buffer[2];
      offs.B[1] = Slave->Buffer[3];
      offs.B[2] = Slave->Buffer[4];
      offs.B[3] = Slave->Buffer[5];

      res = f_lseek(&CurrentFileOperationsStruct->f, f_size(&CurrentFileOperationsStruct->f)); //�������� �������� �����
      //���� �������� ������ ������� �����, (�������� ��� ������ � ��������� ������� �����)
      //�� ���������� ��������� � ����� ����� lseek
      if (offs.I < f_size(&CurrentFileOperationsStruct->f)) 
      {
        res = f_lseek(&CurrentFileOperationsStruct->f, offs.I);//��������� ����������
        try_trunc = TRUE;//�� ������� ������ ������� ��� ������� ��������� (��� trucat)
      }
      shift = strlen((char const*)&Slave->Buffer[6]);//������� ����� ����� �����
      shift +=7;
      //������ ��� ����� ��������. ������ 01.23.OFFSETxx.FILE#0.CN.DATA[CN].CRC
      //��������� ������� �� �N ����
      res = f_write(&CurrentFileOperationsStruct->f, &Slave->Buffer[shift+1], Slave->Buffer[shift], (UINT *)&ByteWrite);
      if (try_trunc)//�������� �������������� �������
      {
        res = f_truncate(&CurrentFileOperationsStruct->f); 
      }      
      if (res == FR_OK) //���-�� ���������� � �� �����
      {
        //���������� ���������� ������ ���������� � br
        Slave->Buffer[2] = ByteWrite;//������ ���-�� ���������� ����
        //��������� ����� ��� �������� �������
        DataLength +=1;
      }
      else Slave->Buffer[1] |= DISK_ERROR; //cmd (23) + error code //������ ����������� ��������
      
      f_close(&CurrentFileOperationsStruct->f);// Close open files
    }
    else Slave->Buffer[1] |= FILE_ERROR; //cmd (23) + error code //���� �� ������� �������/��������
  }
  else Slave->Buffer[1] |= DISK_ERROR; //cmd (24) + error code//�������� ������� �� ������

  DataLength += CRC_SIZE;//��������� ����� crc
  FrameEndCrc16((tU8*)Slave->Buffer, DataLength);
  return DataLength;

}


/*
  0x24 ������� ���� � ��������� ������
  ������ 01.24.CN.FILE.CRC
    01-�����
    24-�������
    �N - ���-�� ���� � ����� �����
    FILE - ��� ����� � ������� 8.3(������ ���� filename.rec)
  ����� 01.24|EC.CRC
    ������/��������� (EC - ErrorCode)
    0x24 | 0x00 = 0010.0011 - ���� �����
    0x24 | 0x80 = 1010.0011 - ���� �� ��������������� ��� �����������
    0x24 | 0x�0 = 1110.0011 - ���� �����������
*/
tU8 ModbusRemoveFile(ModbusSlaveType* Slave)
{ 
  FRESULT res;
  tU8 CN=0;
  tU8 DataLength = MB_HEAD_SIZE; //������ ������������ ������� - ����� ��������� ����+�������

  if (FSReady == FAT_READY) //�������� ������� ������, ����� ��������
  {
    //1) ������������ "0-������������ ������"
    CN = Slave->Buffer[2];
    Slave->Buffer[3+CN] = 0;
    res = f_unlink ((char const*)&Slave->Buffer[3]);// Delete an existing file or directory
    if (res == FR_NO_FILE) Slave->Buffer[1] |= FILE_ERROR; //cmd (24) + error code //���� �����������   
  }
  else Slave->Buffer[1] |= DISK_ERROR; //cmd (24) + error code //�������� ������� �� ������

  DataLength += CRC_SIZE;//��������� ����� crc
  FrameEndCrc16((tU8*)Slave->Buffer, DataLength);
  return DataLength;

}







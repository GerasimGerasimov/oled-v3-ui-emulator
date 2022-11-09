#include "PageEditValue.h"
#include "Router.h"
#include <IniResources.h>
#include <crc16.h>

void TPageEditValue::view() {
    MainMenu->view();
};

void TPageEditValue::clear() {
}

void TPageEditValue::onOpen() {
    p = (TParameter*)IniResources::getSignalByTag(TRouter::PageValueEditEntryData.tag);
    pHeader->setCaption(p->getName());
    pEdit->setCaption(TRouter::PageValueEditEntryData.value);
    tag = TRouter::PageValueEditEntryData.tag;
}

bool TPageEditValue::ProcessMessage(TMessage* m) {
    for (auto& element : List) {
       element->ProcessMessage(m);
    }

    switch (m->Event) {
        case (u32)EventSrc::KEYBOARD: {
            switch (m->p1) {
                case (u32)KeyCodes::ESC:
                    TRouter::goBack();
                    return true;
                case (u32)KeyCodes::ENT:
                    sendValue();
                    TRouter::goBack();
                    return true;
                }
        }
    }
    return false;
};

std::string NetWorkAddrToHex(u16 nwa) {
    char s[4];
    sprintf(s, "%.2X", nwa);
    std::string res(s);
    return res;
}

typedef struct {
    const std::string& Cmd;
    const std::string& DevAddr;
    const std::string& RegAddr;
    const std::string& Value;
} TWriteCmdSrc;

/*
AD, C, №R(h, l), CW(h, l), CntBytes, Data[0](h, l)..Data[CW](h, l), CRC(h, l)
│   │  │         │          │        │             │                └─(word)crc16
│   │  │         │          │        └─────────────┴─(word)Записываемые данные
│   │  │         │          └─(byte)Кол - во передаваемых байт
│   │  │         └─(word)Кол - во регистров к передаче
│   │  └─(word)Начальный адрес
│   └────(byte)Команда(10h)
└──────(byte)Адрес устройства
*/

std::string get0x10WriteRegCmd(TWriteCmdSrc& Src) {
    u8 a[13];
    a[0] = (u8)std::stoi(Src.DevAddr);
    a[1] = 0x10;
    //начальный адрес регистра
    u16 addr = std::stoul(Src.RegAddr, nullptr, 16);
    a[2] = (u8)(addr & 0xFF00) >> 8;
    a[3] = (u8)(addr & 0x00FF);
    //кол-во передаваемых регистров
    u8 regscnt = Src.Value.size() / 4;
    a[4] = (u8)(regscnt & 0xFF00) >> 8;
    a[5] = (u8)(regscnt & 0x00FF);
    a[6] = (u8)(regscnt * 2);//кол-во передаваемых байт
    //данные
    u32 value = std::stol(Src.Value, nullptr, 16);
    (regscnt == 1)
        ? ( a[7] = (value & 0xFF00) >> 8,
            a[8] = (value & 0x00FF) >> 0)
        : ( a[7] = (value & 0xFF000000) >> 24,
            a[8] = (value & 0x00FF0000) >> 16,
            a[9] = (value & 0x0000FF00) >> 8,
            a[10]= (value & 0x000000FF) >> 0);
    //контрольная сумма 
    FrameEndCrc16(a, (regscnt == 1)? 11 : 13);
    /*TODO вернуть подготовленный массив*/
    return "Write Multiple Registers";
}

static const std::map<std::string, std::function<std::string(TWriteCmdSrc&)>> WriteCmdVariants = {
    {"10", [](TWriteCmdSrc& props) {return get0x10WriteRegCmd(props); }},
    {"16", [](TWriteCmdSrc& props) {return " Mask Write Register"; }},
};

std::string CreateWriteCmd(TWriteCmdSrc CmdSrc) {
    std::string res = (WriteCmdVariants.count(CmdSrc.Cmd))
        ? WriteCmdVariants.at(CmdSrc.Cmd)(CmdSrc)
        : "Unknown Reg Write Command";
    return res;
}

void TPageEditValue::sendValue(void) {
    u8 cmd[11];
    std::string value = pEdit->getValue();
    std::string ValueHex = p->getValueHex(value);//получил значение в хексах и сразу длину (так как строка)
    std::string RegHexAddr = p->getRegHexAddr();//получил номер регистра в хексах
    /*getWriteCmdType узнаю какой командой отправлять данные
        Write Multiple Registers - 0х10
        Mask Write Register - 0x16 для манипуляций с битами и байтами*/
    const std::string Cmd = p->getWriteCmdType();
    /*по Tag надо узнаю на какой Адрес отправлять
    "DEVICES":"U1/", есть список устройств, надо сопостоавить из тега U1
        "U1":"DEV1/COM1/1 а из U1 найти адрес (он за COM1/)
    */
    const u16 DevAddr = IniResources::getDevNetWorkAddrByTag(tag);
    const std::string DevAddrHex = NetWorkAddrToHex(DevAddr);
    CreateWriteCmd({ Cmd, DevAddrHex, RegHexAddr, ValueHex });
    /*TODO выяснить в какой командный слот писать полученную команду*/
    /*TODO полученный массив положить в OUT командного слота*/
    /*TODO активировать слот на передачу и показывать анимацию до завершения записи*/
    /*TODO если запись успешна - показать анимаци успешной записаи, если нет соотв неуспешной*/
}

TPageEditValue::TPageEditValue(std::string Name)
/*TODO в этом окне
1) Способ редактирования зависит от типа параметра:
1.1) TBit может принимать начение только "0"/"1"
1.2) TIPAddr нужно уметь перемещаться между байтами и менять каждый из нх
1.3) TPrmList - собственно выбор из списка значений

1) должен быть заголовок с названием параметра (есть)
2) поле с описанием (в самом низу)
3) текущее значение (TODO с учётом формата, который как-то надо передать) + единицы измерения (если есть)
4) новое значение которое отредактировал юзер (желательно более крупным шрифтом)
Варианты релактировония:
5) Старый: есть шаг изменения: это "1", которая:
    - уменьшается в 10 раз при каждом нажатии "ВЛЕВО"
    - увеличивается в 10 раз при каждом нажатии "ВПРАВО"
    - значение увеличивается на шаг изменения при нажатии "ВВЕРХ"
    - значение уменьшается на шаг изменения при нажатии "ВНИЗ"
    TODO предусмотреть автоматическое повторное действие по таймеру, при длительном ужержании кнопок "ВВЕРХ/ВНИЗ"
6) Новый:
    - перемещениями "ВЛЕВО/ВПРАВО" перемещаюсь в разряд числа который надо установить, если разряда нет, то он создатся
      ___.____ крайние разряды в значении НОЛЬ удаляются как только с них уходит курсор
        - в сторону меньшего разряда для целой части числа
        - в сторону большего разряда для дробной части числа
    Нули появляются в пустых местах при продвижении курсора, соотв-но есди юзер не постааит
    значащее значение то все нули обнулятся
*/
    :TPage(Name)
    , p(NULL) {
    TLabelInitStructure LabelInit;
    LabelInit.style = (LabelsStyle)((u32)LabelsStyle::WIDTH_FIXED | (u32)LabelsStyle::TEXT_ALIGN_CENTER);
    LabelInit.Rect = { 10, 10, 10, VIEW_PORT_MAX_WIDTH };
    LabelInit.focused = false;

    LabelInit.caption = "---";
    pHeader = new THeaderLabel(LabelInit);

    LabelInit.focused = true;
    pEdit = new TNumericEdit(LabelInit);

    MainMenu = new TComponentListVertical({ pHeader, pEdit });

    AddList({ MainMenu });
};

TPageEditValue::~TPageEditValue() {
};

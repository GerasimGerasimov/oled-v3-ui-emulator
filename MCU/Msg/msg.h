//служба сообщений
#ifndef MSG_H
#define MSG_H

#include "stm32f4xx.h"

//defines
#define MAXMESSAGE  0xFFFF
#define LBCLICK     MAXMESSAGE
#define LBDOWN      MAXMESSAGE-1
#define LBUP        MAXMESSAGE-2
#define MDRAG       MAXMESSAGE-3
#define MMOVE       MAXMESSAGE-4
#define TICK        MAXMESSAGE-5
#define CHANGE      MAXMESSAGE-6
#define MENUCLOSE   MAXMESSAGE-7
#define BUTTONCLICK MAXMESSAGE-8
#define EDITENTER   MAXMESSAGE-9
#define UNFOCUS     MAXMESSAGE-10
#define SETFOCUS    MAXMESSAGE-11
#define KEYBOARD    MAXMESSAGE-12
#define CHEKCHANGE  MAXMESSAGE-13
#define HIDECURSOR  MAXMESSAGE-14
#define LISTCLICK   MAXMESSAGE-15
#define COLLSTEXIT  MAXMESSAGE-16
#define OPENWINDOW  MAXMESSAGE-17
#define REPAINT		MAXMESSAGE-18
#define TIMER		MAXMESSAGE-19
#define DATAUPDATE  MAXMESSAGE-20

//Клавиатура
/*коды клавиатуры
   P |  UP   | ESC
--------------------
LEFT | ENTER | RIGHT
--------------------
  F1 | DOWN  |   F2
*/
#define kbNone    0 //ниодна клавиша не нажата
#define kbESC     1 //отмена (и выход на один уровень меню вверх)
#define kbUp      72 //2 //стрелка вверх
#define kbP       3 //вызов меню
#define kbRight   4 //стрелка вправо
#define kbENT     13//5 //выбор сделан
#define kbLeft    6 //стрелка влево
#define kbF2      7 //функциональная клавиша F2
#define kbDown    80//8 //стрелка вниз
#define kbF1      9 //функциональная клавиша F1

typedef struct {//угу, вдруг мышь подключу ;-)
  u16 x;
  u16 y;
  u8  Key;
} TMouseState;

typedef struct {//структура сообщения
  u32 Event;//тип сообщения
  //параметры сообщения
  u32 p1;//первый параметр
  u32 p2;//второй параметр
} TMessage;

#define msg_buff_size 32 //размер буфера сообщений

class Msg {
	public:
		static void send_message(u32 event, u32 p1, u32 p2);//добавить сообщение в конец очереди
		static bool get_message(TMessage* m);//извлечь первое в очереди сообщение
		static void clear_msg_queue();//очистка очереди сообщений
	private:
		static TMessage Messages[msg_buff_size];//очередь сообщений
};

#endif
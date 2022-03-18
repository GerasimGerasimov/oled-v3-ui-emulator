#include "menu.h"
#include "msg.h"

#include "graphics.h"

void TMenu::ProcessMessage(TMessage* m){//обработчик сообщений
  u16 Count = ItemsCount();
  if ( Count == 0) return;//рисовать нечего
    switch (m->Event) {
        case KEYBOARD:{//сообщения от клавиатуры
            switch (m->p1) {
                case kbUp:{//кнопка вверх
                    List[FocusLine]->Focus = false;//расфокусировка предыдущей строки
                    if (FocusLine > 0) FocusLine--;
                    List[FocusLine]->Focus = true;//фокусировка строки
                    break;
                }
                case kbDown:{//кнопка вниз
                    List[FocusLine]->Focus = false;//расфокусировка предыдущей строки
                    if ((FocusLine < (Count -1)) && (Count !=0)) FocusLine++;
                    List[FocusLine]->Focus = true;//фокусировка строки
                    break;
                }
                case kbENT: {
                    TVisualObject* p = List[FocusLine];
                    break;
                }

            }
            break;
        }
    }
}

void TMenu::View(){//вывести объект на экране
    if (isOpen == false) {
        if (Caption != NULL) {
            Caption->View();
            return;
        };
    };
    if (ItemsCount() == 0) return;//рисовать нечего
    //FillRect(Left, Top, Width, Height, 0);
    //подсчитать, сколько объектов(строк) умещаются в высоту TMenu начиная с FirstPosition
    //при этом, FocusLine входит в множество между FirstPosition и LastPosition
    u16 c = GetViewObjectsCount();//кол-во объектов умещающихся в высоту меню от FirstPosition до нижнего края
                                //это и есть кол-во объектов выводимых на экран (об их высоте уже можно не волноваться)
    u16 i = FirstPosition;//кол-во объектов выводимых на экран
    u16 h = Top;//текущая координата Y вывода строки
    //первая выводимая строка, в качестве начальных координат имеет начальные координаты TMenu
    while (i != LastPosition) {//отображаю элеменыт если в списке что-то есть 
    //перед выводом строки, требуется задать её координаты,
    //меняется координата Top в зависимости от высоты ПРЕДЫДУЩЕГО объекта
    List[i]->Left  = Left;  //задаю координату Х
    List[i]->Width = Width; //ширина строки = ширине контейнера
    List[i]->Top  = h;      //задаю координату Y
    h += List[i]->Height;   //подготовка координаты Y для следующей строки
    List[i]->View();        //теперь показываю объект
    i++;                    //перехожу к следующей строке
    }
}

u16 TMenu::GetViewObjectsCount(){//кол-во объектов умещающихся в высоту меню от FirstPosition до нижнего края
//при этом контролирую границы
  if (FocusLine <= FirstPosition)  FirstPosition = FocusLine ;//если выше верхней
  if ((FocusLine >= LastPosition) && (FocusLine < ItemsCount()))  FirstPosition++;//если ниже нижней, но не больше чем есть в списке, то подвинуть строчку
  u16 i = FirstPosition;
  u16 c = 0;//счётчик строк
  u16 h = 0; //высота объекта
  while (h <= Height) {//
    if (i < ItemsCount()) {
      h += List[i]->Height;//увеличиваю высоту
      i++; //увеличиваю указатель на объект
      c++; //приращение кол-ва строк умещающихся в видимой части списка
    }
    else {//кончились строки
      //if (c>0) c--;//отступлю назад
      LastPosition = FirstPosition + c;//вычислю номер последней отображаемой строки
      return c;
    }
  }
  //высота превысила допустимую
  if (c>0) c--;//отступлю назад
  LastPosition = FirstPosition + c;//вычислю номер последней отображаемой строки
  return c;
}

void TMenu::Add(TVisualObject* pVisualObject){//добавить объект в список
  List.push_back(pVisualObject);
}

void TMenu::AddList(std::vector <TVisualObject*> Source) {//добавить список объектов в список
    List.assign(Source.begin(), Source.end());
}

void  TMenu::Clear(){//очистит список
  List.clear();
  FocusLine = LastPosition = FirstPosition = 0;
}

TMenu::TMenu (std::string сaption, bool isOpenState, std::vector <TVisualObject*> Source) {//конструктор
  isOpen = isOpenState;
  Focus = false;
  FocusLine = FirstPosition = 0;
  LastPosition = 1;
  Left = Top = 0;//верхний левый угол
  Width  = MAX_RIGHT;  //ширина
  Height = MAX_BOTTOM; //высота
  Caption = (сaption != "")
      ? new TLabel(сaption)
      : NULL;
  AddList(Source);
}

const u16& TMenu::ItemsCount() const {
    return List.size();
}

TMenu::~TMenu() {
    if (Caption != NULL) {
        delete(Caption);
    };
};

///////////////////////////////////////////////////////////////////////////////
//контейнер (список) визуальных объектов
void TVisualObjectsList::View(){
  u16 i = List.size();//кол-во объектов в списке
  while (i != 0) {//отображаю элеменыт если в списке чтото есть
    i--; 
    List[i]->View();
  }
}

void TVisualObjectsList::Add(TVisualObject* pVisualObject){//добавить объект в список
  List.push_back(pVisualObject);
}

void TVisualObjectsList::Clear(){};//очистка списка
TVisualObjectsList::TVisualObjectsList () {};
TVisualObjectsList::~TVisualObjectsList() {};

///////////////////////////////////////////////////////////////////////////////
//const char LabelInitCaptionText[]="TLabel";
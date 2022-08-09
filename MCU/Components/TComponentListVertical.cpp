#include "TComponentListVertical.h"

bool TComponentListVertical::onEnter(void) {
    return true;
}

bool TComponentListVertical::ProcessMessage(TMessage* m){//обработчик сообщений
  if (ItemsCount() == 0) return false;//список пуст
    switch (m->Event) {
        case KEYBOARD:{//сообщения от клавиатуры
            switch (m->p1) {
                case (u32)KeyCodes::Up:{//кнопка вверх
                    goUp();
                    break;
                }
                case (u32)KeyCodes::Down:{//кнопка вниз
                    goDown();
                    break;
                }
            }
            break;
        }
    }
    for (auto& element : List) {
        element->ProcessMessage(m);
    }
    return false;
}

void TComponentListVertical::goUp(void) {
    List[FocusLine]->inFocus = false;//расфокусировка предыдущей строки
    if (FocusLine > 0) FocusLine--;
    List[FocusLine]->inFocus = true;//фокусировка строки
}

void TComponentListVertical::goDown(void) {
    u16 Count = ItemsCount();
    List[FocusLine]->inFocus = false;//расфокусировка предыдущей строки
    if ((FocusLine < (Count - 1)) && (Count != 0)) FocusLine++;
    List[FocusLine]->inFocus = true;//фокусировка строки
}

std::vector<TVisualObject*> TComponentListVertical::getFocusedElements() {
    std::vector<TVisualObject*> res = {};
    TVisualObject* p = List[FocusLine];
    if (p->inFocus) res.push_back(p);
    return res;
};

void TComponentListVertical::view(void){//вывести объект на экране
    if (ItemsCount() == 0) return;//рисовать нечего
    TGrahics::fillRect({ ElementRect.Left, ElementRect.Top , ElementRect.Width, ElementRect.Height, 0});
    //подсчитать, сколько объектов(строк) умещаются в высоту TMenu начиная с FirstPosition
    //при этом, FocusLine входит в множество между FirstPosition и LastPosition
    u16 c = GetViewObjectsCount();//кол-во объектов умещающихся в высоту меню от FirstPosition до нижнего края
                                //это и есть кол-во объектов выводимых на экран (об их высоте уже можно не волноваться)
    u16 i = FirstPosition;//кол-во объектов выводимых на экран
    u16 h = ElementRect.Top;//текущая координата Y вывода строки
    //первая выводимая строка, в качестве начальных координат имеет начальные координаты TMenu
    while (i != LastPosition) {//отображаю элеменыт если в списке что-то есть 
        //перед выводом строки, требуется задать её координаты,
        //меняется координата Top в зависимости от высоты ПРЕДЫДУЩЕГО объекта
        List[i]->ElementRect.Left  = ElementRect.Left;  //задаю координату Х
        List[i]->ElementRect.Width = ElementRect.Width; //ширина строки = ширине контейнера
        List[i]->ElementRect.Top  = h;      //задаю координату Y
        h += List[i]->getHeight();   //подготовка координаты Y для следующей строки
        List[i]->view();        //теперь показываю объект
        i++;                    //перехожу к следующей строке
    }
}

const u16 TComponentListVertical::getHeight(void) {
    return ElementRect.Height;
}

u16 TComponentListVertical::GetViewObjectsCount(){//кол-во объектов умещающихся в высоту меню от FirstPosition до нижнего края
//при этом контролирую границы
  if (FocusLine <= FirstPosition)  FirstPosition = FocusLine ;//если выше верхней
  if ((FocusLine >= LastPosition) && (FocusLine < ItemsCount()))  FirstPosition++;//если ниже нижней, но не больше чем есть в списке, то подвинуть строчку
  u16 i = FirstPosition;
  u16 c = 0;//счётчик строк
  u16 h = 0; //высота объекта
  while (h <= ElementRect.Height) {//
    if (i < ItemsCount()) {
      h += List[i]->getHeight();//увеличиваю высоту
      i++; //увеличиваю указатель на объект
      c++; //приращение кол-ва строк умещающихся в видимой части списка
    }
    else {//кончились строки
      LastPosition = FirstPosition + c;//вычислю номер последней отображаемой строки
      return c;
    }
  }
  //высота превысила допустимую
  if (c>0) c--;//отступлю назад
  LastPosition = FirstPosition + c;//вычислю номер последней отображаемой строки
  return c;
}

void  TComponentListVertical::Clear(){//очистит список
  TComponentsContainer::Clear();
  FocusLine = LastPosition = FirstPosition = 0;
}

TComponentListVertical::TComponentListVertical (std::vector <TVisualObject*> Source) {//конструктор
  isOpen = false;
  inFocus = false;
  FocusLine = FirstPosition = 0;
  LastPosition = 1;
  ElementRect = { 0, 0, VIEW_PORT_MAX_HEIGHT, VIEW_PORT_MAX_WIDTH };
  AddList(Source);
}

TComponentListVertical::~TComponentListVertical() {
};

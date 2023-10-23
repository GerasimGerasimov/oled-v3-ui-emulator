#include "LabelTime.h"
#include "parameters.h"

#include <iomanip>
#include <sstream>

#define MIN_IN_HOUR 60

void TLabelTime::outCaption(TColorScheme& ColorScheme) {
  s16 Left = ElementRect.Left;
  s16 Top = ElementRect.Top;
  if (Style & (int)LabelsStyle::TEXT_ALIGN_CENTER) {
    /*��������� �������� ���� ������ ������ � ElementRect.Width*/
    Left = (ElementRect.Width - TextSize.width) / 2;
  }
  if (Caption != oldCaption) {
    if (Caption != (static_cast<TParameter*>(DataSrc)->getDefaultValue())) {
      setTimeToHH_MM();
    }

  }
    TGrahics::outText(Caption, Left, Top, ColorScheme.Color, Font);
}

void TLabelTime::setTimeToHH_MM() {
  int time;
  std::stringstream stream(Caption);
  u16 hour, minut;
  stream >> time;
  hour = time / MIN_IN_HOUR;
  minut = time % MIN_IN_HOUR;

  stream.seekg(0);
  stream.str("");

  stream << std::setfill('0') << std::setw(2) << hour << ':' << std::setfill('0') << std::setw(2) << minut;
  stream >> Caption;
  oldCaption = Caption;
}

TLabelTime::TLabelTime(TLabelInitStructure init) : TLabel(init){}
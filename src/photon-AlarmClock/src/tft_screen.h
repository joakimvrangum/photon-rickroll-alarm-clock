#ifndef TFT_SCREEN_H
#define TFT_SCREEN_H
/*
 * Project VekkerklokkePhoton
 * Description:         --
 * Author:              Joakim Vrangum
 * Date:                06.04.18
 */

#include <Adafruit_ST7735.h>

// Settings, pins, properties
#define pinCS   A2
#define pinDC   A1
#define pinRST  A0

#define WATER_COLOR 0x001F 

class Screen {
public:
  Screen() :
    tft(Adafruit_ST7735(pinCS, pinDC, pinRST)) {}

  void initScreen();
  void printHeading();
  void printDate();
  void printTime();
  void printAlarm(int& alarmHours, int& alarmMinutes);
  void eraseAlarm(int& alarmHours, int& alarmMinutes);
  String weekdayNorwegian(int& weekdayNumber);
  String monthNorwegian(int& monthNumber);
private:
  Adafruit_ST7735 tft;
};

#endif

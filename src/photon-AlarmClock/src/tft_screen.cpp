#ifndef TFT_SCREEN_CPP
#define TFT_SCREEN_CPP
/*
 * Project VekkerklokkePhoton
 * Description:         --
 * Author:              Joakim Vrangum
 * Date:                06.04.18
 */

#include "tft_screen.h"
String currDay;
int ukedagNum;
int mndNum;
int timeNum;
int minuttNum;
int sekundNum;

void Screen::initScreen() {
  tft.initR( INITR_BLACKTAB );
  tft.fillScreen(ST7735_BLACK); // Tegner skjermen sort
}

void Screen::printHeading() {
  tft.setCursor(1, 0);
  tft.setTextColor(ST7735_MAGENTA);
  tft.setTextSize(3);
  tft.setTextWrap(true);
  tft.print("KLOKKEN");
  tft.setTextSize(2);
  tft.setCursor(37,30);
  tft.print(":");
  tft.setCursor(74,30);
  tft.print(":");
}

void Screen::printDate() {
  tft.setTextSize(2);
  tft.setCursor(0,55);
  tft.setTextColor(ST7735_BLACK);
  tft.print(currDay);
  tft.setCursor(0,55);
  tft.setTextColor(ST7735_CYAN);
  ukedagNum = Time.weekday();
  mndNum = Time.month();
  tft.print(weekdayNorwegian(ukedagNum));
  tft.setCursor(0,75);
  tft.print(Time.day());
  tft.setCursor(30,75);
  tft.setTextSize(1);
  tft.print(monthNorwegian(mndNum));
}

void Screen::printAlarm(int& alarmHours, int& alarmMinutes) {
  tft.setTextSize(2);
  tft.setCursor(0,105);
  tft.setTextColor(ST7735_RED);
  tft.print("ALARM");
  tft.setCursor(30,125);
  tft.print(alarmHours);
  tft.print(":");
  tft.print(alarmMinutes);
}

void Screen::eraseAlarm(int& alarmHours, int& alarmMinutes) {
  tft.setTextSize(2);
  tft.setCursor(0,105);
  tft.setTextColor(ST7735_BLACK);
  tft.print("ALARM");
  tft.setCursor(30,125);
  tft.print(alarmHours);
  tft.print(":");
  tft.print(alarmMinutes);
}

void Screen::printTime() {
  tft.setTextSize(2);
  tft.setCursor(10,30);

  if (timeNum != Time.hour()) {
    tft.setCursor(10,30);
    tft.setTextColor(ST7735_BLACK);
    tft.print(timeNum);
    timeNum = Time.hour();
    tft.setCursor(10,30);
    tft.setTextColor(ST7735_WHITE);
    tft.print(timeNum);
  }

  tft.setCursor(50,30);
  if (minuttNum != Time.minute()) {
    tft.setCursor(50,30);
    tft.setTextColor(ST7735_BLACK);
    tft.print(minuttNum);
    minuttNum = Time.minute();
    tft.setCursor(50,30);
    tft.setTextColor(ST7735_WHITE);
    tft.print(minuttNum);
  }

  tft.setCursor(90,30);
  tft.setTextColor(ST7735_BLACK);
  tft.print(sekundNum);
  tft.setCursor(90,30);
  sekundNum = Time.second();
  tft.setTextColor(ST7735_WHITE);
  tft.print(sekundNum);
  delay(900);
}

String Screen::weekdayNorwegian(int& weekdayNumber) {
  switch (weekdayNumber) {
    case 1:
      return "Søndag";
    case 2:
      return "Mandag";
    case 3:
      return "Tirsdag";
    case 4:
      return "Onsdag";
    case 5:
      return "Torsdag";
    case 6:
      return "Fredag";
    case 7:
      return "Lørdag";
  }
}

String Screen::monthNorwegian(int& monthNumber) {
  switch (monthNumber) {
    case 1:
      return "JANUAR";
    case 2:
      return "FEBRUAR";
    case 3:
      return "MARS";
    case 4:
      return "APRIL";
    case 5:
      return "MAI";
    case 6:
      return "JUNI";
    case 7:
      return "JULI";
    case 8:
      return "AUGUST";
    case 9:
      return "SEPTEMBER";
    case 10:
      return "OKTOBER";
    case 11:
      return "NOVEMBER";
    case 12:
      return "DESEMBER";
  }
}



#endif

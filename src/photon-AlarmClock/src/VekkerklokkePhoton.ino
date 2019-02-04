#ifndef VEKKERKLOKKEPHOTON_INO
#define VEKKERKLOKKEPHOTON_INO

/*
 * Project VekkerklokkePhoton
 * Description:         --
 * Author:              Joakim Vrangum
 * Date:                06.04.18
 */
 // _DEVICE = YOUR_DEVICE_ID_FOR_EASY_REF
 // _TOKEN = YOUR_SECRET_TOKEN_FOR_REF
#include "tft_screen.h"
#include "alarm_sound.h"
#include "sensor.h"

// Objekter
Screen tft;
Alarm_Sound alarm;
Sensor sensor;
// Pre-deklarasjoner
int setAlarm(String command);
int deleteAlarm(String command);

// variabler
bool isAlarmSet = false;
int alarmHours;
int alarmMinutes;

/**
* Validerer tid, initialiserer skjermen, setter opp tekst, og sørger for at
* speakeren har riktig pinMode. Gjør funksjonene og èn variabel tilgjenglig
* via Particle Cloud API
**/
void setup() {
  waitFor(Time.isValid, 10000);
  Time.zone(2);  // Oslo, GMT +2
  pinMode(pinSpeaker, OUTPUT);

  tft.initScreen();
  tft.printHeading();
  Particle.function("setAlarm", setAlarm);
  Particle.function("deleteAlarm", deleteAlarm);
  Particle.variable("isAlarmSet", isAlarmSet);

  //Serial.begin(9600);   <-- Brukt til debug av sensor
  pinMode(pinTriggerSensor,OUTPUT);
  pinMode(pinEchoSensor,INPUT);
}

void loop() {
  tft.printDate();
  tft.printTime();

  if ((isAlarmSet == true) && (Time.hour ()== alarmHours) && (Time.minute() == alarmMinutes)) {
    ringAlarm();
    if (sensor.checkSensorForAlarmStop() == true) {
      isAlarmSet = false;
      tft.eraseAlarm(alarmHours, alarmMinutes);
    }
  }
}

int setAlarm(String alarmtime) {
  alarmHours = atoi(alarmtime.substring(0,2));
  alarmMinutes = atoi(alarmtime.substring(2,4));
  isAlarmSet = true;
  tft.printAlarm(alarmHours, alarmMinutes);
  return 1;
}

int deleteAlarm(String command) {
  isAlarmSet = false;
  tft.eraseAlarm(alarmHours, alarmMinutes);
}

void ringAlarm() {
  alarm.playSound();
}

#endif

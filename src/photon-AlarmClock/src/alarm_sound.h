#ifndef ALARM_SOUND_H
#define ALARM_SOUND_H
/*
 * Project VekkerklokkePhoton
 * Description:         Bibliotek for å spille av alarm-lyden.
 *                      Rick Astley - Never Gonne Give You Up
 * Author:              Joakim Vrangum
 * Date:                06.04.18
 */
#include "Particle.h"

// Settings, pins, properties
#define pinSpeaker D3
const int songLength = 18;
/** Noter. Space = opphold */
const char notes[] = "cdfda ag cdfdg gf "; // space = opphold
/** 1 = 1/4 tone, 2 halvnote, etc... Space (opphold) trenger også lengde */
const int beats[] = {1,1,1,1,1,1,4,4,2,1,1,1,1,1,1,4,4,2};
/** Hastigheten på melodi. Lavere tall = raskere */
const int tempo = 150;


class Alarm_Sound {
public:
  void playSound();
  int frequency(char note);

};


#endif

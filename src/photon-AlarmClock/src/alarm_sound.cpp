#ifndef ALARM_SOUND_CPP
#define ALARM_SOUND_CPP
/*
 * Project VekkerklokkePhoton
 * Description:         --
 * Author:              Joakim Vrangum
 * Date:                06.04.18
 */

#include "alarm_sound.h"

void Alarm_Sound::playSound() {
  int i, duration;
  for (i = 0; i < songLength; i++) {
    duration = beats[i] * tempo;
    if (notes[i] == ' ') delay(duration);
    else {
      tone(pinSpeaker, frequency(notes[i]), duration);
      delay(duration);
    }
    delay(tempo/10);
  }
}


int Alarm_Sound::frequency(char note)
{
  int i;
  const int numNotes = 8;
  char names[] = { 'c', 'd', 'e', 'f', 'g', 'a', 'b', 'C' };
  int frequencies[] = {262, 294, 330, 349, 392, 440, 494, 523};
  for (i = 0; i < numNotes; i++) {
    if (names[i] == note) {
      return(frequencies[i]);
    }
  }
  return(0);
}

#endif

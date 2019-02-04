#ifndef SENSOR_CPP
#define SENSOR_CPP
/*
 * Project VekkerklokkePhoton
 * Description:         --
 * Author:              Joakim Vrangum
 * Date:                06.04.18
 */

#include "sensor.h"

bool Sensor::checkSensorForAlarmStop() {
  digitalWrite(pinTriggerSensor, LOW);
  delayMicroseconds(2);
  digitalWrite(pinTriggerSensor, HIGH);
  delayMicroseconds(10);
  digitalWrite(pinTriggerSensor, LOW);
  Duration = pulseIn(pinEchoSensor,HIGH);
  long distanceMM = calculateDistance(Duration);
  if (distanceMM <= 75) {
    return true;
  }
  return false;
  delay(50);
}

/**
* Calculates distance from sensor in mm
**/
long Sensor::calculateDistance(long time) {
    long DistanceCalc = ((time /2.9) / 2);
    return DistanceCalc;
}

#endif

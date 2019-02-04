#ifndef SENSOR_H
#define SENSOR_H
/*
 * Project VekkerklokkePhoton
 * Description:         --
 * Author:              Joakim Vrangum
 * Date:                06.04.18
 */
#include "Particle.h"
// Settings, pins, properties
#define pinEchoSensor     D0
#define pinTriggerSensor  D1

class Sensor {
  long Duration = 0;
public:
  bool checkSensorForAlarmStop();
private:
  long calculateDistance(long time);
};

#endif

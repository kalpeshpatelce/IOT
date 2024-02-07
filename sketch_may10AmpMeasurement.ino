/*ACS712 Current Sensor Demo
   By miliohm.com
*/
#include "ACS712.h"
//sensor data
ACS712 sensor(ACS712_20A, A0);
//ACS712_20A for 20 Amp type
//ACS712_30A for 30 Amp type

void setup() {
  Serial.begin(9600);
  sensor.calibrate();
  
}
void loop() {

  float I = sensor.getCurrentAC();
//ignoring the value below 0.09
  if (I < 0.09) {
    I = 0;
  }

  Serial.println(I);
  delay(1000);
}
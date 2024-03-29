#include <Wire.h>
const int sensorIn = A0;
int mVperAmp = 140; // use 185 for 5A, 100 for 20A Module and 66 for 30A Module
#define RELAY_PIN D7
double Voltage = 0;
double VRMS = 0;
double AmpsRMS = 0;

void setup(){ 
      pinMode(A0, INPUT);
      Serial.begin(9600);
      Wire.begin();
      delay(10);
      Serial.println(F("Init...."));

  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, LOW); // Turn the relay off initially

}

void loop(){
 Voltage = getVPP();
 VRMS = (Voltage/2.0) *0.707; // sq root
 AmpsRMS = (VRMS * 1000)/mVperAmp;
 float Wattage = (220*AmpsRMS)-18; //Observed 18-20 Watt when no load was connected, so substracting offset value to get real consumption.
 Serial.print(AmpsRMS);
 Serial.println(" Amps RMS ");
 Serial.print(Wattage); 
 Serial.println(" Watt ");
 delay(2000);
}

MakeBucketPowerOn()
{
if (( AmpsRMS == 0.05 ) || (AmpsRMS == 0.04) || (AmpsRMS == 0.02))
   {
     digitalWrite(RELAY_PIN, LOW); // Turn the relay off
     Serial.println("Relay Off");
     delay(15000);
     digitalWrite(RELAY_PIN, HIGH);
     delay(20000);
   } 
delay(10000)
}

float getVPP()
{
  float result;
  
  int readValue;             //value read from the sensor
  int maxValue = 0;          // store max value here
  int minValue = 1024;          // store min value here
  
   uint32_t start_time = millis();

   while((millis()-start_time) < 1000) //sample for 1 Sec
   {
       readValue = analogRead(sensorIn);
       // see if you have a new maxValue
       if (readValue > maxValue) 
       {
           /*record the maximum sensor value*/
           maxValue = readValue;
       }
       if (readValue < minValue) 
       {
           /*record the maximum sensor value*/
           minValue = readValue;
       }
/*       Serial.print(readValue);
       Serial.println(" readValue ");
       Serial.print(maxValue);
       Serial.println(" maxValue ");
       Serial.print(minValue);
       Serial.println(" minValue ");
       delay(1000); */
    }
   
   // Subtract min from max
   result = ((maxValue - minValue) * 5)/1024.0;
      
   return result;
 }
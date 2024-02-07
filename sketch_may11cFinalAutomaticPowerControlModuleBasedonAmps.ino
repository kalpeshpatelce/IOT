#include <Wire.h>
#include <ACS712.h>

ACS712 acs712(ACS712_20A, A0); // Create an instance of ACS712 sensor, with 20A range, connected to A0 pin
const int RELAY_PIN = D7; // Set the pin number for the relay
const int THRESHOLD = 40; // Set the threshold value in milliamps (0.04A)
const int CHECK_INTERVAL = 60000; // Set the check interval in milliseconds (15 minutes) / 1 hours
double Voltage = 0;
double VRMS = 0;
double AmpsRMS = 0;
const int sensorIn = A0;
int mVperAmp = 148; // use 185 for 5A, 100 for 20A Module and 66 for 30A Module
unsigned long lastCheckTime = 0; // Initialize the last check time to 0

double AmpsValue;

void setup() {
  Serial.begin(9600); // Initialize serial communication for debugging
  pinMode(RELAY_PIN, OUTPUT); // Set the relay pin as an output
  digitalWrite(RELAY_PIN, HIGH); // Turn off the relay initially
}

void loop() {
 Voltage = getVPP();
 VRMS = (Voltage/2.0) *0.707; // sq root
 AmpsRMS = (VRMS * 1000)/mVperAmp;
 float Wattage = (220*AmpsRMS)-18; //Observed 18-20 Watt when no load was connected, so substracting offset value to get real consumption.
 Serial.print(AmpsRMS);
 Serial.println(" Amps RMS ");
 Serial.print(Wattage); 
 Serial.println(" Watt ");
delay(1000);

  unsigned long currentTime = millis(); // Get the current time

  if (currentTime - lastCheckTime >= CHECK_INTERVAL) { // Check the power consumption every 15 minutes
    float current = acs712.getCurrentDC(); // Read the current from the ACS712 sensor
    // Serial.print("Current: "); 
    // Serial.print(current); 
    // Serial.println(" mA");
     Serial.print(AmpsRMS);
     Serial.println(" Amps RMS ");
      AmpsValue = AmpsRMS;

if (AmpsValue >= 0.01 && AmpsValue <= 0.01){ // If the current is below the threshold value that 0.01 to 0.09, turn off the relay
//if (AmpsValue == THRESHOLDVal1)  {
    //if (current < THRESHOLD) { // If the current is below the threshold, turn off the relay
      digitalWrite(RELAY_PIN, LOW); // Turn off the relay
      Serial.println("Relay turned off");
      //delay(3580000); //59 miniute 40 seconds
      //digitalWrite(RELAY_PIN, HIGH); // Turn on the relay
    } 
     else { // If the current is above the threshold, turn on the relay
       digitalWrite(RELAY_PIN, HIGH); // Turn on the relay
       Serial.println("Relay turned on");
     }

    lastCheckTime = currentTime; // Update the last check time
  }
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

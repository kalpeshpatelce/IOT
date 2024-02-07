#include <Wire.h>
#include <RTClib.h>

#define RELAY_PIN D7

RTC_DS1307 rtc;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  rtc.begin();

  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, LOW); // Turn the relay off initially
}

void loop() {
  DateTime now = rtc.now();
  Serial.print(now.year(), DEC);
  Serial.print('/');
  Serial.print(now.month(), DEC);
  Serial.print('/');
  Serial.print(now.day(), DEC);
  Serial.print(' ');
  Serial.print(now.hour(), DEC);
  Serial.print(':');
  Serial.print(now.minute(), DEC);
  Serial.print(':');
  Serial.print(now.second(), DEC);
  Serial.println();

  // Turn the relay on between 4 AM and 11 PM
   if (now.hour() >= 4 && now.hour() <= 11) 
   //if ( (now.minute() >= 00 && now.minute() <= 5) || (now.minute() >= 11 && now.minute() <= 15) || (now.minute() >= 21 && now.minute() <= 25) || (now.minute() >= 31 && now.minute() <= 35) || (now.minute() >= 41 && now.minute() <= 45) || (now.minute() >= 51 && now.minute() <= 55))
   {
     digitalWrite(RELAY_PIN, HIGH); // Turn the relay on
     Serial.println("Relay On");
   } else {
     digitalWrite(RELAY_PIN, LOW); // Turn the relay off
     Serial.println("Relay Off");
   }


  delay(1000); // Wait for 1 second before checking the RTC again
}




// #include <Wire.h>
// #include <RTClib.h>

// // Define RTC object
// RTC_DS1307 rtc;

// void setup() {
//   Serial.begin(9600);
//   Wire.begin();
//   rtc.begin();
  
//   // Uncomment below line if you want to set the RTC time to a specific time
//   // rtc.adjust(DateTime(YYYY, MM, DD, HH, MM, SS));
// }

// void loop() {
//   // Get current date and time from RTC module
//   DateTime now = rtc.now();
  
//   // Display date and time in Serial Monitor
//   Serial.print("Date: ");
//   Serial.print(now.day(), DEC);
//   Serial.print('/');
//   Serial.print(now.month(), DEC);
//   Serial.print('/');
//   Serial.print(now.year(), DEC);
//   Serial.print(" Time: ");
//   Serial.print(now.hour(), DEC);
//   Serial.print(':');
//   Serial.print(now.minute(), DEC);
//   Serial.print(':');
//   Serial.print(now.second(), DEC);
//   Serial.println();
  
//   delay(1000); // Wait 1 second before updating again
// }

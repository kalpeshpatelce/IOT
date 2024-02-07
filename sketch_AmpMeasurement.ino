/*ACS712 Current Sensor Demo
   By miliohm.com
*/
#include <WiFiUdp.h>
#include <NTPClient.h>
#include <ESP8266WiFi.h>
#include "ACS712.h"


// Replace with your network credentials
const char* ssid     = "kalpeshRT";
const char* password = "87654321";

// Define NTP properties
const char* ntpServerName = "in.pool.ntp.org"; // India NTP server
const long  gmtOffset_sec = 19800;  // GMT offset in seconds (India Standard Time = UTC+5:30)
const int   daylightOffset_sec = 0; // Daylight offset in seconds

String formattedDate;
String dayStamp;
String timeStamp;

// Define UDP and NTP Client objects
WiFiUDP udp;
NTPClient ntpClient(udp, ntpServerName, gmtOffset_sec, daylightOffset_sec);

//sensor data
ACS712 sensor(ACS712_05B, A0);
//ACS712_20A for 20 Amp type
//ACS712_30A for 30 Amp type
void setup() {
  Serial.begin(9600);
  sensor.calibrate();
    WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
  ntpClient.begin(); // Start NTP Client
  ntpClient.forceUpdate(); // Update NTP immediately
}
void loop() {



  float I = sensor.getCurrentAC();
//ignoring the value below 0.09
  if (I < 0.09) {
    I = 0;
  }

  ntpClient.update(); // Update NTP Client
//  Serial.print("Date: ");
//  Serial.print(ntpClient.getFormattedDate()); // Display current date
//  Serial.print(" Time: ");
// Serial.println(ntpClient.getFormattedTime());
  formattedDate = ntpClient.getFormattedDate();

// Extract date
  int splitT = formattedDate.indexOf("T");
  dayStamp = formattedDate.substring(0, splitT);
  Serial.print("DATE: ");
  Serial.println(dayStamp);



  Serial.println(I);
  delay(1000);
}
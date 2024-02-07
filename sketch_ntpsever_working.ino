#include <WiFiUdp.h>
#include <NTPClient.h>
#include <ESP8266WiFi.h>


// Replace with your network credentials
const char* ssid     = "kalpeshRT";
const char* password = "87654321";

// Define NTP properties
const char* ntpServerName = "in.pool.ntp.org"; // India NTP server
const long  gmtOffset_sec = 19800;  // GMT offset in seconds (India Standard Time = UTC+5:30)
const int   daylightOffset_sec = 0; // Daylight offset in seconds

// Define UDP and NTP Client objects
WiFiUDP udp;
NTPClient ntpClient(udp, ntpServerName, gmtOffset_sec, daylightOffset_sec);
//RTC_DS1307 rtc;
void setup() {
  Serial.begin(9600);
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
  ntpClient.update(); // Update NTP Client
  Serial.print("Date: ");
  Serial.print(ntpClient.getFormattedDate()); // Display current date
  Serial.print(" Time: ");
  Serial.println(ntpClient.getFormattedTime()); // Display current time
  delay(1000); // Wait 1 second before updating again
}

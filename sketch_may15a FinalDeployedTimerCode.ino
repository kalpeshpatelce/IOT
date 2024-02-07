#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <Wire.h>
#include <RTClib.h>
#define RELAY_PIN D7

RTC_DS1307 rtc;

const char* ssid = "kalpeshRTA";
const char* password = "87654321";

ESP8266WebServer server(80);

void handleRoot() {
  String html = "<html><body style='justify-content:center;'>";
  html += "<h2>Set Date & Time</h2><br>";
  html += "<h3>Developed By Kalpesh Patel (CE-CSPIT)<br></h3>";
  //html += "<form action='/set' method='POST'>";
  html += "<form action='/set' method='POST'>";
  html += "Date (YYYY-MM-DD): <input type='text' name='date'><br>";
  html += "Time (HH:MM:SS): <input type='text' name='time'><br>";
  html += "<input type='submit' value='Set'>";
  html += "</form></body></html>";
  server.send(200, "text/html", html);
}

void handleSet() {
  String dateStr = server.arg("date");
  String timeStr = server.arg("time");

  int year = dateStr.substring(0,4).toInt();
  int month = dateStr.substring(5,7).toInt();
  int day = dateStr.substring(8,10).toInt();

  int hour = timeStr.substring(0,2).toInt();
  int minute = timeStr.substring(3,5).toInt();
  int second = timeStr.substring(6,8).toInt();

  DateTime now(year, month, day, hour, minute, second);
  rtc.adjust(now);

  String html = "<html><body>";
  html += "<h2>Date & Time Set Successfully</h2>";
  html += "<p>Developer by Kalpesh Patel (CE-CSPIT)</p>";
  html += "</body></html>";
  server.send(200, "text/html", html);
}

void setup() {
    Serial.begin(9600);

  Wire.begin();
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, HIGH); // Turn the relay off initially


  // Connect to WiFi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  int timeout = 10; // 10 seconds timeout
  while (WiFi.status() != WL_CONNECTED && timeout > 0) {
    delay(1000);
    Serial.print(".");
    timeout--;
  }
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("connected!");
  } else {
    Serial.println("connection failed!");
  }

  // WiFi.begin(ssid, password);
  // while (WiFi.status() != WL_CONNECTED) {
  //   delay(1000);
  //   Serial.println("Connecting to WiFi...");
  //   Serial.println(WiFi.localIP());
  // }
  // Serial.println("WiFi connected");



  if (!rtc.begin()) {
    Serial.println("RTC not found");
    while (1);
  }

  server.on("/", handleRoot);
  server.on("/set", handleSet);

  server.begin();
  Serial.println("Server started");
}

void loop() {
    server.handleClient();
  
  
  // Check WiFi connection status
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("WiFi connection lost!");
    // Attempt to reconnect
    WiFi.begin(ssid, password);
    Serial.print("Reconnecting to WiFi");
    int timeout = 10; // 10 seconds timeout
    while (WiFi.status() != WL_CONNECTED && timeout > 0) {
      delay(500);
      Serial.print(".");
      timeout--;
    }
    if (WiFi.status() == WL_CONNECTED) {
      Serial.println("reconnected!");
    } else {
      Serial.println("reconnection failed!");
    }
  }
  
  
  
  //   // Get current date and time from RTC module
  DateTime now = rtc.now();
    // Display date and time in Serial Monitor
  Serial.print("Date: ");
  Serial.print(now.day(), DEC);
  Serial.print('/');
  Serial.print(now.month(), DEC);
  Serial.print('/');
  Serial.print(now.year(), DEC);
  Serial.print(" Time: ");
  Serial.print(now.hour(), DEC);
  Serial.print(':');
  Serial.print(now.minute(), DEC);
  Serial.print(':');
  Serial.print(now.second(), DEC);
  Serial.println();
  delay(1000);


   // Turn the relay on between 4 AM and 11 PM
   if (now.hour() >= 4 && now.hour() <= 23) 
   //if ( (now.minute() >= 00 && now.minute() <= 5) || (now.minute() >= 11 && now.minute() <= 15) || (now.minute() >= 21 && now.minute() <= 25) || (now.minute() >= 31 && now.minute() <= 35) || (now.minute() >= 41 && now.minute() <= 45) || (now.minute() >= 51 && now.minute() <= 55))
   {
     digitalWrite(RELAY_PIN, HIGH); // Turn the relay on
     Serial.println("Relay On");
   } else {
     digitalWrite(RELAY_PIN, LOW); // Turn the relay off
     Serial.println("Relay Off");
   }

}

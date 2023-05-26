# Smart SwitchBoard Project
Smart SwitchBoard Project Diagram as Below
![image](https://github.com/kalpeshpatelce/IOT/assets/13175900/65714ffe-5d6f-49f7-9148-e6dad4dc920c)
// Code for SmartBoard Project
```
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <Wire.h>
#include <RTClib.h>
#define RELAY_PIN D7

RTC_DS1307 rtc;

const char* ssid = "SmartBoardA";
const char* password = "87654321";
int StartTiHour = 4;
int EndingHour = 23;
int StartMin = 00;
int EndMin = 00;
int CurentHour;
int CurrentMin;
int tmpCurrentMin;

ESP8266WebServer server(80);

void handleRoot() {
  String html = "<html><body style='justify-content:center;'>";
  html += "<h2>Set Date & Time of RTC Module</h2><br>";
//  html += "<h2>Currently Set Date & Time : " + String(DateTime()) + "</h2><br>";
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

void handleSetHour() {
  String html = "<html><body><h1>Hour Setting Page</h1>";
  html += "<form action='/settinghour'>";
  html += "<h2>Current Set Starting & Ending Hour is : </h2>";
  html += "<h2> " + String(StartTiHour) + ":" + String(StartMin) + "-" + String(EndingHour) + ":" + String(EndMin) + " </h2>";
  html += "Enter Start Hour (0-23): <input type='number' name='shour' min='0' max='23' value='" + String(StartTiHour) + "' required><br><br>";
  html += "Enter Start Minutes (0-59): <input type='number' name='sminutes' min='' max='59' value='00' required><br><br>";
  html += "Enter Ending Hour (0-23): <input type='number' name='ehour' min='0' max='23' value='" + String(EndingHour) + "' required><br><br>";
  html += "Enter Ending Minutes (0-59): <input type='number' name='eminutes' min='' max='59' value='00' required><br><br>";
  html += "<input type='submit' value='SetHour'>";
  html += "</form></body></html>";
  server.send(200, "text/html", html);
}

void handlesettinghour(){
String SThour = server.arg("shour");
String Enhour = server.arg("ehour");
String STMin = server.arg("sminutes");
String EnMin = server.arg("eminutes");


StartTiHour = SThour.substring(0,2).toInt();
EndingHour =  Enhour.substring(0,2).toInt();
StartMin = STMin.substring(0,2).toInt();
EndMin = EnMin.substring(0,2).toInt();

 String html = "<html><body>";
  html += "<h2>Hour Set Successfully</h2>";
  html += "<h2>Hour Set As Below</h2>";
  html += "<h2> " + String(StartTiHour) + ":" + String(StartMin) + "-" + String(EndingHour) + ":" + String(EndMin) + " </h2>";
  html += "<p>Developer by Kalpesh Patel (CE-CSPIT)</p>";
  html += "</body></html>";
  server.send(200, "text/html", html);
}

void setup() {
    Serial.begin(9600);

  Wire.begin();
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, HIGH); // Turn the relay off initially



  // Set the ESP8266 module to AP mode
  WiFi.mode(WIFI_AP);

   // Configure the hotspot settings
  WiFi.softAP(ssid, password);
 

  // Connect to WiFi
  // WiFi.begin(ssid, password);
  // Serial.print("Connecting to WiFi");
  // if (WiFi.status() != WL_CONNECTED ) {
  //    delay(3000);
  //    WiFi.begin(ssid, password);
  // }

  //   Serial.print(".");
  //   if 
  // }
  delay(2000);
Serial.println(WiFi.softAPIP());
  // if (WiFi.status() == WL_CONNECTED) {
  //   Serial.println("connected!");
  //   Serial.println(WiFi.localIP());
  // } else {
  //   Serial.println("connection failed!");
  // }

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

  //Hour Module
  server.on("/", HTTP_GET, handleSetHour);
  server.on("/settinghour", handlesettinghour);

// RTC Module
  server.on("/setrtc", handleRoot);
  server.on("/set", handleSet);
//  server.on("/sethour", handleSetHour);
//  server.on("/settinghour", handlesettinghour);

  server.begin();
  Serial.println("Server started");
  
}

void loop() {
    server.handleClient();
  
  
  // Check WiFi connection status
  // if (WiFi.status() != WL_CONNECTED) {
  //   Serial.println("WiFi connection lost!");
  //   // Attempt to reconnect
  //   WiFi.begin(ssid, password);
  //   Serial.print("Reconnecting to WiFi");
  //   int timeout = 10; // 10 seconds timeout
  //   while (WiFi.status() != WL_CONNECTED && timeout > 0) {
  //     delay(500);
  //     Serial.print(".");
  //     timeout--;
  //   }
  //   // if (WiFi.status() == WL_CONNECTED) {
  //   //   Serial.println("reconnected!");
  //   // } else {
  //   //   Serial.println("reconnection failed!");
  //   // }
  // }
  
  


  
  //   // Get current date and time from RTC module
 DateTime now = rtc.now();
    //Display date and time in Serial Monitor
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
  Serial.print("Start Hour :");
  Serial.println(StartTiHour);
  //Serial.print(':');
  //Serial.println(StartMin);
  Serial.print("Ending Hour :");
  Serial.println(EndingHour);
  //Serial.print(':');
  //Serial.println(EndMin);

//   //Concate Starting Hour String
//   String ConcateStartHour = (String(StartTiHour) + String(StartMin));
//   Serial.print("concated Starting Hour String is :");
//   Serial.println(ConcateStartHour);

//  String ConcateEndingHour = (String(EndingHour) + String(EndMin));
//  Serial.print("concated Ending Hour String is :");
//  Serial.println(ConcateEndingHour);


  delay(3000);
//double tmphour = (now.day());
//double tmpMin = (now.minute());
CurentHour = rtc.now().hour();
// tmpCurrentMin = rtc.now().minute();
// if (tmpCurrentMin < 10) {
//     tmpCurrentMin = 10 + tmpCurrentMin;
//     CurrentMin = tmpCurrentMin;
//   }else
//   {
//     CurrentMin = rtc.now().minute();
//   }

CurrentMin = rtc.now().minute();
Serial.print("Current Hour is:");
Serial.println(CurentHour);
Serial.print("Current Minute is :");
Serial.println(CurrentMin);

//concat String of Current Hour & Minutes
String CurrentConcatTimeString = (String(CurentHour) + String(CurrentMin));
Serial.print("concated Current String is :");
Serial.println(CurrentConcatTimeString);

//convert to integer




   // Turn the relay on between 4 AM and 11 PM
   //if (now.hour() >= 4 && now.hour() <= 23) 
  //  if ((CurentHour > StartTiHour || (CurentHour == StartTiHour && CurrentMin >= StartMin)) && (CurentHour < EndingHour || (CurentHour == EndingHour && CurrentMin <= EndMin)))
   if (CurentHour >= StartTiHour && CurentHour < EndingHour )//&& CurrentMin >= StartMin && CurrentMin <= EndMin )
   //if (StartTiHour >= 4 && EndingHour <= 23) 
   //if ( (now.minute() >= 00 && now.minute() <= 5) || (now.minute() >= 11 && now.minute() <= 15) || (now.minute() >= 21 && now.minute() <= 25) || (now.minute() >= 31 && now.minute() <= 35) || (now.minute() >= 41 && now.minute() <= 45) || (now.minute() >= 51 && now.minute() <= 55))
   //if (StartTiHour >= 4 && EndingHour <= 23)
   {
     digitalWrite(RELAY_PIN, HIGH); // Turn the relay on
     Serial.println("Relay On");
   } else {
     digitalWrite(RELAY_PIN, LOW); // Turn the relay off
     Serial.println("Relay Off");
   }

}
```

# SMARTBOARD A
```
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <DNSServer.h>
#include <Wire.h>
#include <RTClib.h>
#define RELAY_PIN D7

RTC_DS1307 rtc;

const char* ssid = "SmartBoardA";
const char* password = "87654321";
int WebStartTiHour = 4;
int WebEndingHour = 23;
int WebStartMin = 00;
int WebEndMin = 00;
int CurentHour;
int CurrentMin;
int tmpCurrentMin;

  int startHour = 4;     // Replace with your start hour
  int startMinute = 0;   // Replace with your start minute
  int endHour = 23;      // Replace with your end hour
  int endMinute = 00;    // Replace with your end minute

ESP8266WebServer server(80);
DNSServer dnsServer;
String formattedDate;
void handleRoot() {

DateTime now = rtc.now();
  // Get the date components
  int year = now.year();
  int month = now.month();
  int day = now.day();
// Format the date as "YYYY-MM-DD"
  formattedDate = String(year) + "-" + formatDigits(month) + "-" + formatDigits(day);



 // Get the time components
  int hour = now.hour();
  int minute = now.minute();
  int second = now.second();

    // Format the time as "HH:MM:SS"
  String formattedTime = formatDigits(hour) + ":" + formatDigits(minute) + ":" + formatDigits(second);

  String html = "<html>";
  html += "<head><style>body { display: flex; align-items: center; justify-content: center; height: 10vh;} h1 { color: red; }</style></head>";
  html += "<body>";
  html += "<form action='/set' method='POST'>";
  html += "<h2>Set Date & Time of RTC Module</h2><br>";
//  html += "<h2>Currently Set Date & Time : " + String(DateTime()) + "</h2><br>";
  html += "<h3>Developed By Kalpesh Patel (CE-CSPIT)<br></h3>";
  //html += "<form action='/set' method='POST'>";
  html += "Date (YYYY-MM-DD): <input type='text' name='date' value='" +  formattedDate + "'><br>";
  html += "Time (HH:MM:SS): <input type='text' name='time' value='" + formattedTime + "'><br>";
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


  String html = "<html>";
  html += "<head><style>body { display: flex; align-items: center; justify-content: center; height: 10vh;} h1 { color: red; }</style></head>";
  html += "<body>";
  html += "<h1> " + String(year) + "-" + String(month) + "-" + String(day) + " </h1><br>";
  html += "<h2>Date & Time Set Successfully</h2><br>";
  html += "<p>Developer by Kalpesh Patel (CE-CSPIT)</p><br>";
  html += "</body></html>";
  server.send(200, "text/html", html);
}

void handleSetHour() {
  String html = "<html>";
  html += "<head><style>body { display: flex; align-items: center; justify-content: center; height: 10vh;} h1 { color: red; }</style></head>";
  html += "<body>";
  html += "<form action='/settinghour'>";
  html += "<h1>SmartBoardA</h1><br>";
  html += "<h2> Hour Setting Page </h2><br>";
  html += "<br><br><br>";
  html += "<a href='/setrtc'>Set Date & Time of RTC Cell</a><br>";
  html += "<h2>Current Set Starting & Ending Hour is : </h2>";
  html += "<h2> " + String(startHour) + ":" + String(startMinute) + "-" + String(endHour) + ":" + String(endMinute) + " </h2><br>";
  html += "Enter Start Hour (0-23): <input type='number' name='shour' min='0' max='23' value='" + String(startHour) + "' required><br><br>";
  html += "Enter Start Minutes (0-59): <input type='number' name='sminutes' min='' max='59' value='" + String(startMinute) + "' required><br><br>";
  html += "Enter Ending Hour (0-23): <input type='number' name='ehour' min='0' max='23' value='" + String(endHour) + "' required><br><br>";
  html += "Enter Ending Minutes (0-59): <input type='number' name='eminutes' min='' max='59' value='" + String(endMinute) + "' required><br><br>";
  html += "<input type='submit' value='SetHour'>";
  html += "</form></body></html>";
  server.send(200, "text/html", html);
}

void handlesettinghour(){
String SThour = server.arg("shour");
String Enhour = server.arg("ehour");
String STMin = server.arg("sminutes");
String EnMin = server.arg("eminutes");



WebStartTiHour = SThour.substring(0,2).toInt();
WebEndingHour =  Enhour.substring(0,2).toInt();
WebStartMin = STMin.substring(0,2).toInt();
WebEndMin = EnMin.substring(0,2).toInt();

startHour = WebStartTiHour;
startMinute= WebStartMin;
endHour = WebEndingHour;
endMinute = WebEndMin;
 

  String html = "<html>";
  html += "<head><style>body { display: flex; align-items: center; justify-content: center; height: 10vh;} h1 { color: red; }</style></head>";
  html += "<body>";
  html += "<a href='/'>Home</a><br>";
  html += "<h2>Hour Set Successfully</h2><br>";
  html += "<h2>Hour Set As Below</h2><br>";
  html += "<h1> " + String(startHour) + ":" + String(startMinute) + "-" + String(endHour) + ":" + String(endMinute) + " </h1><br>";
  html += "<p>Developer by Kalpesh Patel (CE-CSPIT)</p><br>";
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
  dnsServer.start(53, "*", IPAddress(192, 168, 4, 1));

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
    dnsServer.processNextRequest();
    server.handleClient();
  
 DateTime now = rtc.now();
 int currentHour = now.hour();
 int currentMinute = now.minute();
  Serial.print("RTC CurrentTime = ");
  Serial.print(currentHour);
  Serial.print(":");
  Serial.println(currentMinute);

  //assign Starthour ,StartMinute,endHour, EndMinute from WebSite

  
  // Convert start and end times to minutes for easier comparison
  int startTime = startHour * 60 + startMinute;
  int endTime = endHour * 60 + endMinute;

  Serial.print("WebTime= ");
  Serial.print(startHour);
  Serial.print(":");
  Serial.print(startMinute);
  Serial.print(" to ");
  Serial.print(endHour);
  Serial.print(":");
  Serial.println(endMinute);
  Serial.println("*********************");
  Serial.print("StartTime: ");
  Serial.println(startTime);
  Serial.print("EndTime: ");
  Serial.println(endTime);
  Serial.println("***********");

  // Convert current time to minutes
  int currentTime = currentHour * 60 + currentMinute;
  Serial.print("CurrentTime: ");
  Serial.println(currentTime);
  // if (currentTime >= startTime && currentTime <= endTime) {
  //   // RTC time is within the given start and end time range
  //   Serial.println("RTC time is within the given range!");
  // }else
  // {
  //   Serial.println("Out of range!");
  // }








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

    //Display date and time in Serial Monitor
  // Serial.print("Date: ");
  // Serial.print(now.day(), DEC);
  // Serial.print('/');
  // Serial.print(now.month(), DEC);
  // Serial.print('/');
  // Serial.print(now.year(), DEC);
  // Serial.print(" Time: ");
  // Serial.print(now.hour(), DEC);
  // Serial.print(':');
  // Serial.print(now.minute(), DEC);
  // Serial.print(':');
  // Serial.print(now.second(), DEC);
  // Serial.println();
  // Serial.print("Start Hour :");
  // Serial.println(StartTiHour);
  // //Serial.print(':');
  // //Serial.println(StartMin);
  // Serial.print("Ending Hour :");
  // Serial.println(EndingHour);
  // //Serial.print(':');
  // //Serial.println(EndMin);

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
//CurentHour = rtc.now().hour();
// tmpCurrentMin = rtc.now().minute();
// if (tmpCurrentMin < 10) {
//     tmpCurrentMin = 10 + tmpCurrentMin;
//     CurrentMin = tmpCurrentMin;
//   }else
//   {
//     CurrentMin = rtc.now().minute();
//   }

// CurrentMin = rtc.now().minute();
// Serial.print("Current Hour is:");
// Serial.println(CurentHour);
// Serial.print("Current Minute is :");
// Serial.println(CurrentMin);

// //concat String of Current Hour & Minutes
// String CurrentConcatTimeString = (String(CurentHour) + String(CurrentMin));
// Serial.print("concated Current String is :");
// Serial.println(CurrentConcatTimeString);

//convert to integer




   // Turn the relay on between 4 AM and 11 PM
   //if (now.hour() >= 4 && now.hour() <= 23) 
  //  if ((CurentHour > StartTiHour || (CurentHour == StartTiHour && CurrentMin >= StartMin)) && (CurentHour < EndingHour || (CurentHour == EndingHour && CurrentMin <= EndMin)))
   //if (CurentHour >= StartTiHour && CurentHour < EndingHour )//&& CurrentMin >= StartMin && CurrentMin <= EndMin )
   //if (StartTiHour >= 4 && EndingHour <= 23) 
   //if ( (now.minute() >= 00 && now.minute() <= 5) || (now.minute() >= 11 && now.minute() <= 15) || (now.minute() >= 21 && now.minute() <= 25) || (now.minute() >= 31 && now.minute() <= 35) || (now.minute() >= 41 && now.minute() <= 45) || (now.minute() >= 51 && now.minute() <= 55))
   //if (StartTiHour >= 4 && EndingHour <= 23)
   if (currentTime >= startTime && currentTime <= endTime)
   {
     digitalWrite(RELAY_PIN, HIGH); // Turn the relay on
     Serial.println("Relay On");
   } else {
     digitalWrite(RELAY_PIN, LOW); // Turn the relay off
     Serial.println("Relay Off");
   }

}

String formatDigits(int digits) {
  // Add leading zero if necessary
  if (digits < 10) {
    return "0" + String(digits);
  }
  return String(digits);
}

```
# Main Page
![image](https://github.com/kalpeshpatelce/IOT/assets/13175900/aea3fe7a-376a-4ad6-b4c1-ad2aa577c2ea)

# Set RTC Module Time
![image](https://github.com/kalpeshpatelce/IOT/assets/13175900/66a71ad1-41d7-4346-8841-cc5f9cf21b85)


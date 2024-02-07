#include <ESP8266WiFi.h>
#include <Wire.h>
#include "RTClib.h"

const char* ssid = "kalpeshRT";
const char* password = "87654321";

RTC_DS1307 rtc;
WiFiServer server(80);

void setup() {
  Serial.begin(9600);
  Wire.begin();

  if (!rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }

  if (!rtc.isrunning()) {
    Serial.println("RTC is NOT running!");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("WiFi connected");
  server.begin();
}

void loop() {
  WiFiClient client = server.available();

  if (client) {
    String request = client.readStringUntil('\r');
    client.flush();

    if (request.indexOf("/setTime") != -1) {
      String timeStr = request.substring(request.indexOf("time=") + 5, request.indexOf("&"));
      int hour = timeStr.substring(0, 2).toInt();
      int minute = timeStr.substring(3, 5).toInt();
      int second = timeStr.substring(6, 8).toInt();

      rtc.adjust(DateTime(0, 0, 0, hour, minute, second));
      Serial.println("Time set");
    }

    String webPage = "<html><head><title>Set Time</title></head><body>";
    webPage += "<h1>Set Time</h1>";
    webPage += "<form method='get' action='/setTime'>";
    webPage += "Hour (0-23): <input type='number' name='time' min='0' max='23' required><br>";
    webPage += "Minute (0-59): <input type='number' name='time' min='0' max='59' required><br>";
    webPage += "Second (0-59): <input type='number' name='time' min='0' max='59' required><br>";
    webPage += "<br>";
    webPage += "Developed by YourName<br>";
    webPage += "<br>";
    webPage += "<input type='submit' value='Set Time'>";
    webPage += "</form></body></html>";

    client.print("HTTP/1.1 200 OK\r\n");
    client.print("Content-Type: text/html\r\n");
    client.print("Connection: close\r\n");
    client.print("Refresh: 5\r\n");
    client.print("Content-Length: ");
    client.print(webPage.length());
    client.print("\r\n\r\n");
    client.print(webPage);
    client.stop();
  }
}




// #include <ESP8266WiFi.h>
// #include <Wire.h>
// //#include <DS1307.h>

// const char* ssid = "kalpeshRT";
// const char* password = "87654321";



// void setup() {
//   Serial.begin(9600);
//   WiFi.begin(ssid, password);
//   Serial.print("Connecting to WiFi...");
//   while (WiFi.status() != WL_CONNECTED) {
//     delay(1000);
//     Serial.print(".");
//   }
//   Serial.println();
//   Serial.print("WiFi connected, IP address: ");
//   Serial.println(WiFi.localIP());
//   Wire.begin();

// }

// void loop() {
//   if (WiFi.status() == WL_CONNECTED) {
//     handleSetTimePage();
//   }
// }

// void handleSetTimePage() {
//   WiFiServer server(80);
//   server.begin();

//   while (true) {
//     WiFiClient client = server.available();
//     if (!client) {
//       continue;
//     }

//     String request = client.readStringUntil('\r');
//     client.flush();

//     client.println("HTTP/1.1 200 OK");
//     client.println("Content-Type: text/html");
//     client.println("");
//     client.println("<!DOCTYPE HTML>");
//     client.println("<html>");
//     client.println("<head><title>Set Time</title></head>");
//     client.println("<body>");
//     client.println("<style>");
//     client.println("h1 {text-align: center;}");
//     client.println("p {text-align: center;}");
//     client.println("div {text-align: center;}");
//     client.println("</style>");
//     client.println("<h1>Bucket Time Setting System </h1>");
//     client.println("<form action=\"/setTime\">");
//     client.println("<div align=left>");
//     //client.println("Time: <input type=\"text\" name=\"time\" placeholder=\"HH:MM:SS\"><br>");
//     client.println("Year       : <input type=\"text\" name=\"date\" placeholder=\"YY\">");
//     client.println("(Please enter the current year, 00-99. - )<br>");
//     client.println("Month      : <input type=\"text\" name=\"date\" placeholder=\"MM\">");
//     client.println("(Please enter the current month, 1-12. -) <br>");
//     client.println("Current Day: <input type=\"text\" name=\"date\" placeholder=\"DD\">");
//     client.println("(Please enter the current day of the month, 1-31. -) <br>");
//     client.println("Current Day of Week: <input type=\"text\" name=\"date\" placeholder=\"1-7\">");
//     client.println("(1 Sun | 2 Mon | 3 Tues | 4 Weds | 5 Thu | 6 Fri | 7 Sat - ) <br>");
//     client.println("Current Hour: <input type=\"text\" name=\"date\" placeholder=\"HH\">");
//     client.println("(Please enter the current hour in 24hr format, 0-23. -)<br>");
//     client.println("Current Minute: <input type=\"text\" name=\"date\" placeholder=\"M\">");
//     client.println("(Please enter the current minute, 0-59. - )<br>");
//     client.println("<input type=\"submit\" value=\"Set Time\">");
//     client.println("</div>");
//     client.println("</form>");
//     client.println("</body>");
//     client.println("</html>");

//   Wire.beginTransmission(DS1307);
//   Wire.write(byte(0));
//   Wire.write(decToBcd(second));
//   Wire.write(decToBcd(minute));
//   Wire.write(decToBcd(hour));
//   Wire.write(decToBcd(weekday));
//   Wire.write(decToBcd(monthday));
//   Wire.write(decToBcd(month));
//   Wire.write(decToBcd(year));
//   Wire.write(byte(0));
//   Wire.endTransmission();

//     delay(100);
//   }
// }

//MAC Address of this board 2C:F4:32:3C:69:B0
#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 5, en = 0, d4 = 14, d5 = 12, d6 = 4, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// Import required libraries
#include <EEPROM.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#ifdef ESP32
  #include <WiFi.h>
  #include <AsyncTCP.h>
#else
  #include <ESP8266WiFi.h>
  #include <ESPAsyncTCP.h>
#endif
#include <ESPAsyncWebServer.h>

#define EEPROM_SIZE 80
#define alarmpin 15 
#define alarmonoffpin 2 
// Replace with your network credentials
const char* ssid = "CHARUSAT Wi-Fi";
const char* password = "charusat";


// Define NTP Client to get time
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);

// Variables to save date and time in String
String formattedDate;
String DDStamp;
String MMStamp;
String YYYYStamp;
String HH1Stamp;
String MM1Stamp;
String SS1Stamp;
String dayStamp, dayStamp1;
String TIMEStamp;
String DATEStamp;

// Variables to save date and time in integer

int DDint, MMint, YYYYint, HH1int, MM1int, SS1int, dayint;

const char* PARAM_INPUT_101 = "input101";const char* PARAM_INPUT_102 = "input102";const char* PARAM_INPUT_103 = "input103";const char* PARAM_INPUT_104 = "input104";
const char* PARAM_INPUT_201 = "input201";const char* PARAM_INPUT_202 = "input202";const char* PARAM_INPUT_203 = "input203";const char* PARAM_INPUT_204 = "input204";
const char* PARAM_INPUT_301 = "input301";const char* PARAM_INPUT_302 = "input302";const char* PARAM_INPUT_303 = "input303";const char* PARAM_INPUT_304 = "input304";
const char* PARAM_INPUT_401 = "input401";const char* PARAM_INPUT_402 = "input402";const char* PARAM_INPUT_403 = "input403";const char* PARAM_INPUT_404 = "input404";
const char* PARAM_INPUT_501 = "input501";const char* PARAM_INPUT_502 = "input502";const char* PARAM_INPUT_503 = "input503";const char* PARAM_INPUT_504 = "input504";
const char* PARAM_INPUT_601 = "input601";const char* PARAM_INPUT_602 = "input602";const char* PARAM_INPUT_603 = "input603";const char* PARAM_INPUT_604 = "input604";
const char* PARAM_INPUT_701 = "input701";const char* PARAM_INPUT_702 = "input702";const char* PARAM_INPUT_703 = "input703";const char* PARAM_INPUT_704 = "input704";
const char* PARAM_INPUT_801 = "input801";const char* PARAM_INPUT_802 = "input802";const char* PARAM_INPUT_803 = "input803";const char* PARAM_INPUT_804 = "input804";
const char* PARAM_INPUT_901 = "input901";const char* PARAM_INPUT_902 = "input902";const char* PARAM_INPUT_903 = "input903";const char* PARAM_INPUT_904 = "input904";
const char* PARAM_INPUT_1001 = "input1001";const char* PARAM_INPUT_1002 = "input1002";const char* PARAM_INPUT_1003 = "input1003";const char* PARAM_INPUT_1004 = "input1004";
const char* PARAM_INPUT_1101 = "input1101";const char* PARAM_INPUT_1102 = "input1102";const char* PARAM_INPUT_1103 = "input1103";const char* PARAM_INPUT_1104 = "input1104";
const char* PARAM_INPUT_1201 = "input1201";const char* PARAM_INPUT_1202 = "input1202";const char* PARAM_INPUT_1203 = "input1203";const char* PARAM_INPUT_1204 = "input1204";
const char* PARAM_INPUT_1301 = "input1301";const char* PARAM_INPUT_1302 = "input1302";const char* PARAM_INPUT_1303 = "input1303";const char* PARAM_INPUT_1304 = "input1304";
const char* PARAM_INPUT_1401 = "input1401";const char* PARAM_INPUT_1402 = "input1402";const char* PARAM_INPUT_1403 = "input1403";const char* PARAM_INPUT_1404 = "input1404";
const char* PARAM_INPUT_1501 = "input1501";const char* PARAM_INPUT_1502 = "input1502";const char* PARAM_INPUT_1503 = "input1503";const char* PARAM_INPUT_1504 = "input1504";
const char* PARAM_INPUT_1601 = "input1601";const char* PARAM_INPUT_1602 = "input1602";const char* PARAM_INPUT_1603 = "input1603";const char* PARAM_INPUT_1604 = "input1604";
const char* PARAM_INPUT_1701 = "input1701";const char* PARAM_INPUT_1702 = "input1702";const char* PARAM_INPUT_1703 = "input1703";const char* PARAM_INPUT_1704 = "input1704";
const char* PARAM_INPUT_1801 = "input1801";const char* PARAM_INPUT_1802 = "input1802";const char* PARAM_INPUT_1803 = "input1803";const char* PARAM_INPUT_1804 = "input1804";
const char* PARAM_INPUT_1901 = "input1901";const char* PARAM_INPUT_1902 = "input1902";const char* PARAM_INPUT_1903 = "input1903";const char* PARAM_INPUT_1904 = "input1904";
const char* PARAM_INPUT_2001 = "input2001";const char* PARAM_INPUT_2002 = "input2002";const char* PARAM_INPUT_2003 = "input2003";const char* PARAM_INPUT_2004 = "input2004";


String inputMessage101,inputMessage102,inputMessage103,inputMessage104;
String inputMessage201,inputMessage202,inputMessage203,inputMessage204;
String inputMessage301,inputMessage302,inputMessage303,inputMessage304;
String inputMessage401,inputMessage402,inputMessage403,inputMessage404;
String inputMessage501,inputMessage502,inputMessage503,inputMessage504;
String inputMessage601,inputMessage602,inputMessage603,inputMessage604;
String inputMessage701,inputMessage702,inputMessage703,inputMessage704;
String inputMessage801,inputMessage802,inputMessage803,inputMessage804;
String inputMessage901,inputMessage902,inputMessage903,inputMessage904;
String inputMessage1001,inputMessage1002,inputMessage1003,inputMessage1004;
String inputMessage1101,inputMessage1102,inputMessage1103,inputMessage1104;
String inputMessage1201,inputMessage1202,inputMessage1203,inputMessage1204;
String inputMessage1301,inputMessage1302,inputMessage1303,inputMessage1304;
String inputMessage1401,inputMessage1402,inputMessage1403,inputMessage1404;
String inputMessage1501,inputMessage1502,inputMessage1503,inputMessage1504;
String inputMessage1601,inputMessage1602,inputMessage1603,inputMessage1604;
String inputMessage1701,inputMessage1702,inputMessage1703,inputMessage1704;
String inputMessage1801,inputMessage1802,inputMessage1803,inputMessage1804;
String inputMessage1901,inputMessage1902,inputMessage1903,inputMessage1904;
String inputMessage2001,inputMessage2002,inputMessage2003,inputMessage2004;

String temp, temp1, temp2, temp3, temp4;

byte a101,a102,a103,a104;
byte a201,a202,a203,a204;
byte a301,a302,a303,a304;
byte a401,a402,a403,a404;
byte a501,a502,a503,a504;
byte a601,a602,a603,a604;
byte a701,a702,a703,a704;
byte a801,a802,a803,a804;
byte a901,a902,a903,a904;
byte a1001,a1002,a1003,a1004;
byte a1101,a1102,a1103,a1104;
byte a1201,a1202,a1203,a1204;
byte a1301,a1302,a1303,a1304;
byte a1401,a1402,a1403,a1404;
byte a1501,a1502,a1503,a1504;
byte a1601,a1602,a1603,a1604;
byte a1701,a1702,a1703,a1704;
byte a1801,a1802,a1803,a1804;
byte a1901,a1902,a1903,a1904;
byte a2001,a2002,a2003,a2004;


const char* http_username = "admin";
const char* http_password = "cspiteeemd";

const char* PARAM_INPUT_S = "state";

const int output = alarmonoffpin;

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);

const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html>
<head>
<style>

table {
  font-family: arial, sans-serif;
  border-collapse: collapse;
  width: 80%;
}

td, th {
  border: 1px solid #dddddd;
  text-align: center;
  padding: 10px;
}

  tr:nth-child(even) {
  background-color: #dddddd;
}

h2{
color:red;
font-size:50px;
text-align: center;
}
h3{
color:black;
font-size:20px;
text-align: center;
}

p{
color:blue;
font-size:35px;
text-align: center;
}

<style>
    .switch {position: relative; display: inline-block; width: 120px; height: 68px} 
    .switch input {display: none}
    .slider {position: absolute; top: 0; left: 0; right: 0; bottom: 0; background-color: #ccc; border-radius: 34px}
    .slider:before {position: absolute; content: ""; height: 52px; width: 52px; left: 8px; bottom: 8px; background-color: #fff; -webkit-transition: .4s; transition: .4s; border-radius: 68px}
    input:checked+.slider {background-color: #2196F3}
    input:checked+.slider:before {-webkit-transform: translateX(52px); -ms-transform: translateX(52px); transform: translateX(52px)}
  </style>

</style>
</head>
<body>
  <h2>CHARUSAT Alarm System</h2>
  <h3>Developed By: Mr. Maulik J. Shah (Assistant Professor, EE, CSPIT)</h3>
  <p>
    Date (DD:MM:YYYY) --- <span id="DATE1">%DATE1%</span><br>
    Time (HH:MM:SS)   --- <span id="TIME1">%TIME1%</span><br>
  </p>
  <script>function toggleCheckbox(element) {
  var xhr = new XMLHttpRequest();
  if(element.checked){ 
    xhr.open("GET", "/update?state=1", true); 
    document.getElementById("state").innerHTML = "ON";  
  }
  else { 
    xhr.open("GET", "/update?state=0", true); 
    document.getElementById("state").innerHTML = "OFF";      
  }
  xhr.send();
}</script>
  <br>
   <b> Last Set Alarms:</b><br>
   <span id="lastalarm">%lastalarm%</span><br>
   <span id="lastalarm1">%lastalarm%</span><br>
   <span id="lastalarm2">%lastalarm%</span><br>
   <span id="lastalarm3">%lastalarm%</span><br><br>

     <b>Note:<br> Enter ALARM in 24 hour format only. <br>
                For regular alarm set Start second 0 and End second 2,<br>
                For medium alarm set Start second 0 and End second 4, <br>
                For long alarm set Start second 0 and End second 6. </b><br><br>
<form action="/get">
<table>
  <tr>
    <th>ALARM No.</th>
    <th>Hour</th>
    <th>Minute</th>
    <th>Start Second</th>
    <th>End Second</th>
  </tr>
  <tr><td>1</td><td><input type="text" name="input101"></td><td><input type="text" name="input102"></td><td><input type="text" name="input103"></td><td><input type="text" name="input104"></td>
  <tr><td>2</td><td><input type="text" name="input201"></td><td><input type="text" name="input202"></td><td><input type="text" name="input203"></td><td><input type="text" name="input204"></td>
  <tr><td>3</td><td><input type="text" name="input301"></td><td><input type="text" name="input302"></td><td><input type="text" name="input303"></td><td><input type="text" name="input304"></td>
  <tr><td>4</td><td><input type="text" name="input401"></td><td><input type="text" name="input402"></td><td><input type="text" name="input403"></td><td><input type="text" name="input404"></td>
  <tr><td>5</td><td><input type="text" name="input501"></td><td><input type="text" name="input502"></td><td><input type="text" name="input503"></td><td><input type="text" name="input504"></td>
  <tr><td>6</td><td><input type="text" name="input601"></td><td><input type="text" name="input602"></td><td><input type="text" name="input603"></td><td><input type="text" name="input604"></td>
  <tr><td>7</td><td><input type="text" name="input701"></td><td><input type="text" name="input702"></td><td><input type="text" name="input703"></td><td><input type="text" name="input704"></td>
  <tr><td>8</td><td><input type="text" name="input801"></td><td><input type="text" name="input802"></td><td><input type="text" name="input803"></td><td><input type="text" name="input804"></td>
  <tr><td>9</td><td><input type="text" name="input901"></td><td><input type="text" name="input902"></td><td><input type="text" name="input903"></td><td><input type="text" name="input904"></td>
  <tr><td>10</td><td><input type="text" name="input1001"></td><td><input type="text" name="input1002"></td><td><input type="text" name="input1003"></td><td><input type="text" name="input1004"></td>
  <tr><td>11</td><td><input type="text" name="input1101"></td><td><input type="text" name="input1102"></td><td><input type="text" name="input1103"></td><td><input type="text" name="input1104"></td>
  <tr><td>12</td><td><input type="text" name="input1201"></td><td><input type="text" name="input1202"></td><td><input type="text" name="input1203"></td><td><input type="text" name="input1204"></td>
  <tr><td>13</td><td><input type="text" name="input1301"></td><td><input type="text" name="input1302"></td><td><input type="text" name="input1303"></td><td><input type="text" name="input1304"></td>
  <tr><td>14</td><td><input type="text" name="input1401"></td><td><input type="text" name="input1402"></td><td><input type="text" name="input1403"></td><td><input type="text" name="input1404"></td>
  <tr><td>15</td><td><input type="text" name="input1501"></td><td><input type="text" name="input1502"></td><td><input type="text" name="input1503"></td><td><input type="text" name="input1504"></td>
  <tr><td>16</td><td><input type="text" name="input1601"></td><td><input type="text" name="input1602"></td><td><input type="text" name="input1603"></td><td><input type="text" name="input1604"></td>
  <tr><td>17</td><td><input type="text" name="input1701"></td><td><input type="text" name="input1702"></td><td><input type="text" name="input1703"></td><td><input type="text" name="input1704"></td>
  <tr><td>18</td><td><input type="text" name="input1801"></td><td><input type="text" name="input1802"></td><td><input type="text" name="input1803"></td><td><input type="text" name="input1804"></td>
  <tr><td>19</td><td><input type="text" name="input1901"></td><td><input type="text" name="input1902"></td><td><input type="text" name="input1903"></td><td><input type="text" name="input1904"></td>
  <tr><td>20</td><td><input type="text" name="input2001"></td><td><input type="text" name="input2002"></td><td><input type="text" name="input2003"></td><td><input type="text" name="input2004"></td>

  </table>
  <br>
  <br>
  After filling required alarm times click on <b>Submit & Logout</b> button to save alarm time.</br></br>
  <button onclick="logoutButton()">Submit & Logout</button>
    </form> 
  <script>function logoutButton() 
  {
    var xhr = new XMLHttpRequest();
    xhr.open("GET", "/logout", true);
    xhr.send();
    setTimeout(function(){ window.open("/logged-out","_self"); }, 1000);
  }

setInterval(function ( ) {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("DATE1").innerHTML = this.responseText;
    }
  };
  xhttp.open("GET", "DATE1", true);
  xhttp.send();
}, 100 ) ;

setInterval(function ( ) {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("TIME1").innerHTML = this.responseText;
    }
  };
  xhttp.open("GET", "/TIME1", true);
  xhttp.send();
}, 100 ) ;

setInterval(function ( ) {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("day").innerHTML = this.responseText;
    }
  };
  xhttp.open("GET", "/day", true);
  xhttp.send();
}, 100 ) ;

setInterval(function ( ) {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("lastalarm").innerHTML = this.responseText;
    }
  };
  xhttp.open("GET", "/lastalarm", true);
  xhttp.send();
}, 100 ) ;

setInterval(function ( ) {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("lastalarm1").innerHTML = this.responseText;
    }
  };
  xhttp.open("GET", "/lastalarm1", true);
  xhttp.send();
}, 100 ) ;

setInterval(function ( ) {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("lastalarm2").innerHTML = this.responseText;
    }
  };
  xhttp.open("GET", "/lastalarm2", true);
  xhttp.send();
}, 100 ) ;

setInterval(function ( ) {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("lastalarm3").innerHTML = this.responseText;
    }
  };
  xhttp.open("GET", "/lastalarm3", true);
  xhttp.send();
}, 100 ) ;
  
  </script>
  <br>

</body>
</html>
)rawliteral";

void notFound(AsyncWebServerRequest *request) {
  request->send(404, "text/plain", "Not found");
}

const char logout_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html>
<head>
  <meta name="viewport" content="width=device-width, initial-scale=1">
</head>
<body>
  <p>Logged out. <br>All Alarm Saved successfully.</p><br>                                 
  <p><strong>Note:</strong> close all web browser tabs to complete the logout process.</p>
</body>
</html>
)rawliteral";


// Replaces placeholder with DHT values
String processor(const String& var){
  //Serial.println(var);

  if(var == "BUTTONPLACEHOLDER"){
    String buttons ="";
    String outputStateValue = outputState();
    buttons+= "<p><label class=\"switch\"><input type=\"checkbox\" onchange=\"toggleCheckbox(this)\" id=\"output\" " + outputStateValue + "><span class=\"slider\"></span></label></p>";
    return buttons;
  }
  if (var == "STATE"){
    if(digitalRead(output)){
      return "ON";
    }
    else {
      return "OFF";
    }
  }
  
  if(var == "DATE1"){
    return DATEStamp;
  }
  else if(var == "TIME1"){
    return TIMEStamp;
  }
    else if(var == "day"){
    return dayStamp;
  }
    else if(var == "lastalarm"){
    return temp;
  }
      else if(var == "lastalarm1"){
    return temp1;
  }
      else if(var == "lastalarm2"){
    return temp2;
  }
      else if(var == "lastalarm3"){
    return temp3;
  }
  return String();
}

String outputState(){
  if(digitalRead(output)){
    return "checked";
  }
  else {
    return "";
  }
  return "";
}


void setup()
{
  // Serial port for debugging purposes
  Serial.begin(115200);
  lcd.begin(16, 2);
  lcd.clear();
  pinMode(output, OUTPUT);
  digitalWrite(output, LOW);

  pinMode(alarmpin, OUTPUT);
  digitalWrite(alarmpin, LOW);
  
  EEPROM.begin(EEPROM_SIZE);
  a101=EEPROM.read(0);a102=EEPROM.read(1);a103=EEPROM.read(2);a104=EEPROM.read(3);
  a201=EEPROM.read(4);a202=EEPROM.read(5);a203=EEPROM.read(6);a204=EEPROM.read(7);
  a301=EEPROM.read(8);a302=EEPROM.read(9);a303=EEPROM.read(10);a304=EEPROM.read(11);
  a401=EEPROM.read(12);a402=EEPROM.read(13);a403=EEPROM.read(14);a404=EEPROM.read(15);
  a501=EEPROM.read(16);a502=EEPROM.read(17);a503=EEPROM.read(18);a504=EEPROM.read(19);
  a601=EEPROM.read(20);a602=EEPROM.read(21);a603=EEPROM.read(22);a604=EEPROM.read(23);
  a701=EEPROM.read(24);a702=EEPROM.read(25);a703=EEPROM.read(26);a704=EEPROM.read(27);
  a801=EEPROM.read(28);a802=EEPROM.read(29);a803=EEPROM.read(30);a804=EEPROM.read(31);
  a901=EEPROM.read(32);a902=EEPROM.read(33);a903=EEPROM.read(34);a904=EEPROM.read(35);
  a1001=EEPROM.read(36);a1002=EEPROM.read(37);a1003=EEPROM.read(38);a1004=EEPROM.read(39);
  a1101=EEPROM.read(40);a1102=EEPROM.read(41);a1103=EEPROM.read(42);a1104=EEPROM.read(43);
  a1201=EEPROM.read(44);a1202=EEPROM.read(45);a1203=EEPROM.read(46);a1204=EEPROM.read(47);
  a1301=EEPROM.read(48);a1302=EEPROM.read(49);a1303=EEPROM.read(50);a1304=EEPROM.read(51);
  a1401=EEPROM.read(52);a1402=EEPROM.read(53);a1403=EEPROM.read(54);a1404=EEPROM.read(55);
  a1501=EEPROM.read(56);a1502=EEPROM.read(57);a1503=EEPROM.read(58);a1504=EEPROM.read(59);
  a1601=EEPROM.read(60);a1602=EEPROM.read(61);a1603=EEPROM.read(62);a1604=EEPROM.read(63);
  a1701=EEPROM.read(64);a1702=EEPROM.read(65);a1703=EEPROM.read(66);a1704=EEPROM.read(67);
  a1801=EEPROM.read(68);a1802=EEPROM.read(69);a1803=EEPROM.read(70);a1804=EEPROM.read(71);
  a1901=EEPROM.read(72);a1902=EEPROM.read(73);a1903=EEPROM.read(74);a1904=EEPROM.read(75);
  a2001=EEPROM.read(76);a2002=EEPROM.read(77);a2003=EEPROM.read(78);a2004=EEPROM.read(79);
  
  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
    lcd.setCursor(0, 0);
    lcd.print("Connect..WiFi...");
  }

  // Print ESP Local IP Address
  Serial.println(WiFi.localIP());
  lcd.setCursor(0, 1);
  lcd.print(WiFi.localIP());
  // Initialize a NTPClient to get time
  timeClient.begin();
  // Set offset time in seconds to adjust for your timezone, for example:
  // GMT +1 = 3600
  // GMT +8 = 28800
  // GMT -1 = -3600
  // GMT 0 = 0
  timeClient.setTimeOffset(19800);

  // Route for root / web page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    if(!request->authenticate(http_username, http_password))
      return request->requestAuthentication();
    request->send_P(200, "text/html", index_html);
  });
    
  server.on("/logout", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(401);
  });

  server.on("/logged-out", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", logout_html);
  });

  // Send a GET request to <ESP_IP>/update?state=<inputMessage>
  server.on("/update", HTTP_GET, [] (AsyncWebServerRequest *request) {
    if(!request->authenticate(http_username, http_password))
      return request->requestAuthentication();

    String inputMessage;
    String inputParam;
    // GET input1 value on <ESP_IP>/update?state=<inputMessage>
    if (request->hasParam(PARAM_INPUT_S)) {
      inputMessage = request->getParam(PARAM_INPUT_S)->value();
      inputParam = PARAM_INPUT_S;
      digitalWrite(output, inputMessage.toInt());
    }
    else {
      inputMessage = "No message sent";
      inputParam = "none";
    }

    
  });

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", index_html, processor);
  });

  server.on("/DATE1", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", DATEStamp.c_str());
  });
    server.on("/TIME1", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", TIMEStamp.c_str());
  });

      server.on("/day", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", dayStamp.c_str());
  });
    server.on("/lastalarm", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", temp.c_str());
  });
      server.on("/lastalarm1", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", temp1.c_str());
  });
      server.on("/lastalarm2", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", temp2.c_str());
  });
      server.on("/lastalarm3", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", temp3.c_str());
  });

    // Send a GET request to <ESP_IP>/get?input1=<inputMessage>
  server.on("/get", HTTP_GET, [] (AsyncWebServerRequest *request) 
  {

    // GET input1 value on <ESP_IP>/get?input1=<inputMessage>
    if (request->hasParam(PARAM_INPUT_101)) {inputMessage101 = request->getParam(PARAM_INPUT_101)->value();a101=inputMessage101.toInt();}
    if (request->hasParam(PARAM_INPUT_102)) {inputMessage102 = request->getParam(PARAM_INPUT_102)->value();a102=inputMessage102.toInt();}
    if (request->hasParam(PARAM_INPUT_103)) {inputMessage103 = request->getParam(PARAM_INPUT_103)->value();a103=inputMessage103.toInt();}
    if (request->hasParam(PARAM_INPUT_104)) {inputMessage104 = request->getParam(PARAM_INPUT_104)->value();a104=inputMessage104.toInt();}
    if (request->hasParam(PARAM_INPUT_201)) {inputMessage201 = request->getParam(PARAM_INPUT_201)->value();a201=inputMessage201.toInt();}
    if (request->hasParam(PARAM_INPUT_202)) {inputMessage202 = request->getParam(PARAM_INPUT_202)->value();a202=inputMessage202.toInt();}
    if (request->hasParam(PARAM_INPUT_203)) {inputMessage203 = request->getParam(PARAM_INPUT_203)->value();a203=inputMessage203.toInt();}
    if (request->hasParam(PARAM_INPUT_204)) {inputMessage204 = request->getParam(PARAM_INPUT_204)->value();a204=inputMessage204.toInt();}
    if (request->hasParam(PARAM_INPUT_301)) {inputMessage301= request->getParam(PARAM_INPUT_301)->value();a301=inputMessage301.toInt();}
    if (request->hasParam(PARAM_INPUT_302)) {inputMessage302= request->getParam(PARAM_INPUT_302)->value();a302=inputMessage302.toInt();}
    if (request->hasParam(PARAM_INPUT_303)) {inputMessage303= request->getParam(PARAM_INPUT_303)->value();a303=inputMessage303.toInt();}
    if (request->hasParam(PARAM_INPUT_304)) {inputMessage304= request->getParam(PARAM_INPUT_304)->value();a304=inputMessage304.toInt();}
    if (request->hasParam(PARAM_INPUT_401)) {inputMessage401= request->getParam(PARAM_INPUT_401)->value();a401=inputMessage401.toInt();}
    if (request->hasParam(PARAM_INPUT_402)) {inputMessage402= request->getParam(PARAM_INPUT_402)->value();a402=inputMessage402.toInt();}
    if (request->hasParam(PARAM_INPUT_403)) {inputMessage403= request->getParam(PARAM_INPUT_403)->value();a403=inputMessage403.toInt();}
    if (request->hasParam(PARAM_INPUT_404)) {inputMessage404= request->getParam(PARAM_INPUT_404)->value();a404=inputMessage404.toInt();}
    if (request->hasParam(PARAM_INPUT_501)) {inputMessage501= request->getParam(PARAM_INPUT_501)->value();a501=inputMessage501.toInt();}
    if (request->hasParam(PARAM_INPUT_502)) {inputMessage502= request->getParam(PARAM_INPUT_502)->value();a502=inputMessage502.toInt();}
    if (request->hasParam(PARAM_INPUT_503)) {inputMessage503= request->getParam(PARAM_INPUT_503)->value();a503=inputMessage503.toInt();}
    if (request->hasParam(PARAM_INPUT_504)) {inputMessage504= request->getParam(PARAM_INPUT_504)->value();a504=inputMessage504.toInt();}
    if (request->hasParam(PARAM_INPUT_601)) {inputMessage601= request->getParam(PARAM_INPUT_601)->value();a601=inputMessage601.toInt();}
    if (request->hasParam(PARAM_INPUT_602)) {inputMessage602= request->getParam(PARAM_INPUT_602)->value();a602=inputMessage602.toInt();}
    if (request->hasParam(PARAM_INPUT_603)) {inputMessage603= request->getParam(PARAM_INPUT_603)->value();a603=inputMessage603.toInt();}
    if (request->hasParam(PARAM_INPUT_604)) {inputMessage604= request->getParam(PARAM_INPUT_604)->value();a604=inputMessage604.toInt();}
    if (request->hasParam(PARAM_INPUT_701)) {inputMessage701= request->getParam(PARAM_INPUT_701)->value();a701=inputMessage701.toInt();}
    if (request->hasParam(PARAM_INPUT_702)) {inputMessage702= request->getParam(PARAM_INPUT_702)->value();a702=inputMessage702.toInt();}
    if (request->hasParam(PARAM_INPUT_703)) {inputMessage703= request->getParam(PARAM_INPUT_703)->value();a703=inputMessage703.toInt();}
    if (request->hasParam(PARAM_INPUT_704)) {inputMessage704= request->getParam(PARAM_INPUT_704)->value();a704=inputMessage704.toInt();}
    if (request->hasParam(PARAM_INPUT_801)) {inputMessage801= request->getParam(PARAM_INPUT_801)->value();a801=inputMessage801.toInt();}
    if (request->hasParam(PARAM_INPUT_802)) {inputMessage802= request->getParam(PARAM_INPUT_802)->value();a802=inputMessage802.toInt();}
    if (request->hasParam(PARAM_INPUT_803)) {inputMessage803= request->getParam(PARAM_INPUT_803)->value();a803=inputMessage803.toInt();}
    if (request->hasParam(PARAM_INPUT_804)) {inputMessage804= request->getParam(PARAM_INPUT_804)->value();a804=inputMessage804.toInt();}
    if (request->hasParam(PARAM_INPUT_901)) {inputMessage901= request->getParam(PARAM_INPUT_901)->value();a901=inputMessage901.toInt();}
    if (request->hasParam(PARAM_INPUT_902)) {inputMessage902= request->getParam(PARAM_INPUT_902)->value();a902=inputMessage902.toInt();}
    if (request->hasParam(PARAM_INPUT_903)) {inputMessage903= request->getParam(PARAM_INPUT_903)->value();a903=inputMessage903.toInt();}
    if (request->hasParam(PARAM_INPUT_904)) {inputMessage904= request->getParam(PARAM_INPUT_904)->value();a904=inputMessage904.toInt();}
    if (request->hasParam(PARAM_INPUT_1001)) {inputMessage1001= request->getParam(PARAM_INPUT_1001)->value();a1001=inputMessage1001.toInt();}
    if (request->hasParam(PARAM_INPUT_1002)) {inputMessage1002= request->getParam(PARAM_INPUT_1002)->value();a1002=inputMessage1002.toInt();}
    if (request->hasParam(PARAM_INPUT_1003)) {inputMessage1003= request->getParam(PARAM_INPUT_1003)->value();a1003=inputMessage1003.toInt();}
    if (request->hasParam(PARAM_INPUT_1004)) {inputMessage1004= request->getParam(PARAM_INPUT_1004)->value();a1004=inputMessage1004.toInt();}
    if (request->hasParam(PARAM_INPUT_1101)) {inputMessage1101= request->getParam(PARAM_INPUT_1101)->value();a1101=inputMessage1101.toInt();}
    if (request->hasParam(PARAM_INPUT_1102)) {inputMessage1102= request->getParam(PARAM_INPUT_1102)->value();a1102=inputMessage1102.toInt();}
    if (request->hasParam(PARAM_INPUT_1103)) {inputMessage1103= request->getParam(PARAM_INPUT_1103)->value();a1103=inputMessage1103.toInt();}
    if (request->hasParam(PARAM_INPUT_1104)) {inputMessage1104= request->getParam(PARAM_INPUT_1104)->value();a1104=inputMessage1104.toInt();}
    if (request->hasParam(PARAM_INPUT_1201)) {inputMessage1201= request->getParam(PARAM_INPUT_1201)->value();a1201=inputMessage1201.toInt();}
    if (request->hasParam(PARAM_INPUT_1202)) {inputMessage1202= request->getParam(PARAM_INPUT_1202)->value();a1202=inputMessage1202.toInt();}
    if (request->hasParam(PARAM_INPUT_1203)) {inputMessage1203= request->getParam(PARAM_INPUT_1203)->value();a1203=inputMessage1203.toInt();}
    if (request->hasParam(PARAM_INPUT_1204)) {inputMessage1204= request->getParam(PARAM_INPUT_1204)->value();a1204=inputMessage1204.toInt();}
    if (request->hasParam(PARAM_INPUT_1301)) {inputMessage1301= request->getParam(PARAM_INPUT_1301)->value();a1301=inputMessage1301.toInt();}
    if (request->hasParam(PARAM_INPUT_1302)) {inputMessage1302= request->getParam(PARAM_INPUT_1302)->value();a1302=inputMessage1302.toInt();}
    if (request->hasParam(PARAM_INPUT_1303)) {inputMessage1303= request->getParam(PARAM_INPUT_1303)->value();a1303=inputMessage1303.toInt();}
    if (request->hasParam(PARAM_INPUT_1304)) {inputMessage1304= request->getParam(PARAM_INPUT_1304)->value();a1304=inputMessage1304.toInt();}
    if (request->hasParam(PARAM_INPUT_1401)) {inputMessage1401= request->getParam(PARAM_INPUT_1401)->value();a1401=inputMessage1401.toInt();}
    if (request->hasParam(PARAM_INPUT_1402)) {inputMessage1402= request->getParam(PARAM_INPUT_1402)->value();a1402=inputMessage1402.toInt();}
    if (request->hasParam(PARAM_INPUT_1403)) {inputMessage1403= request->getParam(PARAM_INPUT_1403)->value();a1403=inputMessage1403.toInt();}
    if (request->hasParam(PARAM_INPUT_1404)) {inputMessage1404= request->getParam(PARAM_INPUT_1404)->value();a1404=inputMessage1404.toInt();}
    if (request->hasParam(PARAM_INPUT_1501)) {inputMessage1501= request->getParam(PARAM_INPUT_1501)->value();a1501=inputMessage1501.toInt();}
    if (request->hasParam(PARAM_INPUT_1502)) {inputMessage1502= request->getParam(PARAM_INPUT_1502)->value();a1502=inputMessage1502.toInt();}
    if (request->hasParam(PARAM_INPUT_1503)) {inputMessage1503= request->getParam(PARAM_INPUT_1503)->value();a1503=inputMessage1503.toInt();}
    if (request->hasParam(PARAM_INPUT_1504)) {inputMessage1504= request->getParam(PARAM_INPUT_1504)->value();a1504=inputMessage1504.toInt();}
    if (request->hasParam(PARAM_INPUT_1601)) {inputMessage1601= request->getParam(PARAM_INPUT_1601)->value();a1601=inputMessage1601.toInt();}
    if (request->hasParam(PARAM_INPUT_1602)) {inputMessage1602= request->getParam(PARAM_INPUT_1602)->value();a1602=inputMessage1602.toInt();}
    if (request->hasParam(PARAM_INPUT_1603)) {inputMessage1603= request->getParam(PARAM_INPUT_1603)->value();a1603=inputMessage1603.toInt();}
    if (request->hasParam(PARAM_INPUT_1604)) {inputMessage1604= request->getParam(PARAM_INPUT_1604)->value();a1604=inputMessage1604.toInt();}
    if (request->hasParam(PARAM_INPUT_1701)) {inputMessage1701= request->getParam(PARAM_INPUT_1701)->value();a1701=inputMessage1701.toInt();}
    if (request->hasParam(PARAM_INPUT_1702)) {inputMessage1702= request->getParam(PARAM_INPUT_1702)->value();a1702=inputMessage1702.toInt();}
    if (request->hasParam(PARAM_INPUT_1703)) {inputMessage1703= request->getParam(PARAM_INPUT_1703)->value();a1703=inputMessage1703.toInt();}
    if (request->hasParam(PARAM_INPUT_1704)) {inputMessage1704= request->getParam(PARAM_INPUT_1704)->value();a1704=inputMessage1704.toInt();}
    if (request->hasParam(PARAM_INPUT_1801)) {inputMessage1801= request->getParam(PARAM_INPUT_1801)->value();a1801=inputMessage1801.toInt();}
    if (request->hasParam(PARAM_INPUT_1802)) {inputMessage1802= request->getParam(PARAM_INPUT_1802)->value();a1802=inputMessage1802.toInt();}
    if (request->hasParam(PARAM_INPUT_1803)) {inputMessage1803= request->getParam(PARAM_INPUT_1803)->value();a1803=inputMessage1803.toInt();}
    if (request->hasParam(PARAM_INPUT_1804)) {inputMessage1804= request->getParam(PARAM_INPUT_1804)->value();a1804=inputMessage1804.toInt();}
    if (request->hasParam(PARAM_INPUT_1901)) {inputMessage1901= request->getParam(PARAM_INPUT_1901)->value();a1901=inputMessage1901.toInt();}
    if (request->hasParam(PARAM_INPUT_1902)) {inputMessage1902= request->getParam(PARAM_INPUT_1902)->value();a1902=inputMessage1902.toInt();}
    if (request->hasParam(PARAM_INPUT_1903)) {inputMessage1903= request->getParam(PARAM_INPUT_1903)->value();a1903=inputMessage1903.toInt();}
    if (request->hasParam(PARAM_INPUT_1904)) {inputMessage1904= request->getParam(PARAM_INPUT_1904)->value();a1904=inputMessage1904.toInt();}
    if (request->hasParam(PARAM_INPUT_2001)) {inputMessage2001= request->getParam(PARAM_INPUT_2001)->value();a2001=inputMessage2001.toInt();}
    if (request->hasParam(PARAM_INPUT_2002)) {inputMessage2002= request->getParam(PARAM_INPUT_2002)->value();a2002=inputMessage2002.toInt();}
    if (request->hasParam(PARAM_INPUT_2003)) {inputMessage2003= request->getParam(PARAM_INPUT_2003)->value();a2003=inputMessage2003.toInt();}
    if (request->hasParam(PARAM_INPUT_2004)) {inputMessage2004= request->getParam(PARAM_INPUT_2004)->value();a2004=inputMessage2004.toInt();}

    EEPROM.write(0,a101);EEPROM.write(1,a102);EEPROM.write(2,a103);EEPROM.write(3,a104);
    EEPROM.write(4,a201);EEPROM.write(5,a202);EEPROM.write(6,a203);EEPROM.write(7,a204);
    EEPROM.write(8,a301);EEPROM.write(9,a302);EEPROM.write(10,a303);EEPROM.write(11,a304);
    EEPROM.write(12,a401);EEPROM.write(13,a402);EEPROM.write(14,a403);EEPROM.write(15,a404);
    EEPROM.write(16,a501);EEPROM.write(17,a502);EEPROM.write(18,a503);EEPROM.write(19,a504);
    EEPROM.write(20,a601);EEPROM.write(21,a602);EEPROM.write(22,a603);EEPROM.write(23,a604);
    EEPROM.write(24,a701);EEPROM.write(25,a702);EEPROM.write(26,a703);EEPROM.write(27,a704);
    EEPROM.write(28,a801);EEPROM.write(29,a802);EEPROM.write(30,a803);EEPROM.write(31,a804);
    EEPROM.write(32,a901);EEPROM.write(33,a902);EEPROM.write(34,a903);EEPROM.write(35,a904);
    EEPROM.write(36,a1001);EEPROM.write(37,a1002);EEPROM.write(38,a1003);EEPROM.write(39,a1004);
    EEPROM.write(40,a1101);EEPROM.write(41,a1102);EEPROM.write(42,a1103);EEPROM.write(43,a1104);
    EEPROM.write(44,a1201);EEPROM.write(45,a1202);EEPROM.write(46,a1203);EEPROM.write(47,a1204);
    EEPROM.write(48,a1301);EEPROM.write(49,a1302);EEPROM.write(50,a1303);EEPROM.write(51,a1304);
    EEPROM.write(52,a1401);EEPROM.write(53,a1402);EEPROM.write(54,a1403);EEPROM.write(55,a1404);
    EEPROM.write(56,a1501);EEPROM.write(57,a1502);EEPROM.write(58,a1503);EEPROM.write(59,a1504);
    EEPROM.write(60,a1601);EEPROM.write(61,a1602);EEPROM.write(62,a1603);EEPROM.write(63,a1604);
    EEPROM.write(64,a1701);EEPROM.write(65,a1702);EEPROM.write(66,a1703);EEPROM.write(67,a1704);
    EEPROM.write(68,a1801);EEPROM.write(69,a1802);EEPROM.write(70,a1803);EEPROM.write(71,a1804);
    EEPROM.write(72,a1901);EEPROM.write(73,a1902);EEPROM.write(74,a1903);EEPROM.write(75,a1904);
    EEPROM.write(76,a2001);EEPROM.write(77,a2002);EEPROM.write(78,a2003);EEPROM.write(79,a2004);
    EEPROM.commit();
    request->send(200, "text/html","Your Set Alarms (HH:MM:SS:SS)in 24 hour format:-<br>"
                                  "A01:---"+inputMessage101+":"+inputMessage102+":"+inputMessage103+":"+inputMessage104+",<br>" 
                                  "A02:---"+inputMessage201+":"+inputMessage202+":"+inputMessage203+":"+inputMessage204+",<br>"
                                  "A03:---"+inputMessage301+":"+inputMessage302+":"+inputMessage303+":"+inputMessage304+",<br>"
                                  "A04:---"+inputMessage401+":"+inputMessage402+":"+inputMessage403+":"+inputMessage404+",<br>"
                                  "A05:---"+inputMessage501+":"+inputMessage502+":"+inputMessage503+":"+inputMessage504+",<br>"
                                  "A06:---"+inputMessage601+":"+inputMessage602+":"+inputMessage603+":"+inputMessage604+",<br>"
                                  "A07:---"+inputMessage701+":"+inputMessage702+":"+inputMessage703+":"+inputMessage704+",<br>"
                                  "A08:---"+inputMessage801+":"+inputMessage802+":"+inputMessage803+":"+inputMessage804+",<br>"
                                  "A09:---"+inputMessage901+":"+inputMessage902+":"+inputMessage903+":"+inputMessage904+",<br>"
                                  "A10:---"+inputMessage1001+":"+inputMessage1002+":"+inputMessage1003+":"+inputMessage1004+",<br>"
                                  "A11:---"+inputMessage1101+":"+inputMessage1102+":"+inputMessage1103+":"+inputMessage1104+",<br>"
                                  "A12:---"+inputMessage1201+":"+inputMessage1202+":"+inputMessage1203+":"+inputMessage1204+",<br>"
                                  "A13:---"+inputMessage1301+":"+inputMessage1302+":"+inputMessage1303+":"+inputMessage1304+",<br>"
                                  "A14:---"+inputMessage1401+":"+inputMessage1402+":"+inputMessage1403+":"+inputMessage1404+",<br>"
                                  "A15:---"+inputMessage1501+":"+inputMessage1502+":"+inputMessage1503+":"+inputMessage1504+",<br>"
                                  "A16:---"+inputMessage1601+":"+inputMessage1602+":"+inputMessage1603+":"+inputMessage1604+",<br>"
                                  "A17:---"+inputMessage1701+":"+inputMessage1702+":"+inputMessage1703+":"+inputMessage1704+",<br>"
                                  "A18:---"+inputMessage1801+":"+inputMessage1802+":"+inputMessage1803+":"+inputMessage1804+",<br>"
                                  "A19:---"+inputMessage1901+":"+inputMessage1902+":"+inputMessage1903+":"+inputMessage1904+",<br>"
                                  "A20:---"+inputMessage2001+":"+inputMessage2002+":"+inputMessage2003+":"+inputMessage2004+"<br><br>"
                                  "<b> Close this Tab for security purpose.</b>"
                                  );
  // Start server
  });
  server.onNotFound(notFound);
  server.begin();
}
  
void loop() 
{
  temp =String("A1=")+String(a101)+String(":")+String(a102)+String(":")+String(a103)+String(":")+String(a104)+String(",  ")+
        String("A2=")+String(a201)+String(":")+String(a202)+String(":")+String(a203)+String(":")+String(a204)+String(",  ")+
        String("A3=")+String(a301)+String(":")+String(a302)+String(":")+String(a303)+String(":")+String(a304)+String(",  ")+
        String("A4=")+String(a401)+String(":")+String(a402)+String(":")+String(a403)+String(":")+String(a404)+String(",  ")+
        String("A5=")+String(a501)+String(":")+String(a502)+String(":")+String(a503)+String(":")+String(a504);
  temp1=String("A6=")+String(a601)+String(":")+String(a602)+String(":")+String(a603)+String(":")+String(a604)+String(",  ")+
        String("A7=")+String(a701)+String(":")+String(a702)+String(":")+String(a703)+String(":")+String(a704)+String(",  ")+
        String("A8=")+String(a801)+String(":")+String(a802)+String(":")+String(a803)+String(":")+String(a804)+String(",  ")+
        String("A9=")+String(a901)+String(":")+String(a902)+String(":")+String(a903)+String(":")+String(a904)+String(",  ")+
        String("A10=")+String(a1001)+String(":")+String(a1002)+String(":")+String(a1003)+String(":")+String(a1004);
  temp2=String("A11=")+String(a1101)+String(":")+String(a1102)+String(":")+String(a1103)+String(":")+String(a1104)+String(",  ")+
        String("A12=")+String(a1201)+String(":")+String(a1202)+String(":")+String(a1203)+String(":")+String(a1204)+String(",  ")+
        String("A13=")+String(a1301)+String(":")+String(a1302)+String(":")+String(a1303)+String(":")+String(a1304)+String(",  ")+
        String("A14=")+String(a1401)+String(":")+String(a1402)+String(":")+String(a1403)+String(":")+String(a1404)+String(",  ")+
        String("A15=")+String(a1501)+String(":")+String(a1502)+String(":")+String(a1503)+String(":")+String(a1504);
  temp3=String("A16=")+String(a1601)+String(":")+String(a1602)+String(":")+String(a1603)+String(":")+String(a1604)+String(",  ")+
        String("A17=")+String(a1701)+String(":")+String(a1702)+String(":")+String(a1703)+String(":")+String(a1704)+String(",  ")+
        String("A18=")+String(a1801)+String(":")+String(a1802)+String(":")+String(a1803)+String(":")+String(a1804)+String(",  ")+
        String("A19=")+String(a1901)+String(":")+String(a1902)+String(":")+String(a1903)+String(":")+String(a1904)+String(",  ")+
        String("A20=")+String(a2001)+String(":")+String(a2002)+String(":")+String(a2003)+String(":")+String(a2004);
//    Serial.print(a101);Serial.print(" ");Serial.print(a102);Serial.print(" ");Serial.print(a103);Serial.print(" ");Serial.print(a104);Serial.println(" ");
//    Serial.print(a201);Serial.print(" ");Serial.print(a202);Serial.print(" ");Serial.print(a203);Serial.print(" ");Serial.print(a204);Serial.println(" ");
    //Serial.println(temp);
      while(!timeClient.update()) {
    timeClient.forceUpdate();
  }
  // The formattedDate comes with the following format:
  // 2018-05-28T16:00:13Z
  // We need to extract date and time
  formattedDate = timeClient.getFormattedDate();
  dayStamp1 = timeClient.getDay();
  dayint = dayStamp1.toInt();
  if(dayint==0)dayStamp="SUNDAY";if(dayint==1)dayStamp="MONDAY";if(dayint==2)dayStamp="TUESDAY";if(dayint==3)dayStamp="WEDNESDAY";
  if(dayint==4)dayStamp="THURSDAY";if(dayint==5)dayStamp="FRIDAY";if(dayint==6)dayStamp="SATURDAY";
  // Extract DD/MM/YYYY
  int splitT = formattedDate.indexOf("T");
  DDStamp = formattedDate.substring(splitT-2, splitT);
  DDint = DDStamp.toInt();
  MMStamp = formattedDate.substring(splitT-5, splitT-3);
  MMint = MMStamp.toInt();
  YYYYStamp = formattedDate.substring(0, splitT-6);
  YYYYint = YYYYStamp.toInt();
  DATEStamp = String(DDStamp+":"+MMStamp+":"+YYYYStamp);
//  Serial.print("DATE:");
//  Serial.print(DDint);
//  Serial.print("-");
//  Serial.print(MMint);
//  Serial.print("-");
//  Serial.println(YYYYint);

  // Extract time HH/MM/SS
  TIMEStamp = formattedDate.substring(splitT+1, splitT+9);
  HH1int = HH1Stamp.toInt();
  HH1Stamp = formattedDate.substring(splitT+1, splitT+3);
  HH1int = HH1Stamp.toInt();
  MM1Stamp = formattedDate.substring(splitT+4, splitT+6);
  MM1int = MM1Stamp.toInt();
  SS1Stamp = formattedDate.substring(splitT+7, splitT+9);
  SS1int = SS1Stamp.toInt();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("DATE:");lcd.print(DDint);lcd.print("-");lcd.print(MMint);lcd.print("-");lcd.print(YYYYint);
  lcd.setCursor(0, 1);
  lcd.print("TIME:");lcd.print(HH1int);lcd.print(":");lcd.print(MM1int);lcd.print(":");lcd.print(SS1int);
  //Serial.print("TIME:");
  //Serial.print(HH1int);
  //Serial.print(":");
  //Serial.print(MM1int);
  //Serial.print(":");
  //Serial.println(SS1int);
  //Serial.print("HH1=");Serial.println(a101);Serial.print("MM1=");Serial.println(a102);Serial.print("SS1=");Serial.println(a103);Serial.print("SS2=");Serial.println(a104);
  if(HH1int==a101 && MM1int==a102 && SS1int>=a103 && SS1int<a104)digitalWrite(alarmpin,HIGH);
     else if(HH1int==a201 && MM1int==a202 && SS1int>=a203 && SS1int<a204)digitalWrite(alarmpin,HIGH);
     else if(HH1int==a201 && MM1int==a202 && SS1int>=a203 && SS1int<a204)digitalWrite(alarmpin,HIGH);
      else if(HH1int==a301 && MM1int==a302 && SS1int>=a303 && SS1int<a304)digitalWrite(alarmpin,HIGH);
      else if(HH1int==a401 && MM1int==a402 && SS1int>=a403 && SS1int<a404)digitalWrite(alarmpin,HIGH);
      else if(HH1int==a501 && MM1int==a502 && SS1int>=a503 && SS1int<a504)digitalWrite(alarmpin,HIGH);
      else if(HH1int==a601 && MM1int==a602 && SS1int>=a603 && SS1int<a604)digitalWrite(alarmpin,HIGH);
      else if(HH1int==a701 && MM1int==a702 && SS1int>=a703 && SS1int<a704)digitalWrite(alarmpin,HIGH);
      else if(HH1int==a801 && MM1int==a802 && SS1int>=a803 && SS1int<a804)digitalWrite(alarmpin,HIGH);
      else if(HH1int==a901 && MM1int==a902 && SS1int>=a903 && SS1int<a904)digitalWrite(alarmpin,HIGH);
      else if(HH1int==a1001 && MM1int==a1002 && SS1int>=a1003 && SS1int<a1004)digitalWrite(alarmpin,HIGH);
      else if(HH1int==a1101 && MM1int==a1102 && SS1int>=a1103 && SS1int<a1104)digitalWrite(alarmpin,HIGH);
      else if(HH1int==a1201 && MM1int==a1202 && SS1int>=a1203 && SS1int<a1204)digitalWrite(alarmpin,HIGH);
      else if(HH1int==a1301 && MM1int==a1302 && SS1int>=a1303 && SS1int<a1304)digitalWrite(alarmpin,HIGH);
      else if(HH1int==a1401 && MM1int==a1402 && SS1int>=a1403 && SS1int<a1404)digitalWrite(alarmpin,HIGH);
      else if(HH1int==a1501 && MM1int==a1502 && SS1int>=a1503 && SS1int<a1504)digitalWrite(alarmpin,HIGH);
      else if(HH1int==a1601 && MM1int==a1602 && SS1int>=a1603 && SS1int<a1604)digitalWrite(alarmpin,HIGH);
      else if(HH1int==a1701 && MM1int==a1702 && SS1int>=a1703 && SS1int<a1704)digitalWrite(alarmpin,HIGH);
      else if(HH1int==a1801 && MM1int==a1802 && SS1int>=a1803 && SS1int<a1804)digitalWrite(alarmpin,HIGH);
      else if(HH1int==a1901 && MM1int==a1902 && SS1int>=a1903 && SS1int<a1904)digitalWrite(alarmpin,HIGH);
      else if(HH1int==a2001 && MM1int==a2002 && SS1int>=a2003 && SS1int<a2004)digitalWrite(alarmpin,HIGH);
     else digitalWrite(alarmpin,LOW);
  delay(1000);
  if(MM1int==17 && SS1int==0)ESP.restart();
  if(MM1int==47 && SS1int==0)ESP.restart();
}

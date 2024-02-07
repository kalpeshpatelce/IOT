// Include required libraries
#include <ESP8266WiFi.h>
#include <Ticker.h>

// Define constants
const char* ssid = "kalpeshRT";
const char* password = "87654321";
const int LED_PIN = D1; // Change to the desired pin number
const int START_HOUR = 7; // Change to the desired start hour (24-hour format)
const int STOP_HOUR = 19; // Change to the desired stop hour (24-hour format)

// Define the Ticker object and the state variable
Ticker timer;
bool isOn = false;

void setup() {
  // Initialize serial communication
  Serial.begin(9600);
  
  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to ");
  Serial.print(ssid);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println(" connected");
  
  // Set the LED pin as output
  pinMode(LED_PIN, OUTPUT);
  
  // Start the timer
  timer.attach(1.0, timerCallback);
}

void loop() {
  // Nothing to do here
}

void timerCallback() {
  // Get the current time
  time_t now = time(nullptr);
  struct tm* timeinfo = localtime(&now);
  Serial.println(now);
  Serial.println(timeinfo->tm_hour);
  // Check if it's within the desired time range
  if (timeinfo->tm_hour >= START_HOUR && timeinfo->tm_hour < STOP_HOUR) {
    // Check if the LED is off and turn it on
    if (!isOn) {
      digitalWrite(LED_PIN, HIGH);
      isOn = true;
    }
  } else {
    // Check if the LED is on and turn it off
    if (isOn) {
      digitalWrite(LED_PIN, LOW);
      isOn = false;
    }
  }
}

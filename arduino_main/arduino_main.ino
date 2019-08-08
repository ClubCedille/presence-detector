#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

/*
 * File confidential.h contains the ssid and password required to
 * connect to a wifi network. They are kept seperate from the source
 * code as they must stay private. DO NOT PUSH THEM TO GITHUB.
 */
#include "confidential.h"

#define LIGHT_SIGNAL_INPUT 5 // pin D1

int previousLightStatus = -1;
HTTPClient client;

void connectToWifi(char* ssid, char* password)
{
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  int i = 0;
  while(!isConnectedToWiFi())
  {
    delay(1000);
    i++;
    if(i>=30) // Fails after thirty seconds.
    {
      return;
    }
  }
}

void flashForError()
{
  for(int i=0; i<19; i++)
  {
    digitalWrite(LED_BUILTIN, LOW); // LED is on.
    delay(100);
    digitalWrite(LED_BUILTIN, HIGH); // LED is off.
    delay(100);
  }
}

int getLightStatus() {return digitalRead(LIGHT_SIGNAL_INPUT);}

int invertDigitalState(int state) {return state==HIGH? LOW: HIGH;}

bool isConnectedToWiFi() {return WiFi.status()==WL_CONNECTED;}

bool lightIsDetected() {return getLightStatus()==HIGH;}

void sendLightStatus(int status)
{
  String path("http://presence.cedille.club/api/status/");
  client.begin(path + status);
  client.addHeader("Content-Type", "text/plain");
  client.POST("POST request from light detector");
  client.end();
}

void setup()
{
  Serial.begin(115200);
  pinMode(LIGHT_SIGNAL_INPUT, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  connectToWifi(SSID, PASSWORD);
}

void loop()
{
  int lightStatus = getLightStatus();
  if(!isConnectedToWiFi())
  {
    flashForError();
  }
  else if(lightStatus!=previousLightStatus)
  {
    digitalWrite(LED_BUILTIN, invertDigitalState(lightStatus)); // LED state is inverted.
    sendLightStatus(lightStatus);
    previousLightStatus = lightStatus;
  }
  delay(500);
}

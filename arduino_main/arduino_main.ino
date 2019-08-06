#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

/*
 * File wifiConnection.h contains the ssid and password required to
 * connect to a wifi network. They are kept seperate from the source
 * code as they must stay confidential. DO NOT PUSH THEM TO GITHUB.
 */
#include "confidential.h"

#define LIGHT_SIGNAL_INPUT 5 // pin D1
#define HOST "aquinas.xyz"
#define HTTPS_PORT 443
#define PATH "/club/api.php"

int previousSignal = -1;

HTTPClient client;

void connectToWifi(char* ssid, char* password)
{
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  int i=0;
  while(WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
    if(i>=60) // Fails after one minute.
    {
      return;
    }
  }
}

int getLightStatus() {return digitalRead(LIGHT_SIGNAL_INPUT);}

int invertDigitalState(int state) {return state==HIGH? LOW: HIGH;}

bool lightIsDetected() {return getLightStatus() == HIGH;}

void sendLightStatus(int status)
{
  String path("http://presence.cedille.club/api/status/");
  client.begin(path + status);
  client.addHeader("Content-Type", "text/plain");
  client.POST("POST request from light detector");
  client.getString();
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
  int signal = getLightStatus();
  digitalWrite(LED_BUILTIN, invertDigitalState(signal)); // LED state is inverted.
  // The connection is established, and the light status has changed.
  if(signal != previousSignal && WiFi.status() == WL_CONNECTED)
  {
    sendLightStatus(signal);
    previousSignal = signal;
  }
  delay(500);
}

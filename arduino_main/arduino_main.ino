#include <ESP8266WiFi.h>

/*
 * File wifiConnection.h contains the ssid and password required to
 * connect to a wifi network. They are kept seperate from the source
 * code as they must stay confidential. DO NOT PUSH THEM TO GITHUB.
 */
#include "wifiConnection.h"

#define DIGITAL_INPUT D1
boolean connected = false;
boolean lightDetected = false;
boolean lightStateChanged = false;

boolean connectToWifi()
{
  WiFi.begin(SSID, PASSWORD);
  Serial.print("Connecting to ");
  Serial.println(SSID);
  int i=0;
  while(WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
    Serial.print(++i);
    Serial.print(" - ");
    if(i>=120) // Fails after two minutes.
    {
      Serial.print("\nConnection failed");
      return false;
    }
  }
  Serial.println("\nConnection established!");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  return true;
}

static int getDigitalSignal() {return digitalRead(DIGITAL_INPUT);}

static bool lightIsDetected() {return getDigitalSignal() == HIGH;}

void setup()
{
  Serial.begin(9600);
  // The input pin is on when light is detected.
  // Connect a 56 kiloohm pull-down resistor to the digital input pin.
  pinMode(DIGITAL_INPUT, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  connected = connectToWifi();
}

void loop()
{
  if(lightIsDetected())
  {
    digitalWrite(LED_BUILTIN, LOW); // LED state is inverted.
    lightDetected = true;
  }
  else
  {
    digitalWrite(LED_BUILTIN, HIGH); // LED state is inverted.
    lightDetected = false;
  }
  if(connected)
  {
    if(lightDetected)
    {
      //
    }
    else
    {
      //
    }
  }
  delay(1000);
}

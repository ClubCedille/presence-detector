#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecure.h>

/*
La lumière est allumée: https://aquinas.xyz/club/api.php?boolSet=1
La lumière est éteinte: https://aquinas.xyz/club/api.php?boolSet=0
Voir la valeur: https://aquinas.xyz/club/api.php
*/

/*
 * File wifiConnection.h contains the ssid and password required to
 * connect to a wifi network. They are kept seperate from the source
 * code as they must stay confidential. DO NOT PUSH THEM TO GITHUB.
 */
#include "wifiConnection.h"

#define LIGHT_SIGNAL_INPUT 5 // pin D1
#define HOST "aquinas.xyz"
#define HTTPS_PORT 443
#define PATH "/club/api.php"

bool connectedToHost = false;
int previousSignal = -1;

HTTPClient client;
WiFiClientSecure secureClient;

bool connectToHost(char* host, uint16_t port, char* sha1_key)
{
  secureClient.setFingerprint(sha1_key);
  secureClient.setTimeout(15000);
  Serial.println("Establishing a HTTPS connection");
  int i = 0;
  while(!secureClient.connect(host, port))
  {
    Serial.print(++i);
    Serial.print(" - ");
    if(i>=20)
    {
      Serial.println("\nHTTPS connection failed.");
      return false;
    }
    delay(10);
  }
  return true;
}

void connectToWifi(char* ssid, char* password)
{
  delay(1000); // Earase after trials
  //WiFi.mode(WIFI_OFF); //Prevents reconnection issue (taking too long to connect)
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
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
      return;
    }
  }
  Serial.println("\nConnection established!");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

int getLightStatus() {return digitalRead(LIGHT_SIGNAL_INPUT);}

int invertDigitalState(int state) {return state==HIGH? LOW: HIGH;}

bool lightIsDetected() {return getLightStatus() == HIGH;}

void sendLightStatus(int status)
{
  /*
  //String path("http://192.168.1.88:8085/status/");
  String path("https://aquinas.xyz/club/api.php?boolSet=");
  String completePath = path + status;
  Serial.println(completePath);
  //client.begin(completePath, SHA1_KEY);
  client.begin("http://perdu.com");
  //client.addHeader("Content-Type", "text/plain");
  //int httpsCode = client.POST("POST request from light detector");
  int httpsCode = client.GET();
  String response = client.getString();
  client.end();
  Serial.print("Error code: ");
  Serial.println(httpsCode);
  Serial.print("Response: ");
  Serial.println(response);
  //*/

  //*
  secureClient.print(String("GET ") + PATH + "?boolSet=" + status + " HTTP/1.1\r\n" +
               "Host: " + HOST + "\r\n" +   
               "User-Agent: ESP8266\r\n" +            
               "Connection: close\r\n\r\n");
  Serial.print("Request sent");
  //*/
}

void setup()
{
  Serial.begin(115200);
  // The input pin is on when light is detected.
  // Connect a 56 kiloohm pull-down resistor to the digital input pin.
  pinMode(LIGHT_SIGNAL_INPUT, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  char* host = "rocketchat.cedille.club";// HOST;
  char* password = PASSWORD;
  char* sha1_key = SHA1_KEY;
  char* ssid = SSID;
  connectToWifi(ssid, password);
  connectedToHost = connectToHost(host, HTTPS_PORT, sha1_key);
  //https://links2004.github.io/Arduino/d2/d2f/class_wi_fi_client_secure.html uint16_t
}

void loop()
{
  int signal = getLightStatus();
  digitalWrite(LED_BUILTIN, invertDigitalState(signal)); // LED state is inverted.
  // The connection is established, and the light status has changed.
  //if(connected && signal!=previousSignal)
  if(WiFi.status() == WL_CONNECTED && secureClient.connected())
  {
    sendLightStatus(signal);
  }
  previousSignal = signal;
  delay(500);
}

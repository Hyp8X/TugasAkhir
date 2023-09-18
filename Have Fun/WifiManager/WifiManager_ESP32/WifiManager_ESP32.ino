#include <WiFi.h>
#include<WiFiManager.h>

const char *ssid = "ESP32ap";
const char *password = "12345678";

void setup() {
  Serial.begin(115200);
  Serial.println("Configuring access point...");

  WiFi.mode(WIFI_STA);
  WiFi.softAP(ssid, password);
  Serial.println("Wait 100 ms for AP_START...");
  delay(100);
  
  /*Serial.println("Set softAPConfig");
  IPAddress Ip(192, 168, 1, 21);
  IPAddress NMask(255, 255, 255, 0);
  WiFi.softAPConfig(Ip, Ip, NMask);
  
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);*/
}

void loop() {
}
#define BLYNK_TEMPLATE_ID "TMPL7ycfcUlD" // 
#define BLYNK_DEVICE_NAME "Alarm Kebakaran" //
#define BLYNK_AUTH_TOKEN "HU_iCfUCs4OBDjPtnb0CJ6IyRuwa1rBP" //

#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

char ssid[] = "Riady";
char pass[] = "riady121455";

int pinApi = 15; //sensor apa ? int = 012345678910
int ldr = 26; //sesuaikan pin
float pinSuhu = 27; // sesuaikan pin > Float = 10,5 ; 12,1 (nilai Decimal)
    
 void setup() {
  Serial.begin(9600);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  pinMode(pinApi, INPUT); // sesuai Line 14 dst tergantung pin
}

void loop() {
  Blynk.run();
  int bacasensor = digitalRead(pinApi); // disesuaikan data read (digital/analog) & Definisi Variable
  float bacasuhu = analogRead(pinSuhu);// line 15
  int bacaldr = analogRead(ldr); // 15
  Blynk.virtualWrite(V3, bacasuhu); // V3 dapat dari DataStream
  Blynk.virtualWrite(V4, bacaldr); // V4 Dapat dari DataStream
  if (bacasensor => 1200) {
    Serial.print(bacaldr);
    Blynk.virtualWrite(V2, " Sudah Siang !!! ");
  }
  else {
    Blynk.VirtualWrite(V2, " SUDAH MALAM ! ! ! ");
  }
  delay(1000);
}  
  // if (bacasensor == LOW) {
  //   Serial.print(bacasensor);
  //   Serial.println(" - Api terdeteksi");
  //   Blynk.virtualWrite(V2, "Ada Kebakaran");
  // } else {
  //   Serial.print(bacasensor);
  //   Serial.println(" - Tidak Api terdeteksi");
  //   Blynk.virtualWrite(V2, "CLEAR");
  // }


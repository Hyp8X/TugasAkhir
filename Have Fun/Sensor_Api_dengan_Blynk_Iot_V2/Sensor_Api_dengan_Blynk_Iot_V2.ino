// Fill-in information from your Blynk Template here
#define BLYNK_TEMPLATE_ID "TMPL7ycfcUlD"
#define BLYNK_DEVICE_NAME "Alarm Kebakaran"
#define BLYNK_AUTH_TOKEN "HU_iCfUCs4OBDjPtnb0CJ6IyRuwa1rBP"

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "realme C1";
char pass[] = "kipo9807";

int pinApi = 15;


void setup()
{
  Serial.begin(9600);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  pinMode(pinApi, INPUT);
}

void loop() {
  Blynk.run();
  int bacasensor = digitalRead(pinApi);
  Blynk.virtualWrite(V1, bacasensor);
  if (bacasensor == LOW) {
    Serial.print(bacasensor);
    Serial.println(" - Api terdeteksi");
    Blynk.virtualWrite(V2, "Ada Kebakaran");
  } else {
    Serial.print(bacasensor);
    Serial.println(" - Tidak Api terdeteksi");
    Blynk.virtualWrite(V2, "CLEAR");
  }
  delay(1000);
}


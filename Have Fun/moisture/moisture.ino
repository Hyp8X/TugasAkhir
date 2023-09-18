#define BLYNK_TEMPLATE_ID "TMPL7ycfcUlD"
#define BLYNK_DEVICE_NAME "SmartFarm"
#define BLYNK_AUTH_TOKEN "5cT5Ni8bZIFthbW964Wlfn2xI5gMn4r7"
#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include<Wire.h>
#include<LiquidCrystal_I2C.h>


#define AOUT_PIN 36 // ESP32 pin GIOP36 (ADC0) that connects to AOUT pin of moisture sensor
#define THRESHOLD1 1000 // CHANGE YOUR THRESHOLD HERE
#define THRESHOLD2 1700
#define HUJAN 2000
#define GERIMIS 3500
#define pinhujan  32

LiquidCrystal_I2C lcd(0x27, 16,2);

int nilaihujan;
int value;

char ssid[] = "realmeC15";
char pass[] = "realmec15pass";
// const char* ssid = "realmeC15";
// const char* password = "realmec15pass";

void setup() {
  Serial.begin(9600);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  lcd.begin();
  // WiFi.disconnect();
  // WiFi.begin(ssid, pass);
  // while ((!(WiFi.status() == WL_CONNECTED))) {
  //   delay(300);
  //   Serial.print(".");
  // }
  // Serial.println("");
  // Serial.println("WiFi connected");
  // Serial.println("IP address: ");
  // Serial.println(WiFi.localIP());

  pinMode (pinhujan, INPUT);
  pinMode (AOUT_PIN, INPUT);
}

void hujan() {
      nilaihujan = analogRead(pinhujan);
  // Serial.print("Curah Hujan: ");
  // Serial.println(nilaihujan);
  // Serial.println("==============================================");
    Blynk.virtualWrite(V4, nilaihujan);
    Serial.print(nilaihujan);
  if (nilaihujan <= GERIMIS && nilaihujan >= HUJAN) {
    Blynk.virtualWrite(V3, "GERIMIS");
    Serial.print("Sedang Gerimis");
      lcd.setCursor(0,0);
      lcd.print("SEDANG GERIMIS");
      // ==================   
  }
  else if (nilaihujan < HUJAN){
    Blynk.virtualWrite(V3, "HUJAN");
    Serial.print("Sedang Hujan");
      lcd.setCursor(0,0);
      lcd.print("SEDANG HUJAN");
      // ================== 
  } 
  else {
    Serial.print(nilaihujan);
    Blynk.virtualWrite(V3, "TIDAK HUJAN !");
    Serial.print("Tidak Hujan");
      lcd.setCursor(0,0);
      lcd.print("TIDAK HUJAN");
      // ================== 
  }
}

void tanah(){
    value = analogRead(AOUT_PIN); // read the analog value from sensor
  Blynk.virtualWrite(V5, value);
Serial.print(value);  
  if (value <= THRESHOLD2 && value >= THRESHOLD1) {
    Serial.print("Tanah ini LEMBAB (");
    Blynk.virtualWrite(V2, "TANAH LEMBAB");
      lcd.setCursor(0,1);
      lcd.print("TANAH LEMBAB");
      // ==================  
    }
  else if (value <= THRESHOLD1) {
    Serial.print("Tanah ini KERING");
    Blynk.virtualWrite(V2, "TANAH KERING");
      lcd.setCursor(0,1);
      lcd.print("TANAH KERING");
      // ================== 

    }
  else {
    Serial.print("Tanah ini BASAH (");
    Blynk.virtualWrite(V2, "TANAH BASAH");
      lcd.setCursor(0,1);
      lcd.print("TANAH BASAH");
      
      // ==================
  }
  Serial.print(value);
  Serial.println(")");
  }

// ========================================

void loop() {
  Blynk.run();
  lcd.backlight();
  tanah();
  hujan();
  // delay(2000);
  lcd.clear();
  lcd.noBacklight();
  
  
  // delay(5000);      
  }  


/***************************************************************************
  This is a library for the BMP280 humidity, temperature & pressure sensor

  Designed specifically to work with the Adafruit BMP280 Breakout
  ----> http://www.adafruit.com/products/2651

  These sensors use I2C or SPI to communicate, 2 or 4 pins are required
  to interface.

  Adafruit invests time and resources providing this open source code,
  please support Adafruit andopen-source hardware by purchasing products
  from Adafruit!

  Written by Limor Fried & Kevin Townsend for Adafruit Industries.
  BSD license, all text above must be included in any redistribution
 ***************************************************************************/

#include <Wire.h>
#include <SPI.h>
#include <Adafruit_BMP280.h>
#include <ThingSpeak.h>
#include <WiFi.h>

WiFiClient client;

const char *ssid = "realme C1";
const char *pass = "kipo9807";
const char *authW = "LMYQN75R1B8KCQSN";
unsigned long channel = 1968627;

#define BMP_SCK  (13)
#define BMP_MISO (12)
#define BMP_MOSI (11)
#define BMP_CS   (10)
#define SDA 21
#define SCL 22

int tmp;
int qnh;
float QFE;

Adafruit_BMP280 bmp; // I2C
//Adafruit_BMP280 bmp(BMP_CS); // hardware SPI
//Adafruit_BMP280 bmp(BMP_CS, BMP_MOSI, BMP_MISO,  BMP_SCK);

void setup() {
  Serial.begin(9600);
  //WIFI SETUP
    WiFi.disconnect();
  WiFi.begin(ssid, pass);
  while ((!(WiFi.status() == WL_CONNECTED))) {
    delay(300);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  /*Serial.println("IP address: ");
  Serial.println(WiFi.localIP());*/

  ThingSpeak.begin(client);

  //BMP SETUP  
  while ( !Serial ) delay(100);   // wait for native usb
  //Serial.println(F("BMP280 test"));
  unsigned status;
  status = bmp.begin(BMP280_ADDRESS_ALT, BMP280_CHIPID);
  //status = bmp.begin();
  if (!status) {
    Serial.println(F("Could not find a valid BMP280 sensor, check wiring or "
                      "try a different address!"));
    Serial.print("SensorID was: 0x"); Serial.println(bmp.sensorID(),16);
    Serial.print("        ID of 0xFF probably means a bad address, a BMP 180 or BMP 085\n");
    Serial.print("   ID of 0x56-0x58 represents a BMP 280,\n");
    Serial.print("        ID of 0x60 represents a BME 280.\n");
    Serial.print("        ID of 0x61 represents a BME 680.\n");
    while (1) delay(10);

  }

  /* Default settings from datasheet. */
  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
                  Adafruit_BMP280::SAMPLING_X1,     /* Temp. oversampling */
                  Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
                  Adafruit_BMP280::FILTER_X16,      /* Filtering. */
                  Adafruit_BMP280::STANDBY_MS_500); /* Standby time. */
}

void post() {
  int x = ThingSpeak.writeFields(channel, authW);
  if(x == 200){
      Serial.println("Channel update successful.");
    unsigned long timeout = millis();
  }
  else if(x == 404){
    Serial.println("FALSE API / SERVER ADDRESS");
  }
  else{
      Serial.println("Problem updating channel. HTTP error code " + String(x));
    }
}

void loop() {
    tmp = bmp.readTemperature();
    Serial.print("Temperature = ");
    Serial.print(tmp);
    Serial.println(" *C");
    ThingSpeak.setField(1, tmp);
    
    qnh = bmp.readPressure()/100;
    Serial.print("QNH = ");
    Serial.print(qnh);
    Serial.println(" hPa");
    ThingSpeak.setField(2, qnh);
    
    QFE =bmp.readAltitude();
    Serial.print("Approx altitude = ");
    Serial.print(QFE); /* Adjusted to local forecast! */
    Serial.println(" m");
    ThingSpeak.setField(3, QFE);

    delay(10000);
    post();
    delay(2000);
}

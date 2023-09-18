#include <WiFi.h>
#include <ThingSpeak.h>

WiFiClient  client;

//Connection Config


const char *ssid = "Realme C15"; //Nama Hostpot
const char *pass = "riady121455"; //Kosongi bila tanpa password
const char *authW = "EAVL1CK10UI84WC4";
unsigned long channel = 1965747;
const char *tinggi = "ketinggian air";
const char *curah = "curah hujan";

//ThingSpeak Config
/*String host = "api.thingspeak.com";
String writeAPIKey = "EAVL1CK10UI84WC4"; //Ganti API Key di Channel Masing Masing
String request_string;  <== ESP8266 */ 

//Config Jarak Ultrasonic
int trig = 33; // membuat varibel trig yang di set ke-pin D14
int echo = 25; // membuat variabel echo yang di set ke-pin D15
long durasi, jarak;     // membuat variabel durasi dan jarak

//Config Sensor Air Hujan
#define pinhujan  32
//int pinhujan = 26; //D16
int nilaihujan;

void setup() {
  Serial.begin(115200);
  WiFi.disconnect();
  WiFi.begin(ssid, pass);
  while ((!(WiFi.status() == WL_CONNECTED))) {
    delay(300);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  
  pinMode(trig, OUTPUT);    // set pin trig menjadi OUTPUT
  pinMode(echo, INPUT);     // set pin echo menjadi INPUT
  
  pinMode (pinhujan, INPUT);

  ThingSpeak.begin(client);
}

void baca_sensor_ultrasonik() {
  digitalWrite(trig, LOW);
  delayMicroseconds(8);
  digitalWrite(trig, HIGH);
  delayMicroseconds(8);
  digitalWrite(trig, LOW);
  delayMicroseconds(8);
  durasi = pulseIn(echo, HIGH); // menerima suara ultrasonic
  jarak = (durasi / 2) / 29.1;
  Serial.println("");
  Serial.print("Tinggi Air: ");
  Serial.print(jarak);
  Serial.println(" Cm Dari Permukaan");
  ThingSpeak.setField(1, jarak);
}

void baca_sensor_hujan() {
  nilaihujan = analogRead(pinhujan);
  Serial.print("Curah Hujan: ");
  Serial.println(nilaihujan);
  Serial.println("");
  ThingSpeak.setField(2, nilaihujan);
}

void kirim_data_thingspeak() {
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
  baca_sensor_ultrasonik();
  baca_sensor_hujan();
  delay(10000);
  kirim_data_thingspeak();
  delay(2000);
}

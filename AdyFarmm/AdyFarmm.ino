#include <WiFi.h>
#include <Wire.h>
#include "SparkFun_SHTC3.h"
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>   // Universal Telegram Bot Library written by Brian Lough: https://github.com/witnessmenow/Universal-Arduino-Telegram-Bot
#include <ArduinoJson.h>

SHTC3 SHTC; // for My SHTC Module

// Replace with your network credentials
const char* ssid = "Toplapo";
const char* password = "riady121455";

#define THRESHOLD1 1600 // THR Tanah
#define THRESHOLD2 2000
#define HUJAN 2000
#define GERIMIS 3500

#define relay2 26
#define relay 33
#define pinhujan 32
#define hidup HIGH
#define mati LOW

// Initialize Telegram BOT
#define BOTtoken "*******************************************"  // your Bot Token (Get from Botfather)
#define CHAT_ID "**********"
#define AOUT_PIN 36

WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);

// Checks for new messages every 1 second.
int botRequestDelay = 1000;
unsigned long lastTimeBotRan;

// const int RELAY_PIN = 32;
// bool relayState = HIGH;

String getReadings(){
  float humid, temp;
  int value;
  int nilaihujan;
  
  value = analogRead(AOUT_PIN);
  humid = SHTC.toPercent();
  temp = SHTC.toDegC();
  nilaihujan = analogRead(pinhujan);


  String message = "Temperature: " + String(temp) + " ºC \n";
  message += "Humidity: " + String (humid) + " % \n";
  message += "\n";
  message += "Ground Humidity : " + String (value) + "\n";
  message += "Nilai Cuaca : " + String (nilaihujan) + "\n";
  message += "\n";
  
  if (value <= THRESHOLD2 && value >= THRESHOLD1) {
    message += "Status Tanah : Lembab";
    message += "\n";
    digitalWrite(relay, hidup);
  }
  else if (value <= THRESHOLD1) {
    message += "Status Tanah : Basah";
    message += "\n";
    digitalWrite(relay, hidup);
    // digitalWrite(RELAY_PIN, LOW);
  }
  else {
    message += "Status Tanah : Kering";
    message += "\n";
    digitalWrite(relay, mati);
    // digitalWrite(RELAY_PIN, HIGH);
  }

  if (nilaihujan <= GERIMIS && nilaihujan >= HUJAN) {
    message += "Status Cuaca : Gerimis";
  }
  else if (nilaihujan < HUJAN) {
    message += "Status Cuaca : Hujan";
  }
  else {
    message += "Status Cuaca : Cerah";
  }

  return message;
}

// Handle what happens when you receive new messages
void handleNewMessages(int numNewMessages) {
  Serial.println("handleNewMessages");
  Serial.println(String(numNewMessages));

  for (int i=0; i<numNewMessages; i++) {
    // Chat id of the requester
    String chat_id = String(bot.messages[i].chat_id);
    if (chat_id != CHAT_ID){
      bot.sendMessage(chat_id, "Unauthorized user", "");
      continue;
    }
    
    // Print the received message
    String text = bot.messages[i].text;
    Serial.println(text);

    String from_name = bot.messages[i].from_name;

    if (text == "/start" && "/?") {
      String welcome = "Welcome, " + from_name + ".\n";
      welcome += "Gunakan Command untuk memerintahkan dan mendapatkan Output.\n\n";
      welcome += "/Ppupuk_on Untuk Menghidupkan Pompa Pupuk \n";
      welcome += "/Ppupuk_off Untuk Mematikan Pompa Pupuk \n";
      welcome += "/status_Pompa_Air Request Status Pompa Air \n";
      welcome += "/status_pompa_pupuk Request Status Pompa Pupuk \n";
      welcome += "/readings to Request Data Cuaca Terkini \n";
      bot.sendMessage(chat_id, welcome, "");
    }

    if (text == "/Ppupuk_on") {
      bot.sendMessage(chat_id, "Pompa Pupuk Hidup", "");
      digitalWrite(relay2, mati);
    }
    
    if (text == "/Ppupuk_off") {
      bot.sendMessage(chat_id, "Pompa Pupuk Mati", "");
      digitalWrite(relay2, hidup);
    }

    if (text == "/readings") {
    String readings = getReadings();
    bot.sendMessage(chat_id, readings, "");
      }

    if (text == "/status_Pompa_Air") {
      if (digitalRead(relay)){
        bot.sendMessage(chat_id, "Pompa Air Mati", "");
      }
      else{
        bot.sendMessage(chat_id, "Pompa Air Hidup", "");
      }
    }

    if (text == "/status_pompa_pupuk") {
      if (digitalRead(relay2)){
        bot.sendMessage(chat_id, "Pompa Pupuk Mati", "");
      }
      else{
        bot.sendMessage(chat_id, "Pompa Pupuk Hidup", "");
      }
    }
  }
}

void setup() {
  Serial.begin(9600);
  Wire.begin();
  SHTC.begin();
  pinMode(relay, OUTPUT);
  pinMode(relay2, OUTPUT);
  pinMode (AOUT_PIN, INPUT);
  pinMode (pinhujan, INPUT);
  digitalWrite(relay, hidup);
  digitalWrite(relay2, hidup);
  
  // Connect to Wi-Fi
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  client.setCACert(TELEGRAM_CERTIFICATE_ROOT); // Add root certificate for api.telegram.org
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }
  // Print ESP32 Local IP Address
  Serial.println(WiFi.localIP());
}

void siram() {
  int tanah = analogRead(AOUT_PIN);
  Serial.print(tanah);
    if (tanah <= THRESHOLD2 && tanah >= THRESHOLD1) {
      // message += "Status Tanah : Lembab";
      digitalWrite(relay, hidup);
    }
    else if (tanah <= THRESHOLD1) {
      // message += "Status Tanah : Basah";
      digitalWrite(relay, hidup);
    }
    else {
      // message += "Status Tanah : Kering";
      digitalWrite(relay, mati);
    }
}

void loop() {
  //TeleBot
  if (millis() > lastTimeBotRan + botRequestDelay)  {
    int numNewMessages = bot.getUpdates(bot.last_message_received + 1);

    while(numNewMessages) {
      Serial.println("got response");
      handleNewMessages(numNewMessages);
      numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    }
    lastTimeBotRan = millis();
  }
  SHTC3_Status_TypeDef result = SHTC.update();
  siram();
}
#include<Wire.h>
#include<LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16,2);

int pinDO = 12;
int pinAO = A0;

int hijau = 7;
int merah = 8;
int buzzer = 5;

int DataDigital, DataAnalog;

void setup() {
  Serial.begin(9600);
  pinMode (pinDO, INPUT);
  pinMode (pinAO, INPUT);
  pinMode (hijau, OUTPUT);
  pinMode (merah, OUTPUT);
  pinMode (buzzer, OUTPUT);
  lcd.begin();
}

void loop() {
  DataDigital = digitalRead(pinDO);
  DataAnalog = analogRead(pinAO);
  Serial.print("Data Digital = ");
  Serial.print(DataDigital);
  Serial.print("   ");
  Serial.print("Data Analog = ");
  Serial.println(DataAnalog);
  delay(2000);

if (DataAnalog <= 550) {
    digitalWrite(merah, HIGH);
    digitalWrite(hijau, LOW);
    digitalWrite(buzzer, LOW);
    delay(100);
    digitalWrite(buzzer,HIGH);
    delay(50);
    lcd.setCursor(4,0);
    lcd.print("HUJAN ! ! !");
  }
else {
  digitalWrite(merah, LOW);
  digitalWrite(hijau, HIGH);
  digitalWrite(buzzer, LOW);
  }  
}

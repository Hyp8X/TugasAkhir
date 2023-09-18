#include<Wire.h>
#include<LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16,2);

//Deklarasi PIN
int trig = 6; 
int echo = 7; 
long durasi, jarak;     // membuat variabel durasi dan jarak
int merah = 4;
int kuning = 3;
int hijau = 2;
int buzzer = 5;

void setup() {
  pinMode(trig, OUTPUT);    // set pin trig menjadi OUTPUT
  pinMode(echo, INPUT);     // set pin echo menjadi INPUT
  pinMode(merah, OUTPUT);
  pinMode(kuning, OUTPUT);
  pinMode(hijau, OUTPUT);
  pinMode(buzzer, OUTPUT);
  Serial.begin(11000);       // digunakan untuk komunikasi Serial dengan komputer
  lcd.begin ();
}

void loop() {
  digitalWrite(trig, LOW);
  delayMicroseconds(8);
  digitalWrite(trig, HIGH);
  delayMicroseconds(8);
  digitalWrite(trig, LOW);
  delayMicroseconds(8);
  durasi = pulseIn(echo, HIGH); // menerima suara ultrasonic
  jarak = (durasi / 2) / 29.1;  // mengubah durasi menjadi jarak (cm)

  if ((jarak > 20)&&(jarak == 12)){
    digitalWrite(hijau, HIGH);
    digitalWrite(merah, LOW);
    digitalWrite(kuning, LOW);
    digitalWrite(buzzer, LOW);
    delay(350);
    digitalWrite(buzzer, LOW);
    delay(500);
    }

  else if((jarak == 11 )&&(jarak <= 7)){
    digitalWrite(hijau, LOW);
    digitalWrite(merah, LOW);
    digitalWrite(kuning, HIGH);
    digitalWrite(buzzer, LOW);
    delay(50);
    digitalWrite(buzzer, LOW);
    delay(100);
  }
    else {
    digitalWrite(hijau, LOW);
    digitalWrite(merah, HIGH);
    digitalWrite(kuning, LOW);
    digitalWrite(buzzer, LOW);
    }

    //LCD SHOW YEET
    lcd.setCursor(0,0);
    lcd.print("jarak");
    lcd.backlight();
    lcd.setCursor(0,1);
    lcd.print(jarak);
    lcd.setCursor(5,1);
    lcd.print(" Cm !!");
    lcd.clear();
    
    
    
   }
//  Serial.print("Jarak Benda : ");
//  Serial.print(jarak) ;      // menampilkan jarak pada Serial Monitor
//  Serial.println(" Cm");

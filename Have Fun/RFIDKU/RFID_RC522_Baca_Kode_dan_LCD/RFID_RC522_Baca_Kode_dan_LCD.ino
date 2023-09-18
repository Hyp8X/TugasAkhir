#include <SPI.h> 
#include <Wire.h> 
#include <RFID.h> 
#include <LiquidCrystal_I2C.h> 

LiquidCrystal_I2C lcd(0x27, 16, 2); 

#define sda 10 //Pin Serialdata (SDA)
#define rst 9 //pin Reset

RFID rfid(sda, rst);

  int serNum[5];
  
  int cards[][5] = {
  {160,18,160,32,50}
  };

  

  bool access = false;

void setup() {
  Serial.begin(9600); //baud komunikasi serial monitor
  lcd.begin();
  lcd.setBacklight(255); //menghidupkan lampu latar LCD
  SPI.begin(); //Prosedur antarmuka SPI
  rfid.init(); //Memulai inialisasi module RFID

  lcd.setCursor (0, 0);
  lcd.print("****WELCOME!****");
  lcd.setCursor (0, 1);
  delay (5000);
  lcd.clear();
  }


void loop() {

    
    if(rfid.isCard()){
    
        if(rfid.readCardSerial()){
            Serial.print(rfid.serNum[0]);
            Serial.print(" ");
            Serial.print(rfid.serNum[1]);
            Serial.print(" ");
            Serial.print(rfid.serNum[2]);
            Serial.print(" ");
            Serial.print(rfid.serNum[3]);
            Serial.print(" ");
            Serial.print(rfid.serNum[4]);
            Serial.println("");
            

              for(int x = 0; x < sizeof(cards); x++){
              for(int i = 0; i < sizeof(rfid.serNum); i++ ){
                  if(rfid.serNum[i] != cards[x][i]) {
                      lcd.setCursor(0,1);
                      lcd.print("UNKNOWN ACCESS");
                      delay(1000);
                      lcd.clear();
                      access = false;
                      break;
                        }
                  else {
                    access = true;
                    }
                      }
                 if (access) 
                     break;
              }
        }

      if (access){
        lcd.print("Access Accepted");
        lcd.setCursor(1,1);
        lcd.print("WELCOME ADY");
        delay(5000);
        lcd.clear();
        }
        
    }
    rfid.halt();
}
//160 18 160 32 50 kartu
//147 125 186 29 73 ganci

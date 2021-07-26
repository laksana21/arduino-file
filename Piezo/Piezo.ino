#include "Wire.h" // For I2C
#include "LCD.h" // For LCD
#include "LiquidCrystal_I2C.h" // Added library*
LiquidCrystal_I2C lcd(0x3F,2,1,0,4,5,6,7); // 0x27 is the default I2C bus address of the backpack-see article

// deklarasi variabel
int mgetar, ngtr;
int detecDgetar = LOW;
int getarPin = A0;
const int dGetarPin = 2;
int hpeak = 0;

void setup() {
  lcd.setBacklightPin(3,POSITIVE); //BL,BL_POL
  lcd.setBacklight(HIGH);
  lcd.begin(20,4);
  lcd.clear();
  pinMode(12,OUTPUT);
  pinMode(2, INPUT);
}

void loop() {
  // baca getaran dari A0 
  ngtr = analogRead(getarPin);
  detecDgetar = digitalRead(dGetarPin);
  mgetar = ngtr;
  //kirim ke serial
  //Serial.println(mgetar);
  lcd.setCursor(0,0);
  lcd.print("Getaran : ");
  lcd.setCursor(9,0);
  lcd.print(mgetar);

  if (detecDgetar == HIGH)
  {
    lcd.setCursor(0,2);
    lcd.print("D-Shake Detected!");
  }
  else
  {
    lcd.setCursor(0,2);
    lcd.print("                 ");
  }
  
  if(mgetar>=1000)
  {
    lcd.setCursor(0,0);
    lcd.print("Getaran : ");
    lcd.setCursor(10,0);
    lcd.print(mgetar);
  }
  else if(mgetar>=100)
  {
    lcd.setCursor(0,0);
    lcd.print("Getaran : 0");
    lcd.setCursor(11,0);
    lcd.print(mgetar);
  }
  else if(mgetar>=10)
  {
    lcd.setCursor(0,0);
    lcd.print("Getaran : 00");
    lcd.setCursor(12,0);
    lcd.print(mgetar);
  }
  else 
  {
    lcd.setCursor(0,0);
    lcd.print("Getaran : 000");
    lcd.setCursor(13,0);
    lcd.print(mgetar);
  }

  if(mgetar>hpeak) //jika getaran cukup keras
  {
    hpeak = mgetar;
    lcd.clear();
    lcd.setCursor(0,1);
    lcd.print("H.Peak : ");
    lcd.setCursor(9,1);
    lcd.print(hpeak);
  }
  
  if(mgetar>=120) //jika getaran cukup keras
  {
    digitalWrite(12,HIGH); // aktifkan relay
    delay(2000); // delay 2 detik
  }
  else digitalWrite(12,LOW);
  delay(30); // berhenti beberapa milidetik
}

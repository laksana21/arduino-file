#include <Wire.h> // For I2C
#include <LCD.h> // For LCD
#include <LiquidCrystal_I2C.h> // Added library*
#include <SD.h>

Sd2Card card;
SdVolume volume;
SdFile root;

LiquidCrystal_I2C lcd(0x3F, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE); // 0x27 is the default I2C bus address of the backpack-see article
const int chipSelect = 4;   // 4 for Arduino boards, might be different in other non-Arduino boards.

void setup() {
  /*// put your setup code here, to run once:
  Serial.begin(9600);
  if (!card.init(SPI_HALF_SPEED, chipSelect)) {
    Serial.println("initialization failed!");
    return;
  } 
  else {
    Serial.println("Wiring is correct and a card is present!"); 
  }*/
  Serial.begin(115200);
  lcd.begin (20,4); // 16 x 2 LCD module
  lcd.setBacklightPin(3,POSITIVE); // BL, BL_POL
  lcd.setBacklight(HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("1234567890-+%*=/{}()");
  lcd.setCursor(0,1);
  lcd.print("ABCDEFGHIJKLMNOPQRST");
  lcd.setCursor(0,2);
  lcd.print("UVWYZabcdefghijklmno");
  lcd.setCursor(0,3);
  lcd.print("pqrstuvwxyz.,!?@#&<>");
  delay(500);
}

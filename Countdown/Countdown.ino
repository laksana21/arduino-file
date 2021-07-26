#include "Wire.h" // For I2C
#include "LCD.h" // For LCD
#include "LiquidCrystal_I2C.h" // Added library*
LiquidCrystal_I2C lcd(0x3F,2,1,0,4,5,6,7); // 0x27 is the default I2C bus address of the backpack-see article

int waktu = 18000;
int bl = 0, hbl = 10;

byte verticalLine[8] = {
  B00100,
  B00100,
  B00100,
  B00100,
  B00100,
  B00100,
  B00100,
  B00100
};  

byte char2[8] = {
  B00000,
  B00000,
  B00000,
  B11100,
  B00100,
  B00100,
  B00100,
  B00100
};

byte char1[8] = {
  B00000,
  B00000,
  B00000,
  B00111,
  B00100,
  B00100,
  B00100,
  B00100
};

byte char3[8] = {
  B00100,
  B00100,
  B00100,
  B00111,
  B00000,
  B00000,
  B00000,
  B00000
};

byte char4[8] = {
  B00100,
  B00100,
  B00100,
  B11100,
  B00000,
  B00000,
  B00000,
  B00000
};

void createCustomCharacters()
{
  lcd.createChar(0, verticalLine);
  lcd.createChar(1, char1);
  lcd.createChar(2, char2);
  lcd.createChar(3, char3);
  lcd.createChar(4, char4);
}

void printFrame()
{
  lcd.setCursor(1,0);
  lcd.print("------------------");
  lcd.setCursor(1,3);
  lcd.print("------------------");
  lcd.setCursor(0,1);
  lcd.write(byte(0));
  lcd.setCursor(0,2);
  lcd.write(byte(0));
  lcd.setCursor(19,1);
  lcd.write(byte(0));
  lcd.setCursor(19,2);
  lcd.write(byte(0));
  lcd.setCursor(0,0);
  lcd.write(byte(1));
  lcd.setCursor(19,0);
  lcd.write(byte(2));
  lcd.setCursor(0,3);
  lcd.write(byte(3));
  lcd.setCursor(19,3);
  lcd.write(byte(4));
}

void printTime(int detik)
{
  int milisecond,seconds,minutes,hour;
  String ms,sec,mint,hr;
  
  //hour=detik/108000;
  minutes=(detik%108000)/1800;
  seconds=((detik%108000)%1800)/30;
  milisecond=((detik%108000)%60)%30;

  ms = String(milisecond);
  sec = String(seconds);
  mint = String(minutes);
  //hr = String(hour);
  
  lcd.setCursor(6,2);
  //lcd.print(hr);
  //lcd.print(":");

  if(minutes<10)
  {
    mint = "0"+mint;
    lcd.print(mint);
  }else
  {
    lcd.print(minutes);
  }
  
  lcd.print(":");
  if(seconds<10)
  {
    sec = "0"+sec;
    lcd.print(sec);
  }else
  {
    lcd.print(seconds);
  }
  
  lcd.print(":");
  if(milisecond<10)
  {
    ms = "0"+ms;
    lcd.print(ms);
  }else
  {
    lcd.print(milisecond);
  }
}

void bling()
{
  if(waktu>=900 && bl==0)
  {digitalWrite(12,HIGH); bl=120; hbl=10;}
  else if(waktu>=600 && bl==0)
  {digitalWrite(12,HIGH); bl=90; hbl=10;}
  else if(waktu>=300 && bl==0)
  {digitalWrite(12,HIGH); bl=60; hbl=10;}
  else if(waktu>=150 && bl==0)
  {digitalWrite(12,HIGH); bl=30; hbl=10;}
  else if(waktu>=75 && bl==0)
  {digitalWrite(12,HIGH); bl=15; hbl=10;}
  else if(waktu>=1 && bl==0)
  {digitalWrite(12,HIGH); bl=5; hbl=2;}
  else if(waktu<=0)
  {digitalWrite(12,HIGH);}

  if(hbl==0)
  {digitalWrite(12,LOW);}

  bl--;hbl--;
}

void setup() {
  // put your setup code here, to run once:
  pinMode(12,OUTPUT);
  digitalWrite(12,LOW);
  lcd.setBacklightPin(3,POSITIVE); //BL,BL_POL
  lcd.setBacklight(HIGH);
  lcd.begin(20,4); 
  createCustomCharacters();
  printFrame();
  lcd.setCursor(2,1);
  lcd.print("Setting Time....");
  printTime(waktu);
  delay(2000);
}

void loop() {
  // put your main code here, to run repeatedly:
  lcd.setCursor(1,1);
  lcd.print("      ARMED!      ");
  for(int i=waktu; i>=0; i--)
  {
        printTime(waktu);
        bling();
        waktu--;
        delay(30);
  }
}

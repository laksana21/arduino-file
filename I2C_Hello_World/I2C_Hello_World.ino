#include "Wire.h" // For I2C
#include "LCD.h" // For LCD
#include "LiquidCrystal_I2C.h" // Added library*
#include "dht.h"

dht DHT;
#define DHT11_PIN A1
//Set the pins on the I2C chip used for LCD connections
//ADDR,EN,R/W,RS,D4,D5,D6,D7
int ledNorm = 10;
int ledErr = 11;
int buzzer = 4;
int modPin = 8;
int kipas = 7;
int relay = 9;
int lampu = 6;
int mode = 3;
int button = 0;
float sensorShow, sensorCahaya, humidity, temperature, moisture;
String serWeb;
char serInput;

LiquidCrystal_I2C lcd(0x27,2,1,0,4,5,6,7); // 0x27 is the default I2C bus address of the backpack-see article
void bahaya()
{
  digitalWrite(ledNorm, LOW);
  digitalWrite(ledErr, HIGH);
  digitalWrite(buzzer, HIGH);
  delay(100);
  digitalWrite(ledErr, LOW);
}
void awas()
{
  digitalWrite(ledNorm, LOW);
  digitalWrite(ledErr, HIGH);
  digitalWrite(buzzer, LOW);
}
void normal()
{
  digitalWrite(ledNorm, HIGH);
  digitalWrite(ledErr, LOW);
  digitalWrite(buzzer, LOW);
}
void setup()
{
   pinMode(ledNorm, OUTPUT);
   pinMode(ledErr, OUTPUT);
   pinMode(buzzer, OUTPUT);
   pinMode(modPin, INPUT_PULLUP);
   pinMode(lampu, OUTPUT);
   pinMode(kipas, OUTPUT);
   Serial.begin(115200);
   lcd.begin (16,2); // 16 x 2 LCD module
   lcd.setBacklightPin(3,POSITIVE); // BL, BL_POL
   lcd.setBacklight(HIGH);
}
void loop()
{ 
  lcd.clear();
  int chk = DHT.read11(DHT11_PIN);
  humidity = DHT.humidity;
  temperature = DHT.temperature;
  sensorShow = analogRead(A2);
  moisture = (sensorShow/1024)*100;
  sensorCahaya = analogRead(A3);
  float pVolt0 = sensorCahaya / 1024 * 100;
  serInput = Serial.read();
  
  serWeb = humidity;
  serWeb += temperature;
  serWeb += moisture;
  
  Serial.println(serWeb);
  
  if(pVolt0 < 90 || serInput == 'A' || serInput == 'D' || serInput == 'E' || serInput == 'G')
  {
    digitalWrite(lampu, LOW);
  }
  else
  {
    digitalWrite(lampu, HIGH);
  }

  //
  
  if(mode == 0)
  {
    //Soil moisture
    lcd.setCursor(0,0);
    lcd.print("Moisture : ");
    lcd.print(moisture, 0);
    lcd.print("%");

    if(moisture <= 30)
    {
      lcd.setCursor(0,1);
      lcd.print("Pot kebanjiran!");
      pinMode(relay, INPUT);
      bahaya();
    }
    else if(moisture >= 90)
    {
      lcd.setCursor(0,1);
      lcd.print("Tambahkan air!");
      pinMode(relay, OUTPUT);
      bahaya();
    }
    else if(moisture >= 80 && moisture < 90)
    {
      lcd.setCursor(0,1);
      lcd.print("Awas kurang air!");
      pinMode(relay, OUTPUT);
      awas();
    }
    else if(moisture >= 30 && moisture < 40)
    {
      lcd.setCursor(0,1);
      lcd.print("Awas pot banjir!");
      pinMode(relay, INPUT);
      awas();
    }
    else
    {
      lcd.setCursor(0,1);
      lcd.print("Kondisi mandali!");
      pinMode(relay, INPUT);
      normal();
    }
    if((serInput == 'B' || serInput == 'D' || serInput == 'F' || serInput == 'G') && moisture >= 40)
    {
      pinMode(relay, OUTPUT);
    }
  }
  else if(mode == 1)
  {
    //Air humidity
    lcd.setCursor(0,0);
    lcd.print("Humidity : ");
    lcd.print(humidity, 0);
    lcd.print("RH");
    if(humidity >= 90 || humidity <= 20)
    {
      lcd.setCursor(0,1);
      lcd.print("Udara tidak aman!");
      pinMode(kipas, OUTPUT);
      bahaya();
    }
    else
    {
      lcd.setCursor(0,1);
      lcd.print("Kondisi mandali!");
      pinMode(kipas, INPUT);
      normal();
    }
  }
  else if(mode == 2)
  {
    //Air temperature
    lcd.setCursor(0,0);
    lcd.print("Air Temp : ");
    lcd.print(temperature, 0);
    lcd.print("C");
    if(temperature >= 42)
    {
      lcd.setCursor(0,1);
      lcd.print("Suhu tinggi!");
      pinMode(kipas, OUTPUT);
      bahaya();
    }
    else if(temperature < 0)
    {
      lcd.setCursor(0,1);
      lcd.print("Suhu rendah!");
      pinMode(kipas, INPUT);
      bahaya();
    }
    else if(temperature >= 37 && temperature < 42)
    {
      lcd.setCursor(0,1);
      lcd.print("Awas suhu tinggi!");
      pinMode(kipas, OUTPUT);
      awas();
    }
    else if(temperature >= 0 && temperature < 20)
    {
      lcd.setCursor(0,1);
      lcd.print("Awas suhu rendah!");
      pinMode(kipas, INPUT);
      awas();
    }
    else
    {
      lcd.setCursor(0,1);
      lcd.print("Kondisi mandali!");
      pinMode(kipas, OUTPUT);
      normal();
    }
    if ((serInput == 'C' || serInput == 'E' || serInput == 'F' || serInput == 'G') && moisture >= 40)
    {
      pinMode(relay, OUTPUT);
    }
  }
  else if(mode == 3)
  {
    lcd.setCursor(0,0);
    lcd.print("M:");
    lcd.print(moisture, 0);
    lcd.print(" H:");
    lcd.print(humidity, 0);
    lcd.print(" T:");
    lcd.print(temperature, 0);

    if(temperature >= 42 && humidity >= 90)
    {
      lcd.setCursor(0,1);
      lcd.print("Sesuaikan udara!");
      pinMode(kipas, OUTPUT);
      bahaya();
    }
    else if(moisture <= 30)
    {
      lcd.setCursor(0,1);
      lcd.print("Pot kebanjiran!");
      pinMode(relay, INPUT);
      bahaya();
    }
    else if(moisture >= 90)
    {
      lcd.setCursor(0,1);
      lcd.print("Tambahkan air!");
      pinMode(relay, OUTPUT);
      bahaya();
    }
    else if(temperature >= 42)
    {
      lcd.setCursor(0,1);
      lcd.print("Suhu tinggi!");
      pinMode(kipas, OUTPUT);
      bahaya();
    }
    else if(temperature < 0)
    {
      lcd.setCursor(0,1);
      lcd.print("Suhu rendah!");
      pinMode(kipas, OUTPUT);
      bahaya();
    }
    else if(humidity >= 90 || humidity <= 20)
    {
      lcd.setCursor(0,1);
      lcd.print("Udara tidak aman!");
      pinMode(kipas, INPUT);
      bahaya();
    }
    else if(moisture >= 80 && moisture < 90)
    {
      lcd.setCursor(0,1);
      lcd.print("Awas kurang air!");
      pinMode(relay, OUTPUT);
      awas();
    }
    else if(moisture >= 30 && moisture < 40)
    {
      lcd.setCursor(0,1);
      lcd.print("Awas pot banjir!");
      pinMode(relay, INPUT);
      awas();
    }
    else if(temperature >= 37 && temperature < 42)
    {
      lcd.setCursor(0,1);
      lcd.print("Awas suhu tinggi!");
      pinMode(kipas, INPUT);
      awas();
    }
    else if(temperature >= 0 && temperature < 20)
    {
      lcd.setCursor(0,1);
      lcd.print("Awas suhu rendah!");
      pinMode(kipas, OUTPUT);
      awas();
    }
    else
    {
      lcd.setCursor(0,1);
      lcd.print("Kondisi mandali!");
      pinMode(kipas, INPUT);
      pinMode(relay, INPUT);
      normal();
    }
    if ((serInput == 'B' || serInput == 'D' || serInput == 'F' || serInput == 'G') && moisture >= 40)
    {
      pinMode(relay, OUTPUT);
    }
    if ((serInput == 'C' || serInput == 'E' || serInput == 'F' || serInput == 'G') && moisture >= 40)
    {
      pinMode(kipas, OUTPUT);
    }
  }
  else
  {
    mode = 0;
  }
  button = digitalRead(modPin);
  if(button == LOW)
  {
    if(mode < 3)
    {
      mode++;
    }
    else
    {
      mode = 0;
    }
  }
  delay(500);
  Serial.flush();
}

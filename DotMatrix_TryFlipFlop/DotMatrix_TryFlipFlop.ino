#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Max72xxPanel.h>

int pinCS = 10; // Attach CS to this pin, DIN to MOSI and CLK to SCK 
int numberOfHorizontalDisplays = 1;
int numberOfVerticalDisplays = 4;

Max72xxPanel matrix = Max72xxPanel(pinCS, numberOfHorizontalDisplays, numberOfVerticalDisplays);

int wait = 100; // In milliseconds
int x, i, y, j;

void strobe1(){
  for(j=0;j<4;j++)
  {
  for(y=0;y<2;y++)
  {
  for(i=0;i<=7;i++)
  {
    for(x=0;x<=7;x++)
    {
      matrix.drawPixel(x, i, 1);
      matrix.drawPixel(x+16, i, 1);
      matrix.write();
    }
  }
  delay(100);
  for(i=0;i<=7;i++)
  {
    for(x=0;x<=7;x++)
    {
      matrix.drawPixel(x, i, 0);
      matrix.drawPixel(x+16, i, 0);
      matrix.write();
    }
  }
  delay(100);
  }
  for(y=0;y<2;y++)
  {
  for(i=0;i<=7;i++)
  {
    for(x=0;x<=7;x++)
    {
      matrix.drawPixel(x+8, i, 1);
      matrix.drawPixel(x+24, i, 1);
      matrix.write();
    }
  }
  delay(100);
  for(i=0;i<=7;i++)
  {
    for(x=0;x<=7;x++)
    {
      matrix.drawPixel(x+8, i, 0);
      matrix.drawPixel(x+24, i, 0);
      matrix.write();
    }
  }
  delay(100);
  }
  }

  for(j=0;j<10;j++)
  {
  for(i=0;i<=7;i++)
  {
    for(x=0;x<=7;x++)
    {
      matrix.drawPixel(x, i, 1);
      matrix.drawPixel(x+8, i, 1);
      matrix.drawPixel(x+16, i, 0);
      matrix.drawPixel(x+24, i, 0);
      matrix.write();
    }
  }
  delay(100);
  for(i=0;i<=7;i++)
  {
    for(x=0;x<=7;x++)
    {
      matrix.drawPixel(x, i, 0);
      matrix.drawPixel(x+8, i, 0);
      matrix.drawPixel(x+16, i, 1);
      matrix.drawPixel(x+24, i, 1);
      matrix.write();
    }
  }
  delay(100);
  }
  matrix.fillScreen(LOW);
  matrix.write();
  delay(200);
}

void strobe2(){
  for(i=0;i<2;i++)
  {
    for(j=0;j<2;j++)
    {
    matrix.fillScreen(HIGH);
    matrix.write();
    delay(100);
    matrix.fillScreen(LOW);
    matrix.write();
    delay(100);
    }
    delay(500);
  }
}

void strobe3(){
  for(j=0;j<4;j++)
  {
  for(y=0;y<2;y++)
  {
  for(i=0;i<=7;i++)
  {
    for(x=0;x<=7;x++)
    {
      matrix.drawPixel(x+8, i, 1);
      matrix.drawPixel(x+16, i, 1);
      matrix.write();
    }
  }
  delay(100);
  for(i=0;i<=7;i++)
  {
    for(x=0;x<=7;x++)
    {
      matrix.drawPixel(x+8, i, 0);
      matrix.drawPixel(x+16, i, 0);
      matrix.write();
    }
  }
  delay(100);
  }
  for(y=0;y<2;y++)
  {
  for(i=0;i<=7;i++)
  {
    for(x=0;x<=7;x++)
    {
      matrix.drawPixel(x, i, 1);
      matrix.drawPixel(x+24, i, 1);
      matrix.write();
    }
  }
  delay(100);
  for(i=0;i<=7;i++)
  {
    for(x=0;x<=7;x++)
    {
      matrix.drawPixel(x, i, 0);
      matrix.drawPixel(x+24, i, 0);
      matrix.write();
    }
  }
  delay(100);
  }
  }
}

void setup() {

  matrix.setIntensity(15); // Use a value between 0 and 15 for brightness

// Adjust to your own needs
  matrix.setPosition(0, 0, 0); // The first display is at <0, 0>
  matrix.setPosition(1, 1, 0); // The second display is at <1, 0>
  matrix.setPosition(2, 2, 0); // The third display is at <2, 0>
  matrix.setPosition(3, 3, 0); // And the last display is at <3, 0>
//  ...
//  matrix.setRotation(0, 2);    // The first display is position upside down
 matrix.setRotation(3);    // The same hold for the last display
}

void loop() {
  //matrix.fillScreen(HIGH);
  strobe1();
  strobe2();
  strobe3();
  delay(wait);
}

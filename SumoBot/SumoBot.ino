// motor one
int enA = 11;
int in1 = 7;
int in2 = 6;
// motor two
int enB = 10;
int in3 = 5;
int in4 = 4;

int FLamp = 8;
int HazLamp = 13;

char blueToothVal;

void setup() {
  // put your setup code here, to run once:
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  pinMode(FLamp, OUTPUT);
  pinMode(HazLamp, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available())
  {
    blueToothVal=Serial.read();
  }
  
  if (blueToothVal=='W')
  {
    digitalWrite(FLamp, HIGH);
  }
  else if (blueToothVal=='w')
  {
    digitalWrite(FLamp, LOW);
  }

  if (blueToothVal=='X')
  {
    digitalWrite(HazLamp, HIGH);
  }
  else if (blueToothVal=='x')
  {
    digitalWrite(HazLamp, LOW);
  }
  
  if (blueToothVal=='F') //Maju
  {
     digitalWrite(in1, LOW);
     digitalWrite(in2, HIGH);  
     digitalWrite(in3, HIGH);
     digitalWrite(in4, LOW);
  
     analogWrite(enA, 255);
     analogWrite(enB, 255);
  }
  else if (blueToothVal=='G') //Maju Kiri
  {
     digitalWrite(in1, LOW);
     digitalWrite(in2, HIGH);  
     digitalWrite(in3, HIGH);
     digitalWrite(in4, LOW);
  
     analogWrite(enA, 180);
     analogWrite(enB, 255);
  }
  else if (blueToothVal=='I') //Maju Kanan
  {
     digitalWrite(in1, LOW);
     digitalWrite(in2, HIGH);  
     digitalWrite(in3, HIGH);
     digitalWrite(in4, LOW);
  
     analogWrite(enA, 255);
     analogWrite(enB, 180);
  }
  else if (blueToothVal=='L') //Belok Kiri
  {
     digitalWrite(in1, LOW);
     digitalWrite(in2, HIGH);  
     digitalWrite(in3, HIGH);
     digitalWrite(in4, LOW);
  
     analogWrite(enA, 0);
     analogWrite(enB, 255);
  }
  else if (blueToothVal=='R') //Belok Kanan
  {
     digitalWrite(in1, LOW);
     digitalWrite(in2, HIGH);  
     digitalWrite(in3, HIGH);
     digitalWrite(in4, LOW);
  
     analogWrite(enA, 255);
     analogWrite(enB, 0);
  }
  else if (blueToothVal=='B') //Mundur
  {
     digitalWrite(in1, HIGH);
     digitalWrite(in2, LOW);  
     digitalWrite(in3, LOW);
     digitalWrite(in4, HIGH);
  
     analogWrite(enA, 255);
     analogWrite(enB, 255);
  }
  else if (blueToothVal=='H') //Mundur Kiri
  {
     digitalWrite(in1, HIGH);
     digitalWrite(in2, LOW);  
     digitalWrite(in3, LOW);
     digitalWrite(in4, HIGH);
  
     analogWrite(enA, 180);
     analogWrite(enB, 255);
  }
  else if (blueToothVal=='J') //Mundur Kanan
  {
     digitalWrite(in1, HIGH);
     digitalWrite(in2, LOW);  
     digitalWrite(in3, LOW);
     digitalWrite(in4, HIGH);
  
     analogWrite(enA, 255);
     analogWrite(enB, 180);
  }
  else
  {
     digitalWrite(in1, LOW);
     digitalWrite(in2, LOW);  
     digitalWrite(in3, LOW);
     digitalWrite(in4, LOW);
  
     analogWrite(enA, 0);
     analogWrite(enB, 0);
  }

  delay(10);
}

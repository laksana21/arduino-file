float sensorCahaya;
int lampu = 6;

void setup() {
  // put your setup code here, to run once:
  pinMode(lampu, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  sensorCahaya = analogRead(A3);
  float pVolt0 = sensorCahaya / 1024 * 100;

  if(pVolt0 < 95)
  {
    digitalWrite(lampu, LOW);
  }
  else
  {
    digitalWrite(lampu, HIGH);
  }
}

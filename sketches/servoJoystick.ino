#include <Servo.h>
Servo ServoLR;
Servo ServoUD;
int vertpin = A0;
int horzpin = A1;

void setup() {
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  Serial.begin(9600);
  ServoUD.attach(10);
  ServoLR.attach(11);
}

void loop() {
  int vert = analogRead(A0);
  int horz = analogRead(A1);

  Serial.print("vert: ");
  Serial.print(vert);
  Serial.print("  horz: ");
  Serial.println(horz);
  int horzval = map(horz, 0, 1023, 0 ,180);
  int vertval = map(vert, 0, 1023, 0 ,180);
  ServoLR.write(horzval);
  ServoUD.write(vertval);
  

  delay(200); // optional, just to slow down spam
}

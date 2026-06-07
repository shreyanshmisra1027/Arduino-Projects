void setup() {
  // put your setup code here, to run once:
  pinMode(4, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(9, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(9, HIGH);
  delay(5000);
  digitalWrite(9, LOW);
  digitalWrite(7, HIGH);
  delay(1000);
  digitalWrite(7, LOW);
  digitalWrite(4, HIGH);
  delay(5000);
  digitalWrite(4, LOW);
}

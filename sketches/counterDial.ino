int pot = A0;

// 7 segment pins
int a = 2;
int b = 3;
int c = 4;
int d = 5;
int e = 6;
int f = 7;
int g = 8;

void setup() {
  pinMode(a, OUTPUT);
  pinMode(b, OUTPUT);
  pinMode(c, OUTPUT);
  pinMode(d, OUTPUT);
  pinMode(e, OUTPUT);
  pinMode(f, OUTPUT);
  pinMode(g, OUTPUT);
}

void loop() {

  int potValue = analogRead(pot);   // 0–1023
  int number = map(potValue, 0, 1023, 0, 9);      // converts to 0–9

  if (number == 0) zero();
  if (number == 1) one();
  if (number == 2) two();
  if (number == 3) three();
  if (number == 4) four();
  if (number == 5) five();
  if (number == 6) six();
  if (number == 7) seven();
  if (number == 8) eight();
  if (number == 9) nine();
}

// -------- Numbers --------

void zero() {
  digitalWrite(a,HIGH); digitalWrite(b,HIGH);
  digitalWrite(c,HIGH); digitalWrite(d,HIGH);
  digitalWrite(e,HIGH); digitalWrite(f,HIGH);
  digitalWrite(g,LOW);
}

void one() {
  digitalWrite(a,LOW); digitalWrite(b,HIGH);
  digitalWrite(c,HIGH); digitalWrite(d,LOW);
  digitalWrite(e,LOW); digitalWrite(f,LOW);
  digitalWrite(g,LOW);
}

void two() {
  digitalWrite(a,HIGH); digitalWrite(b,HIGH);
  digitalWrite(c,LOW);  digitalWrite(d,HIGH);
  digitalWrite(e,HIGH); digitalWrite(f,LOW);
  digitalWrite(g,HIGH);
}

void three() {
  digitalWrite(a,HIGH); digitalWrite(b,HIGH);
  digitalWrite(c,HIGH); digitalWrite(d,HIGH);
  digitalWrite(e,LOW);  digitalWrite(f,LOW);
  digitalWrite(g,HIGH);
}

void four() {
  digitalWrite(a,LOW);  digitalWrite(b,HIGH);
  digitalWrite(c,HIGH); digitalWrite(d,LOW);
  digitalWrite(e,LOW);  digitalWrite(f,HIGH);
  digitalWrite(g,HIGH);
}

void five() {
  digitalWrite(a,HIGH); digitalWrite(b,LOW);
  digitalWrite(c,HIGH); digitalWrite(d,HIGH);
  digitalWrite(e,LOW);  digitalWrite(f,HIGH);
  digitalWrite(g,HIGH);
}

void six() {
  digitalWrite(a,HIGH); digitalWrite(b,LOW);
  digitalWrite(c,HIGH); digitalWrite(d,HIGH);
  digitalWrite(e,HIGH); digitalWrite(f,HIGH);
  digitalWrite(g,HIGH);
}

void seven() {
  digitalWrite(a,HIGH); digitalWrite(b,HIGH);
  digitalWrite(c,HIGH); digitalWrite(d,LOW);
  digitalWrite(e,LOW);  digitalWrite(f,LOW);
  digitalWrite(g,LOW);
}

void eight() {
  digitalWrite(a,HIGH); digitalWrite(b,HIGH);
  digitalWrite(c,HIGH); digitalWrite(d,HIGH);
  digitalWrite(e,HIGH); digitalWrite(f,HIGH);
  digitalWrite(g,HIGH);
}

void nine() {
  digitalWrite(a,HIGH); digitalWrite(b,HIGH);
  digitalWrite(c,HIGH); digitalWrite(d,HIGH);
  digitalWrite(e,LOW);  digitalWrite(f,HIGH);
  digitalWrite(g,HIGH);
}

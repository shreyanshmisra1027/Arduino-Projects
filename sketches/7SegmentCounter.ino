int DP = 8;
int a = 3 ;
int b = 4 ;
int c = 7 ;
int d = 6 ;
int e = 5 ;
int f = 2 ;
int g = 1 ;
int wait = 1000;
void setup() {
  // put your setup code here, to run once:
pinMode(DP, OUTPUT);
pinMode(a, OUTPUT);
pinMode(b, OUTPUT);
pinMode(c, OUTPUT);
pinMode(d, OUTPUT);
pinMode(e, OUTPUT);
pinMode(f, OUTPUT);
pinMode(g, OUTPUT);
}

void loop() {
//Number 9
digitalWrite(a, HIGH);
digitalWrite(b, HIGH);
digitalWrite(c, HIGH);
digitalWrite(d, HIGH);
digitalWrite(f, HIGH);
digitalWrite(g, HIGH);
delay(wait);
digitalWrite(a, LOW);
digitalWrite(b, LOW);
digitalWrite(c, LOW);
digitalWrite(d, LOW);
digitalWrite(f, LOW);
digitalWrite(g, LOW);
//Number 8
digitalWrite(a, HIGH);
digitalWrite(b, HIGH);
digitalWrite(c, HIGH);
digitalWrite(d, HIGH);
digitalWrite(e, HIGH);
digitalWrite(f, HIGH);
digitalWrite(g, HIGH);
delay(wait);
digitalWrite(a, LOW);
digitalWrite(b, LOW);
digitalWrite(c, LOW);
digitalWrite(d, LOW);
digitalWrite(e, LOW);
digitalWrite(f, LOW);
digitalWrite(g, LOW);
//Number 7
digitalWrite(a, HIGH);
digitalWrite(b, HIGH);
digitalWrite(c, HIGH);
delay(wait);
digitalWrite(a, LOW);
digitalWrite(b, LOW);
digitalWrite(c, LOW);
//Number 6
digitalWrite(a, HIGH);
digitalWrite(c, HIGH);
digitalWrite(d, HIGH);
digitalWrite(e, HIGH);
digitalWrite(f, HIGH);
digitalWrite(g, HIGH);
delay(wait);
digitalWrite(a, LOW);
digitalWrite(c, LOW);
digitalWrite(d, LOW);
digitalWrite(e, LOW);
digitalWrite(f, LOW);
digitalWrite(g, LOW);
//Number 5
digitalWrite(a, HIGH);
digitalWrite(c, HIGH);
digitalWrite(d, HIGH);
digitalWrite(f, HIGH);
digitalWrite(g, HIGH);
delay(wait);
digitalWrite(a, LOW);
digitalWrite(c, LOW);
digitalWrite(d, LOW);
digitalWrite(f, LOW);
digitalWrite(g, LOW);
//Number 4
digitalWrite(b, HIGH);
digitalWrite(c, HIGH);
digitalWrite(f, HIGH);
digitalWrite(g, HIGH);
delay(wait);
digitalWrite(b, LOW);
digitalWrite(c, LOW);
digitalWrite(f, LOW);
digitalWrite(g, LOW);
//Number 3
digitalWrite(a, HIGH);
digitalWrite(b, HIGH);
digitalWrite(c, HIGH);
digitalWrite(d, HIGH);
digitalWrite(g, HIGH);
delay(wait);
digitalWrite(a, LOW);
digitalWrite(b, LOW);
digitalWrite(c, LOW);
digitalWrite(d, LOW);
digitalWrite(g, LOW);
//Number 2
digitalWrite(a, HIGH);
digitalWrite(b, HIGH);
digitalWrite(d, HIGH);
digitalWrite(e, HIGH);
digitalWrite(g, HIGH);
delay(wait);
digitalWrite(a, LOW);
digitalWrite(b, LOW);
digitalWrite(d, LOW);
digitalWrite(e, LOW);
digitalWrite(g, LOW);
//Number 1
digitalWrite(c, HIGH);
digitalWrite(b, HIGH);
delay(wait);
digitalWrite(c, LOW);
digitalWrite(b, LOW);
//Number 0
digitalWrite(a, HIGH);
digitalWrite(b, HIGH);
digitalWrite(c, HIGH);
digitalWrite(d, HIGH);
digitalWrite(e, HIGH);
digitalWrite(f, HIGH);
delay(wait);
digitalWrite(a, LOW);
digitalWrite(b, LOW);
digitalWrite(c, LOW);
digitalWrite(d, LOW);
digitalWrite(e, LOW);
digitalWrite(f, LOW);
//End flash
digitalWrite(DP, HIGH);
delay(500);
digitalWrite(DP, LOW);
delay(500);
digitalWrite(DP, HIGH);
delay(500);
digitalWrite(DP, LOW);
delay(500);
digitalWrite(DP, HIGH);
delay(500);
digitalWrite(DP, LOW);
delay(500);
digitalWrite(a, HIGH);
delay(500);
digitalWrite(b, HIGH);
delay(500);
digitalWrite(c, HIGH);
delay(500);
digitalWrite(d, HIGH);
delay(500);
digitalWrite(e, HIGH);
delay(500);
digitalWrite(f, HIGH);
delay(500);
digitalWrite(g, HIGH);

//off animation

delay(500);
delay(wait);
digitalWrite(a, LOW);
digitalWrite(d, LOW);
delay(500);
digitalWrite(b, LOW);
digitalWrite(f, LOW);
digitalWrite(e, LOW);
digitalWrite(c, LOW);
delay(500);
digitalWrite(g, LOW);

delay(2000);


}


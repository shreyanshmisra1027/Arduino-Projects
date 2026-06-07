int alog_read= A5;

void setup() {
  // put your setup code here, to run once:
 pinMode(alog_read, INPUT);
 pinMode(A2, OUTPUT);
 Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  float voltread = (analogRead(alog_read) / 1023.0) * 5.0;  
  float voltout= (analogRead(alog_read) /1023.0) * 255.0 ;
  analogWrite(A2, voltout);
  Serial.println(voltread);
  
}

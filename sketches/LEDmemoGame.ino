int ledPins[4] = {2,3,4,5};
int btnPins[4] = {7,8,9,10};

int sequence[50];
int level = 1;

void setup() {
  Serial.begin(9600);
  randomSeed(analogRead(A0));

  for(int i=0;i<4;i++){
    pinMode(ledPins[i], OUTPUT);
    pinMode(btnPins[i], INPUT_PULLUP);
  }
}

void flashLED(int i){
  digitalWrite(ledPins[i], HIGH);
  delay(350);
  digitalWrite(ledPins[i], LOW);
  delay(200);
}

int readButton(){
  while(true){
    for(int i=0;i<4;i++){
      if(digitalRead(btnPins[i]) == LOW){
        delay(20);
        while(digitalRead(btnPins[i]) == LOW);
        return i;
      }
    }
  }
}

void showSequence(){
  for(int i=0;i<level;i++){
    flashLED(sequence[i]);
  }
}

bool getInput(){
  for(int i=0;i<level;i++){
    int b = readButton();
    flashLED(b);
    if(b != sequence[i]) return false;
  }
  return true;
}

void gameOver(){
  Serial.println("Game Over");
  for(int k=0;k<6;k++){
    for(int i=0;i<4;i++) digitalWrite(ledPins[i], HIGH);
    delay(120);
    for(int i=0;i<4;i++) digitalWrite(ledPins[i], LOW);
    delay(120);
  }
  level = 1;
}

void loop(){

  sequence[level-1] = random(0,4);

  Serial.print("Level: ");
  Serial.println(level);

  showSequence();

  if(getInput()){
    level++;
    delay(600);
  } else {
    gameOver();
    delay(1000);
  }
}

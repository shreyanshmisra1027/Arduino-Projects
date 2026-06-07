#include <Keypad.h>
#include <TM1637Display.h>

// ---------- TM1637 ----------
#define CLK 3
#define DIO 2
TM1637Display display(CLK, DIO);

// ---------- Keypad ----------
const byte ROWS = 4;
const byte COLS = 4;

char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[ROWS] = {4,5,6,7};
byte colPins[COLS] = {8,9,10,11};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

// ---------- State ----------
char buffer[4] = {' ',' ',' ',' '};
bool commandMode = false;
bool animating = false;

// ---------- Helpers ----------
void clearBuffer() {
  for(int i=0;i<4;i++) buffer[i]=' ';
  display.clear();
}

void pushChar(char k) {
  buffer[0]=buffer[1];
  buffer[1]=buffer[2];
  buffer[2]=buffer[3];
  buffer[3]=k;
}

uint8_t enc(char c) {
  if(c>='0' && c<='9') return display.encodeDigit(c-'0');
  switch(c){
    case 'A': return 0x77;
    case 'B': return 0x7C;
    case 'C': return 0x39;
    case 'D': return 0x5E;
    default: return 0x00;
  }
}

void showBuffer() {
  uint8_t s[4];
  for(int i=0;i<4;i++) s[i]=enc(buffer[i]);
  display.setSegments(s);
}

bool stopRequested() {
  char k = keypad.getKey();
  if(k){
    animating=false;
    if(k=='*') clearBuffer();
    return true;
  }
  return false;
}

//
// ===== DESIGN A — revolving circles =====
//
void designA() {
  animating=true;
  uint8_t ring[6]={0x01,0x02,0x04,0x08,0x10,0x20};
  int p=0;

  while(animating){
    uint8_t s[4];
    for(int i=0;i<4;i++) s[i]=ring[(p+i)%6];
    display.setSegments(s);
    delay(110);
    p++;
    if(stopRequested()) return;
  }
}

//
// ===== DESIGN B — infinite snake =====
//
void designB() {
  animating = true;

  uint8_t path[6] = {0x01,0x02,0x04,0x08,0x10,0x20};
  int i = 0;

  while(animating) {
    uint8_t s[4] = {0,0,0,0};

    s[i%4] = path[i%6];
    s[(i+2)%4] = path[(i+3)%6];   // second chaser

    display.setSegments(s);
    delay(95);
    i++;

    if(stopRequested()) return;
  }
}


//
// ===== DESIGN C — wave =====
//
void designC() {
  animating = true;

  uint8_t barLevels[4] = {0x08, 0x48, 0x49, 0x7F}; // small → full

  while(animating) {

    // forward
    for(int pos=0; pos<4; pos++) {
      for(int lvl=0; lvl<4; lvl++) {
        uint8_t s[4]={0,0,0,0};
        s[pos] = barLevels[lvl];
        display.setSegments(s);
        delay(70);
        if(stopRequested()) return;
      }
    }

    // backward
    for(int pos=3; pos>=0; pos--) {
      for(int lvl=3; lvl>=0; lvl--) {
        uint8_t s[4]={0,0,0,0};
        s[pos] = barLevels[lvl];
        display.setSegments(s);
        delay(70);
        if(stopRequested()) return;
      }
    }
  }
}


//
// ===== DESIGN D — breathing pulse =====
//
void designD() {
  animating = true;

  uint8_t full[4] = {0x7F,0x7F,0x7F,0x7F};
  uint8_t s[4];

  while(animating) {

    // build up
    for(int i=0;i<4;i++) {
      for(int k=0;k<4;k++) s[k]=0;
      for(int k=0;k<=i;k++) s[k]=0x7F;

      display.setSegments(s);
      delay(120);
      if(stopRequested()) return;
    }

    // flash explosion
    for(int j=0;j<3;j++){
      display.setSegments(full);
      delay(60);
      display.clear();
      delay(60);
      if(stopRequested()) return;
    }

    // crumble away
    for(int i=3;i>=0;i--) {
      for(int k=0;k<4;k++) s[k]=0x7F;
      s[i] = 0;

      display.setSegments(s);
      delay(110);
      if(stopRequested()) return;
    }
  }
}


// ---------- Setup ----------
void setup() {
  display.setBrightness(6);
  clearBuffer();
}

// ---------- Loop ----------
void loop() {

  if(animating) return;

  char key = keypad.getKey();
  if(!key) return;

  if(key=='*'){
    clearBuffer();
    commandMode=false;
    return;
  }

  if(key=='#'){
    commandMode=true;
    return;
  }

  if(commandMode){
    commandMode=false;
    if(key=='A') designA();
    else if(key=='B') designB();
    else if(key=='C') designC();
    else if(key=='D') designD();
    clearBuffer();
    return;
  }

  pushChar(key);
  showBuffer();
}

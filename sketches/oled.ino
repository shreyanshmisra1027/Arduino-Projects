#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <math.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// Cube vertices
float cube[8][3] = {
  {-1,-1,-1}, {1,-1,-1}, {1,1,-1}, {-1,1,-1},
  {-1,-1, 1}, {1,-1, 1}, {1,1, 1}, {-1,1, 1}
};

// Edges between vertices
int edges[12][2] = {
  {0,1},{1,2},{2,3},{3,0},
  {4,5},{5,6},{6,7},{7,4},
  {0,4},{1,5},{2,6},{3,7}
};

float angle = 0;

void setup() {
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
}

void loop() {
  display.clearDisplay();

  float projected[8][2];

  for(int i=0;i<8;i++){
    float x = cube[i][0];
    float y = cube[i][1];
    float z = cube[i][2];

    // Rotate around Y
    float x1 = x*cos(angle) - z*sin(angle);
    float z1 = x*sin(angle) + z*cos(angle);

    // Rotate around X
    float y1 = y*cos(angle) - z1*sin(angle);
    float z2 = y*sin(angle) + z1*cos(angle);

    // Perspective projection
    float scale = 40 / (z2 + 4);
    projected[i][0] = x1 * scale + 64;
    projected[i][1] = y1 * scale + 32;
  }

  // Draw edges
  for(int i=0;i<12;i++){
    int a = edges[i][0];
    int b = edges[i][1];
    display.drawLine(
      projected[a][0], projected[a][1],
      projected[b][0], projected[b][1],
      SSD1306_WHITE
    );
  }

  display.display();
  angle += 0.05;
  delay(30);
}

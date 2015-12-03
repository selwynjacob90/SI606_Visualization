#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>
#include "Data.h"
#ifndef PSTR
 #define PSTR // Make Arduino Due happy
#endif

#define PIN 6

struct RGB {
  byte r;
  byte g;
  byte b;  
};
RGB green = { 128, 255, 0 };
RGB yellow = { 0, 255, 255 };
RGB red = { 255, 0, 0 };
RGB purple = { 178, 102, 255 };

Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(8, 8, PIN,
  NEO_MATRIX_LEFT     + NEO_MATRIX_TOP +
  NEO_MATRIX_ROWS + NEO_MATRIX_PROGRESSIVE,
  NEO_GRB            + NEO_KHZ800);

const uint16_t colors[] = {
  matrix.Color(255, 0, 0), matrix.Color(0, 255, 0), matrix.Color(0, 0, 255) };

void setup() {
  matrix.begin();
  matrix.setTextWrap(false);
  matrix.setBrightness(10);
  matrix.setTextColor(colors[0]);
  Serial.begin(9600);

}

uint8_t getRadiusForDuration (uint8_t duration) {
  if (duration < 21) {
    return 0;  
  }
  else if (duration < 31) {
    return 1;  
  }
  else if (duration < 61) {
    return 2;  
  }
  else {
    return 3;  
  }
}

RGB getColorForFeeling (uint8_t feeling) {
  if (feeling == RELAXING) {
    return green;
  }
  else if(feeling == FUN) {
    return yellow;
  }
  else if(feeling == INTENSE) {
    return red;
  }
  else {
    return purple;
  }  
}

void showFeeling (RGB currColor, uint8_t radius) {
  matrix.fillScreen(0);
  matrix.fillCircle(4, 4, radius, matrix.Color(currColor.r, currColor.g, currColor.b));
  matrix.show();
}

void showSignificance (RGB currColor) {
  matrix.fillScreen(0);
  for (uint8_t j=0; j<15; j++) {
    if(j%2 == 0) {
      matrix.fillCircle(4, 4, 3, matrix.Color(currColor.r, currColor.g, currColor.b));
      matrix.show();
    }
    else {
      matrix.fillScreen(0);
      matrix.show();
    }
    delay(100); 
  } 
}



void loop() {
  for(uint8_t i=0 ; i<18; i++) {
    if (duration[i] == 0) {
      matrix.fillScreen(0);
      matrix.show();
      delay(1000);
      continue;  
    }

    RGB currColor = getColorForFeeling(feeling[i]);    

    if (significance[i] == 10) {  
      showSignificance(currColor);
      continue;
    }
    
    uint8_t radius = getRadiusForDuration(duration[i]);
    showFeeling(currColor, radius);
    delay(1500);
  }
  
  delay(5000);
}

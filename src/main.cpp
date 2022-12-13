#include <Arduino.h>
#include <config.h>
#include <LEDMatrix.h>

const int pins[] = {A1, A2, A3, A4, A5, A6, A7, A8, A9, Clk, AB};

LEDMatrix Matrix(pins, ROWS, COLS);

int character = 0;
uint32_t curMillis;

char millisString[20];

void setup()
{
  Matrix.begin();
   curMillis = 3000;
}

void loop()
{
  Matrix.clearDisplay();
  // Matrix.setCursor(7,1);
  // itoa((micros()-curMillis), millisString, 10);
  // curMillis = micros();
  // Matrix.addStringGFX(millisString);
  //Matrix.addStringGFX("Das ist ein langer Test!");
  // if(millis()-curMillis > 70){
  //   curMillis = millis();
  //   Matrix.infiniteScroll(-1);
  // }
    Matrix.drawLine(1, 1, 10, 1);
  Matrix.drawLine(1, 1, 1, 3);
  Matrix.drawLine(0, 0, 8, 8);
  Matrix.drawLine(8, 8, 16, 0);
  //Matrix.drawRectangle(10,5, 1);
  Matrix.drawDisplay();
}

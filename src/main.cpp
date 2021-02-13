#include <Arduino.h>
#include <config.h>
#include <LEDMatrix.h>

const int pins[] = {A1, A2, A3, A4, A5, A6, A7, A8, A9, Clk, AB};

LEDMatrix Matrix(pins, ROWS, COLS);

int character = 0;
uint32_t curMillis;

void setup()
{
  Matrix.begin();
  Matrix.setCursor(7,20);
  Matrix.addStringGFX("Hello World!");
  curMillis = millis();
}

void loop()
{
  if(millis()-curMillis > 70){
    curMillis = millis();
    Matrix.infiniteScroll(-1);
  }
  Matrix.drawDisplay();
}

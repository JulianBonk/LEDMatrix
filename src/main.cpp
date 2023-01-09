#include <Arduino.h>
#include <config.h>
#include <LEDMatrix.h>

const int pins[] = {A1, A2, A3, A4, A5, A6, A7, A8, A9, Clk, AB};

LEDMatrix Matrix(pins, ROWS, COLS);

uint32_t curMillis;

void setup()
{
  Matrix.begin();
  Matrix.clearDisplay();
  Matrix.setCursor(7, 0);
  Matrix.addStringGFX("Das ist ein langer Test!");
  }

void loop()
{


  if (millis() - curMillis > 100)
  {
    curMillis = millis();
    Matrix.infiniteScroll(1);
    
  }
  Matrix.drawDisplay();
}

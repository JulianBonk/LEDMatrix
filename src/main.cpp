#include <Arduino.h>
#include <config.h>
#include <LEDMatrix.h>

const int pins[] = {A1, A2, A3, A4, A5, A6, A7, A8, A9, Clk, AB};

LEDMatrix Matrix(pins, ROWS, COLS);

void setup(){
  Matrix.begin();
  //Matrix.addString("   Es weihnachtet sehr!!!");
  Matrix.setCursor(8, 10);
  Matrix.addStringGFX("Es weihnachtet sehr!!");
}

void loop(){
  Matrix.drawDisplay();
}

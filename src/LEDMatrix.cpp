#include <Arduino.h>
#include "LEDMatrix.h"
#include <GFXFont.h>

LEDMatrix::LEDMatrix(const int pins[], int rows_in, int collumns_in)
{
  rows_ = rows_in;
  collumns_ = collumns_in;
  for (int i = 0; i < rows_in; i++)
    rowPins_[i] = pins[i];
  clockPin_ = pins[rows_in];
  AbPin_ = pins[rows_in + 1];
  Display = new unsigned char[rows_in * collumns_in];
  cursorX_ = 0;
  cursorY_ = 0;
  clearDisplay();
}

LEDMatrix::~LEDMatrix()
{
}

void LEDMatrix::infiniteScrollLeft1(){
  int index = 0;
  char firstCollumn[collumns_];
  for(int i = 0; i<rows_;i++){
    firstCollumn[i] = Display[i*collumns_];
  }
  for (int col = 0; col < collumns_; col++)
  {
    for (int row = 0; row < rows_; row++)
    {
      index = collumns_ * row + col;
      Display[index] = Display[index] << 1;
      if (col != collumns_ - 1){
        Display[index] |= (Display[index + 1] / 128) * 0b00000001;
      } else{
        Display[index] |= (firstCollumn[row] / 128) * 0b00000001;
      }
    }
  }
}

void LEDMatrix::infiniteScrollLeft8(){
  char firstCollumn[collumns_];
  for(int i = 0; i<rows_;i++){
    firstCollumn[i] = Display[i*collumns_];
  }

  int index = 0;
  for (int col = 0; col < collumns_; col++)
  {
    for (int row = 0; row < rows_; row++)
    {
      index = row * collumns_ + col;
      if (col != collumns_-1)
      {
        Display[index] = Display[index + 1];
      }
      else
      {
        Display[index] = firstCollumn[row];
      }
    }
  }
}

void LEDMatrix::infiniteScrollRight1(){
  int index = 0;
  char lastCollumn[collumns_];
  for(int i = 0; i<rows_;i++){
    lastCollumn[i] = Display[((i+1)*collumns_)-1];
  }
  for (int col = collumns_ - 1; col >= 0; col--)
  {
    for (int row = 0; row < rows_; row++)
    {
      index = collumns_ * row + col;
      Display[index] = Display[index] >> 1;
      if (col != 0){
        Display[index] |= (Display[index - 1] % 2) * 0b10000000;
      } else{
        Display[index] |= (lastCollumn[row] % 2) * 0b10000000;
      }
    }
  }
}

void LEDMatrix::infiniteScrollRight8(){
  int index = 0;
  char lastCollumn[collumns_];
  for(int i = 0; i<rows_;i++){
    lastCollumn[i] = Display[((i+1)*collumns_)-1];
  }
  for (int col = collumns_ - 1; col >= 0; col--)
  {
    for (int row = 0; row < rows_; row++)
    {
      index = row * collumns_ + col;
      if (col != 0)
      {
        Display[index] = Display[index - 1];
      }
      else
      {
        Display[index] = lastCollumn[row];
      }
    }
  }
}

void LEDMatrix::infiniteScrollLeftn(int l)
{
  for (int i = 0; i < l / 8; i++)
  {
    infiniteScrollLeft8();
  }
  for (int i = 0; i < l % 8; i++)
  {
    infiniteScrollLeft1();
  }
}

void LEDMatrix::infiniteScrollRightn(int r)
{
  for (int i = 0; i < r / 8; i++)
  {
    infiniteScrollRight8();
  }
  for (int i = 0; i < r % 8; i++)
  {
    infiniteScrollRight1();
  }
}

void LEDMatrix::infiniteScroll(int scrollAmount)
{
  if (scrollAmount < 0)
    infiniteScrollLeftn(abs(scrollAmount));
  if (scrollAmount > 0)
    infiniteScrollRightn(scrollAmount);
}

void LEDMatrix::setPixel(int row, int col, bool val)
{
  if (val)
  {
    Display[row * collumns_ + col / 8] |= 0x01 << (7 - (col % 8));
  }
  else
  {
    Display[row * collumns_ + col / 8] &= ~(0x01 << (7 - (col % 8)));
  }
}

void LEDMatrix::setCursor(int row, int col)
{
  cursorX_ = col;
  cursorY_ = row;
}

void LEDMatrix::addCharGFX(const char character)
{
  if(cursorX_ < collumns_*8 &&
     cursorY_ < rows_){
   int bitmapOffset = GFXGlyph[character - 0x20][0];
   int width = GFXGlyph[character - 0x20][1];
   int height = GFXGlyph[character - 0x20][2];
   int xAdvance = GFXGlyph[character - 0x20][3];
   int xOffset = GFXGlyph[character - 0x20][4];
   int yOffset = GFXGlyph[character - 0x20][5];

  int cursorXTemp = cursorX_ + xOffset;
  int cursorYTemp = cursorY_ + yOffset;

  bool set = false;

  for (int i = 0; i < height; i++)
  {
    for (int j = 0; j < width; j++)
    {
      set = GFXBitmap[bitmapOffset+(i*width+j)/8] & 0b10000000 >> (i*width+j)%8;
      if(cursorXTemp + j < collumns_*8 &&
         cursorYTemp + i < rows_){
      setPixel(cursorYTemp + i, cursorXTemp + j, set);
         }
    }
  }
  cursorX_ += xAdvance;
  }
}

void LEDMatrix::addStringGFX(const char *input){
  for (uint i = 0; i < strlen(input); i++)
  {
    addCharGFX(input[i]);
  }
}

void LEDMatrix::begin()
{
  pinMode(rowPins_[0], OUTPUT);
  pinMode(rowPins_[1], OUTPUT);
  pinMode(rowPins_[2], OUTPUT);
  pinMode(rowPins_[3], OUTPUT);
  pinMode(rowPins_[4], OUTPUT);
  pinMode(rowPins_[5], OUTPUT);
  pinMode(rowPins_[6], OUTPUT);
  pinMode(rowPins_[7], OUTPUT);
  pinMode(rowPins_[8], OUTPUT);

  pinMode(clockPin_, OUTPUT);
  pinMode(AbPin_, OUTPUT);

  clearAll();

  digitalWrite(AbPin_, LOW);

  clearDisplay();
  cursorX_ = 0;
  cursorY_ = 0;
}

void LEDMatrix::scrollRight1()
{
  int index = 0;
  for (int col = collumns_ - 1; col >= 0; col--)
  {
    for (int row = 0; row < rows_; row++)
    {
      index = collumns_ * row + col;
      Display[index] = Display[index] >> 1;
      if (col != 0)
        Display[index] |= (Display[index - 1] % 2) * 0b10000000;
    }
  }
}

void LEDMatrix::scrollLeft1()
{
  int index = 0;
  for (int col = 0; col < collumns_; col++)
  {
    for (int row = 0; row < rows_; row++)
    {
      index = collumns_ * row + col;
      Display[index] = Display[index] << 1;
      if (col != collumns_ - 1)
        Display[index] |= (Display[index + 1] / 128) * 0b00000001;
    }
  }
}

void LEDMatrix::scrollRight8()
{
  int index = 0;
  for (int col = collumns_ - 1; col >= 0; col--)
  {
    for (int row = 0; row < rows_; row++)
    {
      index = row * collumns_ + col;
      if (col != 0)
      {
        Display[index] = Display[index - 1];
      }
      else
      {
        Display[index] = 0x00;
      }
    }
  }
}

void LEDMatrix::scrollLeft8()
{
  int index = 0;
  for (int col = 0; col < collumns_; col++)
  {
    for (int row = 0; row < rows_; row++)
    {
      index = row * collumns_ + col;
      if (col != collumns_-1)
      {
        Display[index] = Display[index + 1];
      }
      else
      {
        Display[index] = 0x00;
      }
    }
  }
}

void LEDMatrix::scrollLeftn(int l)
{
  for (int i = 0; i < l / 8; i++)
  {
    scrollLeft8();
  }
  for (int i = 0; i < l % 8; i++)
  {
    scrollLeft1();
  }
}

void LEDMatrix::scrollRightn(int r)
{
  for (int i = 0; i < r / 8; i++)
  {
    scrollRight8();
  }
  for (int i = 0; i < r % 8; i++)
  {
    scrollRight1();
  }
}

void LEDMatrix::clearDisplay()
{
  for (int i = 0; i < rows_ * collumns_; i++)
  {
    Display[i] = 0x00;
  }
}

void LEDMatrix::clearAll()
{
  for (int i = 0; i < rows_; i++)
  {
    digitalWrite(rowPins_[i], HIGH);
  }
}

void LEDMatrix::clearRow(int row)
{
  digitalWrite(rowPins_[row], HIGH);
}

void LEDMatrix::setRow(int row)
{
  digitalWrite(rowPins_[row], LOW);
}

void LEDMatrix::drawDisplay()
{
  for (int row = 0; row < rows_; row++)
  {
    for (int col = 0; col < (collumns_ * 8); col++)
    {
      digitalWriteFast(digitalPinToPinName(clockPin_), LOW);
      bool write = Display[row * collumns_ + col / 8] & (0b1 << (7 - (col % 8)));
      digitalWrite(AbPin_, write);
      digitalWriteFast(digitalPinToPinName(clockPin_), HIGH);
      digitalWrite(AbPin_, LOW);
    }
    setRow(row);
    delayMicroseconds(50);
    clearRow(row);
    delayMicroseconds(100);
  }
}

void LEDMatrix::scroll(int scrollAmount)
{
  if (scrollAmount < 0)
    scrollLeftn(abs(scrollAmount));
  if (scrollAmount > 0)
    scrollRightn(scrollAmount);
}
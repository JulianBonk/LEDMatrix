#include <Arduino.h>
#include "LEDMatrix.h"
#include <CustomFont.h>

LEDMatrix::LEDMatrix(const int pins[], int rows_in, int collumns__in)
{
  rows_ = rows_in;
  collumns_ = collumns__in;
  for(uint i = 0; i < 9;i++) rowPins_[i] = pins[i];
  clockPin_ = pins[9];
  AbPin_ = pins[10];

  for(int i = 0; i< rows_*collumns_;i++){
    Display[i] = 0x00;
  }
}

LEDMatrix::~LEDMatrix()
{
}

void LEDMatrix::begin(){
  //for(int i = 0; i< rows_+2; i++){
    //pinMode(i, OUTPUT);
    //digitalWrite(i, i>=rows_?HIGH:LOW);
  //}

   // put your setup code here, to run once:
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  pinMode(A3, OUTPUT);
  pinMode(A4, OUTPUT);
  pinMode(A5, OUTPUT);
  pinMode(A6, OUTPUT);
  pinMode(A7, OUTPUT);
  pinMode(A8, OUTPUT);
  pinMode(A9, OUTPUT);

  pinMode(Clk, OUTPUT);
  pinMode(AB, OUTPUT);

  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(A1, HIGH);
  digitalWrite(A2, HIGH);
  digitalWrite(A3, HIGH);
  digitalWrite(A4, HIGH);
  digitalWrite(A5, HIGH);
  digitalWrite(A6, HIGH);
  digitalWrite(A7, HIGH);
  digitalWrite(A8, HIGH);
  digitalWrite(A9, HIGH);

  digitalWrite(AB, LOW);

  clearDisplay();
}

void LEDMatrix::clearAll(){
  for(int i = 0; i< rows_; i++){
    digitalWrite(i, HIGH);
  }
}



void LEDMatrix::setRow(int row){
 digitalWrite(rowPins_[row], LOW);
}

void LEDMatrix::addString(const char *input){
  for(int i= strlen(input)-1; i>=0; i--){
    addChar(input[i]);
    if(i!=0) scrollRightn(5);
  }

}

void LEDMatrix::addChar(char character){
  int fontIndex = (character - 0x20)*8;
  for(int i = 0; i<8; i++){
      Display[i*collumns_]&=0b11100000;
      Display[i*collumns_]|=fontChar[fontIndex+i];
  }
}


void LEDMatrix::scrollRight1(){
  int index = 0;
 for(int col = collumns_-2; col >= 0; col--) {
    for(int row = 0; row<rows_; row++){
      index = collumns_*row + col;
      Display[index] = Display[index] >> 1;
      if(col!=0) Display[index] |= (Display[index-1] % 2) * 0b10000000;
    }
 }
}

void LEDMatrix::scrollLeft1(){
  int index = 0;
 for(int col = 0; col <collumns_-1 ; col++) {
    for(int row = 0; row<rows_; row++){
      index = collumns_*row + col;
      Display[index] = Display[index] << 1;     //linkesfasdfasdfdfdsfsdfsdfsdfsjmnkhjkjhkhjkjhkhjk
      if(col!=collumns_-2) 
      Display[index] |= (Display[index+1] / 128) * 0b00000001;
    }  
 }
}

void LEDMatrix::scrollRight8(){
    int DisplayIndex=0;
   for(int col = collumns_-2; col >=0; col --){
     for(int row = 0; row <rows_; row++){
       DisplayIndex = row*collumns_+col;
       if(col >0){
        Display[DisplayIndex] = Display[DisplayIndex-1];   
       } else{
         Display[DisplayIndex] = Display[row*collumns_];
       }    
     }
   }
}



void LEDMatrix::scrollLeft8(){
   int DisplayIndex=0;
   for(int col = 0; col <collumns_-1; col ++){
     for(int row = 0; row <rows_; row++){
       DisplayIndex = row*collumns_+col;
       if(col != collumns_){
        Display[DisplayIndex] = Display[DisplayIndex+1];   
       } else{
         Display[DisplayIndex] = 0x00;
       }    
     }
   }
}

void LEDMatrix::slowClear(){
 for(int col = 19; col >= 0; col--) {
    for(int row = 0; row<9; row++){
      Display[20*row + col] = Display[20*row +col] >> 1;
    }
 }
}

void LEDMatrix::scrollLeftn(int l){
  for(int i =0;i<l/8;i++){
    scrollLeft8();
  }
  for(int i = 0; i<l%8;i++){
    scrollLeft1();
  }
}

void LEDMatrix::scrollRightn(int r){
  for(int i =0;i<r/8;i++){
    scrollRight8();
  }
  for(int i = 0; i<r%8;i++){
    scrollRight1();
  }
}



void LEDMatrix::clearDisplay(){
  for(uint i = 0; i < rows_*collumns_; i++){
  Display[i] = 0x55;
  }
}

void LEDMatrix::drawDisplay(){
  for(int row = 0; row <rows_; row++){
    for(int col = 8; col <168; col++){
      digitalWrite(clockPin_, LOW);
      bool write = Display[row*collumns_+col/8] & (0b1<<(7-(col%8)));
      digitalWrite(AbPin_, write);
      digitalWrite(clockPin_, HIGH);
      digitalWrite(AbPin_, LOW);
    }
clearAll();
setRow(row);
delayMicroseconds(300);
clearAll();
delayMicroseconds(5);
  }
}
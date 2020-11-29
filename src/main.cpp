#include <Arduino.h>
#include <CustomFont.h>
#include <stdio.h>
#include <malloc.h>

#define A1 20
#define A2 19
#define A3 15
#define A4 12
#define A5 11
#define A6 8
#define A7 31
#define A8 30
#define A9 21

#define Clk 25
#define AB 24
#define ROWS 9
#define COLS 22

//unsigned char Display[198];
unsigned char Display[] = {
  0x01, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02,
  0x01, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0E, 0x00, 0x00, 0x09, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x01, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0A, 0x00, 0x00, 0x13, 0x0A, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x01, 0x02, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x0C, 0x00, 0x00, 0x15, 0x0A, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x01, 0x02, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x0A, 0x00, 0x00, 0x17, 0x1F, 0x00, 0x55, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x01, 0x02, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x0E, 0x00, 0x00, 0x10, 0x11, 0x00, 0x00, 0x00, 0x55, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x01, 0x02, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x55, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x01, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x01, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

//9x20

  

void addChar(const char character); //Auf Tims risiko ohne unsigned  // jULIAN HATTE RECHT
void addString(const char *input);   
void clearAll();
void setRow(int row);
void drawDisplay();
void clearDisplay();
void scrollRight8();
void scrollRight1();
void scrollRightn(int r);
void scrollLeft1();
void scrollLeft8();
void scrollLeftn(int l);
void slowClear();
void autoScroll(const char *input);

//////////////////////////////////////////////////////////////////////////////////////////////////
///////////STARTUP
//////////////////////////////////////////////////////////////////////////////////////////////////

void setup(){
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
  //addChar('C');
  addString(" BibbaBonk ft. Bergemann");
  scrollRightn(16);
}

//////////////////////////////////////////////////////////////////////////////////////////////////
///////////LOOP
//////////////////////////////////////////////////////////////////////////////////////////////////
int j =0;

void loop(){  
  
drawDisplay();
 
 j++;
 if(j > 100){
  j = 0;
  //scrollRight8();
   
 }
}

//////////////////////////////////////////////////////////////////////////////////////////////////
///////////Functions
//////////////////////////////////////////////////////////////////////////////////////////////////
/*void autoScroll(const char* input){

    for(int i= strlen(input)-1; i>=0; i--){
      addChar(input[i]);
      if(i!=0) scrollRightn(5);
    }
  }
}
*/
void addString(const char *input){
  for(int i= strlen(input)-1; i>=0; i--){
    addChar(input[i]);
    if(i!=0) scrollRightn(5);
  }

}

void addChar(char character){
  int fontIndex = (character - 0x20)*8;
  for(int i = 0; i<8; i++){
      Display[i*COLS]&=0b11100000;
      Display[i*COLS]|=fontChar[fontIndex+i];
  }
}

void scrollRight1(){
  int index = 0;
 for(int col = COLS-2; col >= 0; col--) {
    for(int row = 0; row<ROWS; row++){
      index = COLS*row + col;
      Display[index] = Display[index] >> 1;
      if(col!=0) Display[index] |= (Display[index-1] % 2) * 0b10000000;
    }
    
 }
}

void scrollLeft1(){
  int index = 0;
 for(int col = 0; col <20 ; col++) {
    for(int row = 0; row<9; row++){
      index = 20*row + col;
      Display[index] = Display[index] << 1;
      if(col!=19) 
      Display[index] |= (Display[index+1] / 128) * 0b00000001;
    }
    
 }

}

void scrollLeft8(){
   int DisplayIndex=0;
   for(int col = 0; col <=19; col ++){
     for(int row = 0; row <9; row++){
       DisplayIndex = row*20+col;
       if(col != 19){
        Display[DisplayIndex] = Display[DisplayIndex+1];   
       } else{
         Display[DisplayIndex] = 0x00;
       }    
     }
   }
}

void slowClear(){
 for(int col = 19; col >= 0; col--) {
    for(int row = 0; row<9; row++){
      Display[20*row + col] = Display[20*row +col] >> 1;
    }
 }
}

void scrollLeftn(int l){
  for(int i =0;i<l/8;i++){
    scrollLeft8();
  }
  for(int i = 0; i<l%8;i++){
    scrollLeft1();
  }
}

void scrollRightn(int r){
  for(int i =0;i<r/8;i++){
    scrollRight8();
  }
  for(int i = 0; i<r%8;i++){
    scrollRight1();
  }
}


void scrollRight8(){
    int DisplayIndex=0;
   for(int col = COLS; col >=0; col --){
     for(int row = 0; row <ROWS-1; row++){
       DisplayIndex = row*COLS+col;
       if(col >0){
        Display[DisplayIndex] = Display[DisplayIndex-1];   
       } else{
         Display[DisplayIndex] = 0x00;
       }    
     }
   }
}

void clearAll(){
  digitalWrite(A1, HIGH);
  digitalWrite(A2, HIGH);
  digitalWrite(A3, HIGH);
  digitalWrite(A4, HIGH);
  digitalWrite(A5, HIGH);
  digitalWrite(A6, HIGH);
  digitalWrite(A7, HIGH);
  digitalWrite(A8, HIGH);
  digitalWrite(A9, HIGH);
}

void setRow(int row){
  switch (row)
  {
  case 0: digitalWrite(A1, LOW);
    break;
  case 1: digitalWrite(A2, LOW);
    break;
  case 2: digitalWrite(A3, LOW);
    break;
  case 3: digitalWrite(A4, LOW);
    break;
  case 4: digitalWrite(A5, LOW);
    break;
  case 5: digitalWrite(A6, LOW);
    break;
  case 6: digitalWrite(A7, LOW);
    break;
  case 7: digitalWrite(A8, LOW);
    break;
  case 8: digitalWrite(A9, LOW);
    break;
  
  default: clearAll();
    break;
  }
}

void clearDisplay(){
  for(uint i = 0; i < sizeof(Display); i++){
  Display[i] = 0x00;
  }
}

void drawDisplay(){
  for(int row = 0; row <ROWS; row++){
    for(int col = 8; col <168; col++){
      digitalWrite(Clk, LOW);
      digitalWrite(AB, (Display[row*COLS+col/8] & (0b1<<(7-(col%8))))? HIGH:LOW);
      digitalWrite(Clk, HIGH);
      digitalWrite(AB, LOW);
    }
clearAll();
setRow(row);
delayMicroseconds(300);
clearAll();
delayMicroseconds(5);
  }
}
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

class LEDMatrix{

private:
//Variables
    int rows_;
    int collumns_;
    int clockPin_;
    int AbPin_;
    int rowPins_[9];
    unsigned char Display[];
//Functions  
    void clearAll();
    void setRow(int row);

public:
//Functions
    void begin();
    void addChar(const char character);
    void addCharGFX(const char character);
    void addString(const char *input); 
    void drawDisplay();
    void clearDisplay();
    void scrollRight8();
    void scrollRight1();
    void scrollRightn(int r);
    void scrollLeft1();
    void scrollLeft8();
    void scrollLeftn(int l);
    void slowClear();
//Constructor/Deconstructor
    LEDMatrix(const int pins[], int rows, int cols);
    ~LEDMatrix();
};

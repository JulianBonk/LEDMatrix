class LEDMatrix{

private:
//Variables
    int rows_;
    int collumns_;
    int clockPin_;
    int AbPin_;
    int rowPins_[9];
    unsigned char *Display;
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
    LEDMatrix(int pins[], int rows, int cols);
    ~LEDMatrix();
};

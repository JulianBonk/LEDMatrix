class LEDMatrix{

private:
//Variables
    int rows_;
    int collumns_;
    int clockPin_;
    int AbPin_;
    int rowPins_[9];
    int cursorX_;
    int cursorY_;
    unsigned char *Display;

//Functions  
    void clearAll();
    void clearRow(int row);
    void setRow(int row);
    void scrollRight8();
    void scrollRight1();
    void scrollLeft1();
    void scrollLeft8();
    void scrollRightn(int r);
    void scrollLeftn(int l);
    void addCharGFX(const char character);
    void setPixel(int row, int col, bool val);  

public:
//Functions
    void begin();      
    void addStringGFX(const char *input); 
    void clearDisplay();
    void scroll(int scrollAmount);  
    void setCursor(int row, int col);
    void drawDisplay();

//Constructor/Deconstructor
    LEDMatrix(const int pins[], int rows, int cols);
    ~LEDMatrix();
};

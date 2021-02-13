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
    void addCharGFX(const char character);
    void setPixel(int row, int col, bool val); 

    void scrollRight8();
    void scrollRight1();
    void scrollRightn(int r);
    void scrollLeft8();
    void scrollLeft1();  
    void scrollLeftn(int l);

    void infiniteScrollRight8();
    void infiniteScrollRight1();
    void infiniteScrollRightn(int r);
    void infiniteScrollLeft8();
    void infiniteScrollLeft1();
    void infiniteScrollLeftn(int l);
public:
//Functions
    void begin();  
    void clearDisplay(); 
    void drawDisplay();   
    void addStringGFX(const char *input); 
    void scroll(int scrollAmount);  
    void infiniteScroll(int scrollAmount);
    void setCursor(int row, int col);

//Constructor/Deconstructor
    LEDMatrix(const int pins[], int rows, int cols);
    ~LEDMatrix();
};

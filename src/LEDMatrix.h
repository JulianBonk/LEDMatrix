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
    void sortPoints(int* x1, int* y1, int* x2, int* y2);
    void drawStraightLine(int x1, int y1, int x2, int y2);
    void drawDiagonal(int x1, int y1, int x2, int y2);

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
    void setCursor(int col, int row);
    void drawRectangle(int width, int height, int thickness);
    void drawSquare(int width, int thickness);
    void drawLine(int x1, int y1, int x2, int y2);

//Constructor/Deconstructor
    LEDMatrix(const int pins[], int rows, int cols);
    ~LEDMatrix();
};

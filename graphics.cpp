struct Equation{
    double coeff1;
    double coeff2;
    double coeff3;
};

struct CoordinateCenter{
    int x;
    int y;
};

enum WhatThefirstCoeff{
    POSITIVE,
    NEGATIVE,
    ZERO
};

enum DirectionOfShift{
    UP,
    DOWN,
    RIGHT,
    LEFT,
    DEFAULT
};

enum Button{
    rectangleZoomInX = 0,
    rectangleZoomOutX = 1,
    rectangleZoomInY = 2,
    rectangleZoomOutY = 3,
    NOTPRESSED = 4
};

struct Rect{
    int x0;
    int y0;
    int x1;
    int y1;
};

void printTitleForGraphicMode();
bool enterCoeffs(Equation* equation);
void graphOfTheEquation(int lengthX, int lengthY, Equation equation1, double* scaleX, double* scaleY, CoordinateCenter* center);
void getStringAnswers(double coeffs[], double* x1, double* x2, char sol1[], char sol2[], int lengthStr);
void doubleToString(double a, char str[], int lengthStr);
void printCoordinateAxes(CoordinateCenter center, int lengthX, int lengthY);
void drawParabola(double coeffs[], double scaleX, double scaleY, CoordinateCenter center, int lengthX);
void drawAxisMarkings(CoordinateCenter center, int lengthX, int lengthY, double scaleX, double scaleY);            
void drawCorrectAnswers(CoordinateCenter center, double scaleX, double sol1, double sol2,
                        char str1sol[], char str2sol[], int lengthX, int lengthY);
void drawZoomButtons(Rect buttons[], int lengthX, int lengthY);         
bool shiftButtonPressCheck(DirectionOfShift* direction); 
void shiftGraphic(DirectionOfShift direction, CoordinateCenter* center);  
Button zoomButtonPressCheck(Rect buttons[], int* mouseState);
bool handleButtonPress(Button button, double* scaleX, double* scaleY);
bool mouseInRectangle(Rect rectangle);
void moveGraphByMouse(CoordinateCenter* center);            


void graphicMode(){
    printTitleForGraphicMode();
    Equation equation = {};
    while(!enterCoeffs(&equation)){
        printf("Invalid enter!!!!!\n");
        printf("Enter the coefficients again:\n");
    }

    int lengthX = 1200;
    int lengthY = 800;

    CoordinateCenter center = {lengthX / 2, lengthY / 2};
    txClearConsole();
    txCreateWindow (lengthX, lengthY);

    double scaleX = 1;
    double scaleY = 1;

    while(true){
        graphOfTheEquation(lengthX, lengthY, equation, &scaleX, &scaleY, &center);
        txSetFillColor(TX_BLACK);
        txClear();
    }
}

void graphOfTheEquation(int lengthX, int lengthY, Equation equation1, double* scaleX, double* scaleY, CoordinateCenter* center){
    // Rect rectangleZoomInX =  {.x0 = (int) (0.85 * lengthX), .y0 = (int) (0.85 * lengthY), 
    //                           .x1 = (int) (0.90 * lengthX), .y1 = (int) (0.88 * lengthY)};
    // Rect rectangleZoomOutX = {.x0 = (int) (0.85 * lengthX), .y0 = (int) (0.90 * lengthY), 
    //                           .x1 = (int) (0.90 * lengthX), .y1 = (int) (0.93 * lengthY)};
                            
    // Rect rectangleZoomInY =  {.x0 = (int) (0.77 * lengthX), .y0 = (int) (0.85 * lengthY), 
    //                           .x1 = (int) (0.82 * lengthX), .y1 = (int) (0.88 * lengthY)};
    // Rect rectangleZoomOutY = {.x0 = (int) (0.77 * lengthX), .y0 = (int) (0.90 * lengthY), 
    //                           .x1 = (int) (0.82 * lengthX), .y1 = (int) (0.93 * lengthY)};
    
    Rect buttons[4] = {}; 
    buttons[rectangleZoomInX] =  {.x0 = (int) (0.85 * lengthX), .y0 = (int) (0.85 * lengthY), 
                                  .x1 = (int) (0.90 * lengthX), .y1 = (int) (0.88 * lengthY)};    
    buttons[rectangleZoomOutX] = {.x0 = (int) (0.85 * lengthX), .y0 = (int) (0.90 * lengthY), 
                                  .x1 = (int) (0.90 * lengthX), .y1 = (int) (0.93 * lengthY)};       

    buttons[rectangleZoomInY] =  {.x0 = (int) (0.77 * lengthX), .y0 = (int) (0.85 * lengthY), 
                                  .x1 = (int) (0.82 * lengthX), .y1 = (int) (0.88 * lengthY)};   
    buttons[rectangleZoomOutY] = {.x0 = (int) (0.77 * lengthX), .y0 = (int) (0.90 * lengthY), 
                                  .x1 = (int) (0.82 * lengthX), .y1 = (int) (0.93 * lengthY)};  

    double x1 = 0, x2 = 0;
    double coeffs[] = {equation1.coeff1, equation1.coeff2, equation1.coeff3};

    char sol1Str[25] = {}, sol2Str[25] = {};
    getStringAnswers(coeffs, &x1, &x2, sol1Str, sol2Str, sizeof(sol1Str));

    printCoordinateAxes(*center, lengthX, lengthY);
    drawAxisMarkings(*center, lengthX, lengthY, *scaleX, *scaleY);
    drawParabola(coeffs, *scaleX, *scaleY, *center, lengthX);
    drawCorrectAnswers(*center, *scaleX, x1, x2, sol1Str, sol2Str, lengthX, lengthY);
    drawZoomButtons(buttons, lengthX, lengthY);

    int mouseState = txMouseButtons();
    while(true){
        DirectionOfShift direction = DEFAULT;
        if(shiftButtonPressCheck(&direction)){
            shiftGraphic(direction, center);
            txSleep(10);
            break;
        }
        else if(txMouseButtons() == 1){
            Button button = zoomButtonPressCheck(buttons, &mouseState);
            if(!handleButtonPress(button, scaleX, scaleY)){
                moveGraphByMouse(center);
            };
            break;
        }
    }
}

void getStringAnswers(double coeffs[], double* x1, double* x2, char sol1[], char sol2[], int lengthStr){
    solveQuadraticEquation(coeffs, x1, x2);
    doubleToString(*x1, sol1, lengthStr);
    doubleToString(*x2, sol2, lengthStr);
}

void printCoordinateAxes(CoordinateCenter center, int lengthX, int lengthY){
    txLine(0, center.y, lengthX, center.y);
    txLine(center.x, 0, center.x, lengthY);
}

void doubleToString(double a, char str[], int lengthStr){
    snprintf(str, lengthStr, "%.4g", a);
}

void drawParabola(double coeffs[], double scaleX, double scaleY, CoordinateCenter center, int lengthX){
    for(int x = 0; x < lengthX - center.x;  x++){
        double xScaled = scaleX * x;
        double y = scaleY * (coeffs[0] * xScaled * xScaled + coeffs[1] * xScaled + coeffs[2]);   
        txSetPixel(x + center.x, center.y - (int) y, TX_WHITE); 
    }   
    for(int x = 0; x < center.x; x++){
        double xScaled = - scaleX * x;
        double y = scaleY * (coeffs[0] * xScaled * xScaled + coeffs[1] * xScaled + coeffs[2]);
        txSetPixel(center.x - x, center.y - (int) y, TX_WHITE);
    }
}

void drawZoomButtons(Rect buttons[], int lengthX, int lengthY){
    Rect rectZoomInX =  buttons[rectangleZoomInX];
    Rect rectZoomOutX = buttons[rectangleZoomOutX];
    Rect rectZoomInY =  buttons[rectangleZoomInY];
    Rect rectZoomOutY = buttons[rectangleZoomOutY];

    txDrawText( rectZoomInX.x0,  rectZoomInX.y0 - 0.05 * lengthY,
                rectZoomInX.x1,  rectZoomInX.y1 - 0.03 * lengthY, "X");
    txSetFillColor(TX_GREEN);
    txRectangle( rectZoomInX.x0,  rectZoomInX.y0,  rectZoomInX.x1,  rectZoomInX.y1);
    txSetFillColor(TX_RED);
    txRectangle(rectZoomOutX.x0, rectZoomOutX.y0, rectZoomOutX.x1, rectZoomOutX.y1);
    
    txDrawText( rectZoomInY.x0,  rectZoomInY.y0 - 0.05 * lengthY,
                rectZoomInY.x1,  rectZoomInY.y1 - 0.03 * lengthY, "Y");
    txSetFillColor(TX_GREEN);
    txRectangle( rectZoomInY.x0,  rectZoomInY.y0,  rectZoomInY.x1,  rectZoomInY.y1);
    txSetFillColor(TX_RED);
    txRectangle(rectZoomOutY.x0, rectZoomOutY.y0, rectZoomOutY.x1, rectZoomOutY.y1);
}

bool mouseInRectangle(Rect rectangle){
    double x = txMouseX();
    double y = txMouseY();
    return(((x > rectangle.x0) && (x < rectangle.x1)) && ((y > rectangle.y0) && (y < rectangle.y1)));
}

void shiftGraphic(DirectionOfShift direction, CoordinateCenter* center){
    int shiftParameterX = 40;
    int shiftParameterY = 30;

    switch (direction)
    {
    case UP:
        center->y += shiftParameterY;
        break;
    case DOWN:
        center->y -= shiftParameterY;
        break;
    case RIGHT:
        center->x -= shiftParameterX;
        break;
    case LEFT:
        center->x += shiftParameterX;
        break;
    case DEFAULT:
    default:
        break;
    }
}

Button zoomButtonPressCheck(Rect buttons[], int* mouseState){
    if(*mouseState == 1){
        return NOTPRESSED;
    }
    else {
        if(txMouseButtons() == 1){
        if(mouseInRectangle(buttons[rectangleZoomInX])){
            return rectangleZoomInX;
        }
        if(mouseInRectangle(buttons[rectangleZoomOutX])){
            return rectangleZoomOutX;
        }
        if(mouseInRectangle(buttons[rectangleZoomInY])){
            return rectangleZoomInY;
        }
        if(mouseInRectangle(buttons[rectangleZoomOutY])){
            return rectangleZoomOutY;
        }
    }
    *mouseState = 1; 
    }
    return NOTPRESSED;
}

bool shiftButtonPressCheck(DirectionOfShift* direction){
    if(txGetAsyncKeyState(VK_UP)){
        *direction = UP;
        return true;
    }
    else if(txGetAsyncKeyState(VK_DOWN)){
        *direction = DOWN;
        return true;
    }
    else if(txGetAsyncKeyState(VK_RIGHT)){
        *direction = RIGHT;
        return true;
    }
    else if(txGetAsyncKeyState(VK_LEFT)){
        *direction = LEFT;
        return true;
    }
    return false;
}

void moveGraphByMouse(CoordinateCenter* center){
    double a = txMouseX();
    double b = txMouseY();
    txSleep();
    center->x = center->x + (int) (1.5 * (txMouseX() - a));
    center->y = center->y + (int) (1.5 * (txMouseY() - b));
}

void printTitleForGraphicMode(){
    printf("You have enabled graphics mode\n");
    printf("Enter the coefficients:\n");
}

void drawCorrectAnswers(CoordinateCenter center, double scaleX, double sol1, double sol2,
                        char str1sol[], char str2sol[], int lengthX, int lengthY){
    double reverseCompression = 1 / scaleX;
    txDrawText(reverseCompression * sol1 + center.x - 0.05 * lengthX, center.y + 0.004 * lengthY,
               reverseCompression * sol1 + center.x + 0.05 * lengthX, center.y + 0.028 * lengthY, str1sol);
    txDrawText(reverseCompression * sol2 + center.x - 0.05 * lengthX, center.y + 0.004 * lengthY,
               reverseCompression * sol2 + center.x + 0.05 * lengthX, center.y + 0.028 * lengthY, str2sol); 
}

bool enterCoeffs(Equation* equation){
        double coeffs[] = {equation->coeff1, equation->coeff2, equation->coeff3};
        enum CountSol Enter = setCoeffs(coeffs);
        if(Enter != INCORRECT_ENTER){
            equation->coeff1 = coeffs[0];
            equation->coeff2 = coeffs[1];
            equation->coeff3 = coeffs[2];
            return true;
        }
        else{
            clearTheBuffer();
            return false;
        }
}

void drawAxisMarkings(CoordinateCenter center, int lengthX, int lengthY, double scaleX, double scaleY){
    double lengthOfUnitSegmentX = 1 / scaleX;
    double lengthOfUnitSegmentY = scaleY;
    for(int x = center.x; x < lengthX; x += (int)lengthOfUnitSegmentX){
        txLine(x, center.y - 0.005 * lengthY, x, center.y + 0.005 * lengthY);
    }
    for(int x = center.x; x > 0; x -= (int)lengthOfUnitSegmentX){
        txLine(x, center.y - 0.005 * lengthY, x, center.y + 0.005 * lengthY);
    }
    for(int y = center.y; y > 0; y -= (int)lengthOfUnitSegmentY){
        txLine(center.x - 0.005 * lengthX, y, center.x + 0.005 * lengthX, y);
    }
    for(int y = center.y; y < lengthY; y += (int)lengthOfUnitSegmentY){
        txLine(center.x - 0.005 * lengthX, y, center.x + 0.005 * lengthX, y);
    }
}

bool handleButtonPress(Button button, double* scaleX, double* scaleY){
    switch (button)
    {
    case NOTPRESSED:
        return false;
    case rectangleZoomInX:
        *scaleX /= 2;
        return true;
    case rectangleZoomOutX:
        *scaleX *= 2;
        return true;
    case rectangleZoomInY:
        *scaleY *= 2;
        return true;
    case rectangleZoomOutY:
        *scaleY /= 2;
        return true;   
    default:
        return false;
    }
}





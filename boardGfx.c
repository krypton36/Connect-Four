/*
* boardGfx.c
*/

#include "boardGfx.h"

mouseStruct mousePos = {0,0};


BUTTON resetButtonInt = {25,748,100,40, 0, "Reset", resetBoard};
BUTTON computerButton = {150,748,125,40, 0, "Computer", initiateComputer};
/* respondToWin(): Displays who won after someone won.
 *
 *
 * Revision History:
 * 6/22/2015 (JV): Initial version
 */

void respondToWin(){
    rgbStruct rgbColor;
    if(winner == 2){
        getColorRgb(COLOR_WHITE,&rgbColor);
        glColor3f(rgbColor.r, rgbColor.g, rgbColor.b);
        Font(GLUT_BITMAP_TIMES_ROMAN_24,"BLACK WINS!",400,30);
    }
    if(winner == 1){
        getColorRgb(COLOR_WHITE,&rgbColor);
        glColor3f(rgbColor.r, rgbColor.g, rgbColor.b);
        Font(GLUT_BITMAP_TIMES_ROMAN_24,"RED WINS!",400,30);
    }

}

/* clickedOnButton: checks to weather the click in in range
 * of button.
 *
 * Revision History:
 * 6/16/2015 (JV): Initial Version.
 *
 */
int clickedOnButton(BUTTON *button, int x, int y){
    if(button)
    {
        if( x > button->x && x < button->x+button->w){
            if(y > button->y && y < button->y+button->h) {
                return 1;
            }
        }
    }
    return 0;
}
/* pressedButton: checks to weather the button is pressed down.
 *
 * Revision History:
 * 6/16/2015 (JV): Initial Version.
 *
 */
void pressedButton(BUTTON *button, int x, int y ){
    if (button) {
        if (clickedOnButton(button,x,y)) {
            button->state = 1;
        }
    }
}
/* releaseButton: checks to weather the button has been
 * released.
 *
 * Revision History:
 * 6/16/2015 (JV): Initial Version.
 *
 */
void releasedButton(BUTTON *button, int x, int y ){
    if (button) {
        if (clickedOnButton(button,mousePos.xCordPress, mousePos.yCordPress) && clickedOnButton(button,x,y)) {
            if (button->callBackFunction) {
                button->state = 0;
                player = 1;
                totalMoves = 0;
                button->callBackFunction();
            }
        }
    }
}

/*
* yellowBoard:
*
* Revision History:
* 6/11/2015 (JV): Initial Version
* 6/12/2015 (JB): moved the body into the drawRectangle function in gfxLib.c
*/
void yellowBoard(){
    drawRectangle(BOARD_VERTEX1_X,BOARD_VERTEX1_Y,BOARD_VERTEX2_X,BOARD_VERTEX2_Y,COLOR_YELLOW);
    drawRectangleLine(BOARD_VERTEX1_X,BOARD_VERTEX1_Y,BOARD_VERTEX2_X,BOARD_VERTEX2_Y,COLOR_BLACK);
}


/*
* placeCircle:
* This will take the cordinated of the board. (0,0) being
* the Bottom most, left most position and (6,5) being the
* top most, right most position.
*
* Revision History:
* 6/11/2015 (JV): Initial Version
* 6/12/2015 (JB): removed magic numbers
*/
void placeCircle(int x, int y, colorEnum curColor){
    int xPosInt, yPosInt;
    rgbStruct rgbColor;
    if (x >= NUM_COLS || x < 0 ||  y >= NUM_COLS || y < 0) {
        fprintf(stderr,"Invalid position of chip (%d,%d)\n",x,y);
        exit(-1);
    }
    
    xPosInt =  X_START + x*X_SPACE;
    yPosInt = Y_START - y*Y_SPACE;
    
    drawCircle(xPosInt,yPosInt,40,curColor);
    if (player == 2 && !winner) {
        getColorRgb(COLOR_WHITE,&rgbColor);
        glColor3f(rgbColor.r, rgbColor.g, rgbColor.b);
        Font(GLUT_BITMAP_TIMES_ROMAN_24,"Red's Turn",400,30);
    }
    if (player == 1 && !winner) {
        getColorRgb(COLOR_WHITE,&rgbColor);
        glColor3f(rgbColor.r, rgbColor.g, rgbColor.b);
        Font(GLUT_BITMAP_TIMES_ROMAN_24,"Black's Turn",400,30);
    }
    
    drawRing(xPosInt,yPosInt,CIRCLE_RADIUS,COLOR_BLACK);
}

/*
 * mouseButton: determines the location and when button was clicked o
 * the mouse
 *
 * Revision History:
 * 6/13/2015 (JV): Initial version
 */
void mouseButton(int button,int state,int x, int y){
    if (state == GLUT_DOWN)
    {
        if (button == GLUT_LEFT_BUTTON) {
            pressedButton(&resetButtonInt,x,y);
            pressedButton(&computerButton,x,y);
            mousePos.xCordPress = x;
            mousePos.yCordPress = y;
            //printf("button pressed at (%d,%d)\n",x,y);
            
        }
    }
    else
    {
        if (button == GLUT_LEFT_BUTTON) {
            releasedButton(&resetButtonInt,x,y);
            releasedButton(&computerButton,x,y);
            mouseResponder(x, y, winner);
            mousePos.xCordPress = 0;
            mousePos.yCordPress = 0;
            
            //printf("button released at (%d,%d)\n",x,y);
        }
        
    }
    glutPostRedisplay();
}

/*
* drawCircles:
* draws all circles based on current board state.
*
* Revision History:
* 6/13/2015 (JB): Initial Version
*/
void drawCircles(){
    int x,y;
    colorEnum curColor;
    chipColorEnum chipColor;
    for(y=NUM_ROWS-1;y>=0;y--){
        for(x=0;x<NUM_COLS;x++){
            chipColor = getChipAt(&boardState,x,y);
            switch(chipColor){
                case RED_CHIP:
                    curColor = COLOR_RED;
                    break;
                case BLACK_CHIP:
                    curColor = COLOR_BLACK;
                    break;
                case BLANK_CHIP:
                    curColor = COLOR_WHITE;
                    break;
            }
            placeCircle(x,y,curColor);
        }
    }
}

/*
* display:
*
* Revision History:
* 6/11/2015 (JV): Initial version
* 6/12/2015 (JV): added an example to add chips.
*/
void display(void){
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0,WINDOW_WIDTH,WINDOW_HEIGHT,0,-1,1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    yellowBoard();
    //Adds all the circles to the board.
    drawCircles();
    drawButton(&resetButtonInt, COLOR_WHITE);
    drawButton(&computerButton, COLOR_WHITE);
    
    respondToWin();
    glutSwapBuffers();
}

/*
* startGfx:
*
* Revision History:
* 6/13/2015 (JB): Inital Version - moved from connectFour.c
*/
void startGfx(void){
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); 
    glutInitWindowSize (WINDOW_WIDTH, WINDOW_HEIGHT); 
    glutInitWindowPosition (100, 25); 
    glutCreateWindow ("Connect Four");
    //Changes the window background to blue.
    glClearColor(BLUE_R,BLUE_G,BLUE_B,WINDOW_ALPHA);
    //Keeps the Display open and running.
    glutDisplayFunc(display);
    glutMouseFunc(mouseButton);
    glutMainLoop();
    destroyBoard();
}
/*
 * computerPlayer:If the user decided to play agains a
 * computer returns 1.
 *
 * Revision Hisotry:
 * 6/13/2015 (JB): Initial Version
 */
int computerPlayer(){
    return 1;
}


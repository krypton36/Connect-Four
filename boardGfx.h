/*
* boardGfx.h
*/

#ifndef BOARD_GFX_H
#define BOARD_GFX_H

#include "computer.h"


#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT 800
#define WINDOW_ALPHA 1.0 // a value of 0 is transparent and 1.0 is solid
#define X_START 104
#define Y_START 685
#define X_SPACE 130
#define Y_SPACE 113
#define CIRCLE_RADIUS 40.0
// vertex locations for the yellow board
#define BOARD_VERTEX1_X 45
#define BOARD_VERTEX1_Y 55
#define BOARD_VERTEX2_X 945
#define BOARD_VERTEX2_Y 735





//extern cfBoardStruct boardState;


void yellowBoard();
void placeCircle(int x, int y, colorEnum curColor);
void mouseButton(int button,int state,int x, int y);
void drawCircles();



#endif

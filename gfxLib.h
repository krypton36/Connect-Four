/*
* gfxLib.h
*/

#ifndef GFX_LIB_H
#define GFX_LIB_H

#include <math.h>
#include <GLUT/glut.h>


/*
* list fo rgb colors
*
* Revision History:
* 6/12/2015 (JB): Initial Version - added red,black,yellow,white,blue
*/
#define RED_R 0.74
#define RED_G 0.12
#define RED_B 0.12
#define BLACK_R 0.0
#define BLACK_G 0.0
#define BLACK_B 0.0
#define YELLOW_R 1.0
#define YELLOW_G 0.95
#define YELLOW_B 0.3
#define WHITE_R 1.0
#define WHITE_G 1.0
#define WHITE_B 1.0
#define BLUE_R 0.02
#define BLUE_G 0.11
#define BLUE_B 0.9

#define CIRCLE_TRIANGLE_AMOUNT 1000 //How defined the circle is using triangles to draw.
typedef enum
{
COLOR_WHITE=0,
COLOR_RED,
COLOR_BLUE,
COLOR_BLACK,
COLOR_YELLOW
} colorEnum;

typedef struct
{
float r;
float g;
float b;
} rgbStruct;


typedef void (*ButtonFunction)();

typedef struct buttonStruct{
    float   x;							/* top left x coord of the button */
    float   y;							/* top left y coord of the button */
    float   w;							/* the width of the button */
    float   h;							/* the height of the button */
    int	  state;						/* the state, 1 if pressed, 0 otherwise */
    char *label;
    ButtonFunction callBackFunction;
}BUTTON;


void drawButton(BUTTON *button, colorEnum curColor);
void drawRing(float positionX, float positionY, float radius, colorEnum curColor);
void drawCircle(float positionX, float positionY, float radius, colorEnum curColor);
void drawRectangleLine(int v1x, int v1y, int v2x, int v2y, colorEnum curColor);
void drawRectangle(int v1x, int v1y, int v2x, int v2y, colorEnum curColor);
void getColorRgb(colorEnum curColor, rgbStruct *rgbVal) ;
void Font(void *font,char *text,float x,float y);




#endif

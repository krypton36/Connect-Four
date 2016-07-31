/*
* gfxLib.c
*/

#include "gfxLib.h"

/*
 * drawRing:
 * draws a circle of based on color, position(x,y), and radius.
 *
 * Revision History:
 * 6/13/2015 (JV): Initial Version - Coppied from draw circle.
 */
void drawRing(float positionX, float positionY, float radius, colorEnum curColor){
    int i;
    int triangleAmount = CIRCLE_TRIANGLE_AMOUNT;
    rgbStruct rgbColor;
    getColorRgb(curColor,&rgbColor);
    
    GLfloat twoPi = 2.0f * M_PI;
    glColor3f(rgbColor.r, rgbColor.g, rgbColor.b);
    glLineWidth(2);
    glBegin(GL_LINE_LOOP);
    for(i = 0; i <= triangleAmount;i++) {
        glVertex2i(positionX + (radius * cos(i *  twoPi / triangleAmount)),
                   positionY + (radius * sin(i * twoPi / triangleAmount))
                   );
    }
    glEnd();
}

/*
* drawCircle:
* draws a solid circle of based on color, position(x,y), and radius.
*
* Revision History:
* 6/11/2015 (JV): Initial Version
* 6/12/2015 (JB): changed to use rgbStruct
*/
void drawCircle(float positionX, float positionY, float radius, colorEnum curColor){
    int i;
    int triangleAmount = CIRCLE_TRIANGLE_AMOUNT;
    rgbStruct rgbColor;
    getColorRgb(curColor,&rgbColor);
    
    GLfloat twoPi = 2.0f * M_PI;
    glColor3f(rgbColor.r, rgbColor.g, rgbColor.b);
    
    glBegin(GL_TRIANGLE_FAN);
    for(i = 0; i <= triangleAmount;i++) {
        glVertex2i(positionX + (radius * cos(i *  twoPi / triangleAmount)),
                   positionY + (radius * sin(i * twoPi / triangleAmount))
                   );
    }
    glEnd();
}

/*
* drawRectangle:
* draws a rectangle that covers the two specified vertices and fills with the given color.
*
* Revision History:
* 6/12/2015 (JB): Initial Version - copied from yellowBoard in board.c
*/
void drawRectangle(int v1x, int v1y, int v2x, int v2y, colorEnum curColor){
    rgbStruct rgbColor;
    getColorRgb(curColor,&rgbColor);
    glColor3f(rgbColor.r, rgbColor.g, rgbColor.b);
    glBegin(GL_QUADS);
    glVertex2i(v1x, v1y);
    glVertex2i(v1x, v2y);
    glVertex2i(v2x, v2y);
    glVertex2i(v2x, v1y);
    glEnd();
}
/*
 * drawRectangleLine:
 * draws a rectangle perimeter in the specified color and vertices.
 *
 * Revision History:
 * 6/13/2015 (JV): Initial Version - copied from drawRectangle.
 */
void drawRectangleLine(int v1x, int v1y, int v2x, int v2y, colorEnum curColor){
    rgbStruct rgbColor;
    getColorRgb(curColor,&rgbColor);
    glColor3f(rgbColor.r, rgbColor.g, rgbColor.b);
    glLineWidth(5);
    glBegin(GL_LINE_LOOP);
    glVertex2i(v1x, v1y);
    glVertex2i(v1x, v2y);
    glVertex2i(v2x, v2y);
    glVertex2i(v2x, v1y);
    glEnd();
}
/*
* getColorRgb:
* takes in a color from colorEnum and returns the associated rgb.
*
* Revision History:
* 6/12/2015 (JB): Initial version
*/
void getColorRgb(colorEnum curColor, rgbStruct *rgbVal) {
    switch(curColor) {
        case COLOR_RED:
            rgbVal->r = RED_R;
            rgbVal->g = RED_G;
            rgbVal->b = RED_B;
            break;
        case COLOR_BLACK:
            rgbVal->r = BLACK_R;
            rgbVal->g = BLACK_G;
            rgbVal->b = BLACK_B;
            break;
        case COLOR_YELLOW:
            rgbVal->r = YELLOW_R;
            rgbVal->g = YELLOW_G;
            rgbVal->b = YELLOW_B;
            break;
        case COLOR_WHITE:
            rgbVal->r = WHITE_R;
            rgbVal->g = WHITE_G;
            rgbVal->b = WHITE_B;
            break;
        case COLOR_BLUE:
            rgbVal->r = BLUE_R;
            rgbVal->g = BLUE_G;
            rgbVal->b = BLUE_B;
            break;
    }
}
void Font(void *font,char *text,float x,float y){
    glRasterPos2i(x,y);
    while( *text != '\0' )
    {
        glutBitmapCharacter( font, *text );
        ++text;
    }
}
/*
 * drawButton: draws the button from
 * the struct that is created.
 *
 * Revision History: 
 * 06/16/15 (JV): Initial Version.
 *
 */

void drawButton(BUTTON *button, colorEnum curColor){
    float fontx;
    float fonty;
    
    rgbStruct rgbColor;
    getColorRgb(curColor, &rgbColor);
    

    if (button) {
        glColor3f(rgbColor.r, rgbColor.g, rgbColor.b);
        glBegin(GL_QUADS);
        glVertex2i( button->x, button->y);
        glVertex2i( button->x, button->y+button->h);
        glVertex2i( button->x+button->w, button->y+button->h);
        glVertex2i( button->x+button->w, button->y);
        glEnd();
        
        glLineWidth(3);
        
        if (button->state)
            glColor3f(rgbColor.r, rgbColor.g, rgbColor.b);
        else
            glColor3f(0.75,0.75,0.75);
        
        glBegin(GL_LINE_STRIP);
        glVertex2i( button->x+button->w, button->y);
        glVertex2i( button->x, button->y);
        glVertex2i( button->x, button->y+button->h);
        glEnd();

        if (button->state)
            glColor3f(0.8f,0.8f,0.8f);
        else
            glColor3f(0.4f,0.4f,0.4f);
        
        glBegin(GL_LINE_STRIP);
        glVertex2i( button->x, button->y+button->h);
        glVertex2i( button->x+button->w, button->y+button->h);
        glVertex2i( button->x+button->w, button->y);
        glEnd();
        
        glLineWidth(1);
        fontx = button->x + (button->w - glutBitmapLength(GLUT_BITMAP_TIMES_ROMAN_24,(const unsigned char *)button->label)) / 2 ;
        fonty = button->y + (button->h+10)/2;
        glColor3f(0,0,0);
        Font(GLUT_BITMAP_TIMES_ROMAN_24,button->label,fontx,fonty);
        
    }
}

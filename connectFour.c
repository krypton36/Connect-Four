/*
* ConnectFour.c
*/

#include "connectFour.h"


/*
* main:
*
* Revision History:
* 6/11/2015 (JV): Initial version
* 6/12/2015 (JB): moved the body to startGfx
*/
int main(int argc, char** argv){
    cfBoardStruct cfBoard;
    glutInit(&argc, argv);
    createBoard(&cfBoard);
    //printBitPackedBoard(&cfBoard);
    boardState = cfBoard;
    
    startGfx();
    return 0;
}

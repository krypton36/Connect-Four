

#ifndef COMPUTER_H
#define COMPUTER_H
#include "win.h"
#include "gfxLib.h"


#define NUM_ROWS 6
#define NUM_COLS 7
#define NUM_BITS_PER_CHIP 2 // this is how many bits are needed per piece when bitpacking the board
//Starting Values of each chip.
#define VALUE_BLANK_CHIP 0x00
#define VALUE_RED_CHIP 0x01
#define VALUE_BLACK_CHIP 0x02

#define PLAYER_ONE 1
#define PLAYER_TWO 2

/* Lower bouds and upper bounds to each
 column
 */
#define COL1_LOW 46
#define COL1_HIGH 170
#define COL2_LOW 171
#define COL2_HIGH 300
#define COL3_LOW 301
#define COL3_HIGH 432
#define COL4_LOW 433
#define COL4_HIGH 569
#define COL5_LOW 570
#define COL5_HIGH 702
#define COL6_LOW 703
#define COL6_HIGH 835
#define COL7_LOW 836
#define COL7_HIGH 976

typedef enum{
    BLANK_CHIP=0,
    RED_CHIP,
    BLACK_CHIP
}chipColorEnum;

typedef struct{
    /*
     * the bits are packed as follows:
     * the bottom row from left to right
     * then the next row up from left to right etc.
     */
    char *bitPackedBoard;
}cfBoardStruct;
typedef struct{
    int xCordPress;
    int yCordPress;
}mouseStruct;

extern mouseStruct mousePos;
extern unsigned int numCharsPerBoard;
extern int winner;
extern unsigned char player;
extern cfBoardStruct boardState;
extern unsigned char totalMoves;
extern int disableMouse;

void createBoard(cfBoardStruct *newBoard);
void destroyBoard();
void resetBoard();
chipColorEnum getChipAt(cfBoardStruct *, int x, int y);
void setChipAt(cfBoardStruct *cfBoard, int x, int y, chipColorEnum chipColor);
unsigned char mapChipColorToBits(chipColorEnum chipColor);
chipColorEnum mapBitsToChipColor(unsigned char chipBitPattern);
void getBitPosInBoard(int x, int y, int *charNum, int *bitNumRelativeToCharNum);
void printBitPackedBoard(cfBoardStruct *cfBoard);
int isValidChipPos(int x, int y);
void addChipAt(cfBoardStruct *cfBoard, int column, chipColorEnum chipColor);
void startGfx(void);
cfBoardStruct *getCurrentBoard();
void disableMouseFunction(int disable);
void mouseResponder(int x, int y, int pause);
unsigned char alterTurn();

//Computer Functions
void initiateComputer();
void playMoveComputer();
extern int computerOn;

#endif
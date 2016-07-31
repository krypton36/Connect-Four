/*
* board.c
* 
* [0,5] [1,5] [2,5] [3,5] [4,5] [5,5] [6,5]
* [0,4] [1,4] [2,4] [3,4] [4,4] [5,4] [6,4]
* [0,3] [1,3] [2,3] [3,3] [4,3] [5,3] [6,3]
* [0,2] [1,2] [2,2] [3,2] [4,2] [5,2] [6,2]
* [0,1] [1,1] [2,1] [3,1] [4,1] [5,1] [6,1]
* [0,0] [1,0] [2,0] [3,0] [4,0] [5,0] [6,0]
*/

#include "computer.h"
int winner = 0;
unsigned char player = 1;
unsigned char totalMoves = 0;
unsigned int numCharsPerBoard = 0; // this is initialized in createBoard function
int debugLevel = 1;
int disableMouse = 0;
cfBoardStruct *curBoard;
cfBoardStruct boardState;
/*
* createBoard:
* make a new board type
*
* Revision History:
* 6/13/2105 (JB): Initial Version
*/
void createBoard(cfBoardStruct *newBoard){
    if (numCharsPerBoard == 0) { // only redfine it once
        //printf("NUM_ROWS*NUM_COLS*NUM_BITS_PER_CHIP=%d\n",NUM_ROWS*NUM_COLS*NUM_BITS_PER_CHIP);
        //printf("sizeof(char)=%lu\n",(sizeof(char)*8));
        numCharsPerBoard = ceil(NUM_ROWS*NUM_COLS*NUM_BITS_PER_CHIP / (double)(sizeof(char)*8));
        //printf("numCharsPerBoard=%d\n",numCharsPerBoard);
    }
    newBoard->bitPackedBoard = (char *)calloc(numCharsPerBoard,sizeof(char));
    curBoard = newBoard;
    initializeHorizontal();
    initializeVertical();
    intitializeDiagonal();
}

/*
* destroyBoard:
* cleans up anything realted to the cfBoard type.
*
* Revision History:
* 6/13/2015 (JB): Initial Version
*/
void destroyBoard(){
    free(curBoard->bitPackedBoard);
    freeWinAllocations();
}

/*
* resetBoard:
* set the board back to blanks
*
* Revision History:
* 6/13/2015 (JB): Initial Version
*/
void resetBoard(){
    int i;
    for(i=0;i<numCharsPerBoard;i++){
        curBoard->bitPackedBoard[i] = 0;
    }
    resetWin();
    winner = 0;
    disableMouse = 0;
}

/*
* getChipAt:
* returns the color of the chip at the specified location
* 
* Revision History:
* 6/13/2015 (JB): Initial Version
*/
chipColorEnum getChipAt(cfBoardStruct *cfBoard, int x, int y){
    int charNum, bitNumRelativeToCharNum;
    unsigned char bitPattern;
    chipColorEnum chipColor;
    if(!isValidChipPos(x,y)){
        fprintf(stderr,"Invalid position of chip (%d,%d)\n",x,y);
        return BLANK_CHIP;
    }
    getBitPosInBoard(x,y,&charNum,&bitNumRelativeToCharNum);
    bitPattern = 0x03&(cfBoard->bitPackedBoard[charNum] >> (bitNumRelativeToCharNum-2));
    chipColor = mapBitsToChipColor(bitPattern);
    if(debugLevel >= 5){
        printf("(%d,%d):color(%d):charNum%d:(-0)=%d,(-2)=%d,(-4)=%d\n",x,y,chipColor,charNum,0x03&(cfBoard->bitPackedBoard[charNum] >> bitNumRelativeToCharNum),0x03&(cfBoard->bitPackedBoard[charNum] >> (bitNumRelativeToCharNum-2)),0x03&(cfBoard->bitPackedBoard[charNum] >> (bitNumRelativeToCharNum-4)));
    }
    return chipColor;
}

/*
* setChipAt:
* sets the chip at the specified location to the specifed color
* x is the column and y is the row.
* 
* Revision History:
* 6/13/2015 (JB): Initial Version
*/
void setChipAt(cfBoardStruct *cfBoard, int x, int y, chipColorEnum chipColor){
    unsigned char curChip = mapChipColorToBits(chipColor);
    int charNum, bitNumRelativeToCharNum;
    
    if(!isValidChipPos(x,y)){
        fprintf(stderr,"Invalid position of chip (%d,%d)\n",x,y);
        return;
    }
    getBitPosInBoard(x,y,&charNum,&bitNumRelativeToCharNum);
    cfBoard->bitPackedBoard[charNum] |= curChip << (bitNumRelativeToCharNum-2);
    
    winner = checkWin(x, y, curChip);
    disableMouse = winner;
}

/*
* isValidChipPos:
*
* Revision History:
* 6/13/2015 (JB): Initial Version
*/
int isValidChipPos(int x, int y){
    int returnVal = 1;
    if (x < 0){
        returnVal = 0;
    }
    if (x >= NUM_COLS){
        returnVal = 0;
    }
    if (y < 0){
        returnVal = 0;
    }
    if (y >= NUM_ROWS){
        returnVal = 0;
    }
    return returnVal;
}


/*
* mapChipColorToBits:
* returns the correct bit patter for the specified chip
*
* Revision History:
* 6/13/2015 (JB): Initial Version
*/
unsigned char mapChipColorToBits(chipColorEnum chipColor){
    unsigned char returnVal = 0;
    switch(chipColor){
        case RED_CHIP:
            returnVal = VALUE_RED_CHIP;
            break;
        case BLACK_CHIP:
            returnVal = VALUE_BLACK_CHIP;
            break;
        default:
            returnVal = VALUE_BLANK_CHIP;
            break;
    }
    return returnVal;
}

/*
* mapBitsToChipColor:
* returns the correct color for specified bit pattern
*
* Revision History:
* 6/13/2015 (JB): Initial Version
*/
chipColorEnum mapBitsToChipColor(unsigned char chipBitPattern){
    unsigned char returnVal = BLANK_CHIP;
    switch(chipBitPattern){
        case VALUE_RED_CHIP:
            returnVal = RED_CHIP;
            break;
        case VALUE_BLACK_CHIP:
            returnVal = BLACK_CHIP;
            break;
        default:
            returnVal = BLANK_CHIP;
            break;
    }
    return returnVal;
}
/*
* getBitPosInBoard:
* maps the x,y position to the bit packed board
*
* Revision History:
* 6/13/2015 (JB): Initial Version
*/
void getBitPosInBoard(int x, int y, int *charNum, int *bitNumRelativeToCharNum){
    int rowOffset, colOffset, totalBitNum;
    colOffset = x * NUM_BITS_PER_CHIP;
    rowOffset = y * NUM_BITS_PER_CHIP * NUM_COLS;
    totalBitNum = colOffset + rowOffset;
    *charNum = (totalBitNum) / (sizeof(char)*8); // integer division
    *bitNumRelativeToCharNum = sizeof(char)*8-(totalBitNum % (sizeof(char)*8));
    //printf("(%d,%d):totalBits=%d:char%d,bit%d\n",x,y,totalBitNum,*charNum,*bitNumRelativeToCharNum);
}

/*
* printBitPakcedBoard:
* utility function to look at how the bitpacked board works
*
* Revision History:
* 6/13/2015 (JB): Initial Version
*/
void printBitPackedBoard(cfBoardStruct *cfBoard){
    int i,x,y,rowNum,colNum;
    unsigned char curChar;
    chipColorEnum chipColor;
    if(debugLevel >= 2){
        printf("Printing Raw Chars (%d):\n",numCharsPerBoard);
        for(i=0;i<numCharsPerBoard;i++){
            printf("char%02d:0x%02x: ",i+1,0x000000FF&cfBoard->bitPackedBoard[i]);
            curChar = cfBoard->bitPackedBoard[i];
            printf("%d%d ",(0x80&curChar) >> 7,(0x40&curChar) >> 6);
            printf("%d%d ",(0x20&curChar) >> 5,(0x10&curChar) >> 4);
            printf("%d%d ",(0x08&curChar) >> 3,(0x04&curChar) >> 2);
            printf("%d%d ",(0x02&curChar) >> 1,0x01&curChar);
            printf("\n");
        }
        printf("Printing GameBoard of size(%d,%d):\n",NUM_COLS,NUM_ROWS);
        rowNum = 0;
        colNum = 1;
        printf("  0  1  2  3  4  5  6\n");
        printf("%d ",rowNum);
        for(i=0;i<numCharsPerBoard;i++){
            curChar = cfBoard->bitPackedBoard[i];
            if(colNum > NUM_COLS){
                colNum = 1;
                printf("\n%d ",++rowNum);
            }
            printf("%d%d ",(0x80&curChar) >> 7,(0x40&curChar) >> 6);
            colNum++;
            if(colNum > NUM_COLS){
                colNum = 1;
                printf("\n%d ",++rowNum);
            }
            printf("%d%d ",(0x20&curChar) >> 5,(0x10&curChar) >> 4);
            colNum++;
            if(colNum > NUM_COLS){
                colNum = 1;
                printf("\n%d ",++rowNum);
            }
            printf("%d%d ",(0x08&curChar) >> 3,(0x04&curChar) >> 2);
            colNum++;
            if(colNum > NUM_COLS){
                colNum = 1;
                printf("\n%d ",++rowNum);
            }
            printf("%d%d ",(0x02&curChar) >> 1,0x01&curChar);
            colNum++;
        }
        printf("\n");   
        printf("Printing GameBoard of size(%d,%d):\n",NUM_COLS,NUM_ROWS);
        for(y=NUM_ROWS-1;y>=0;y--){
            //printf("Row%d:",y);
            for(x=0;x<NUM_COLS;x++){
                chipColor = getChipAt(cfBoard,x,y);
                //printf("%0d  ",chipColor);
            }
            printf("\n");
        }
    }
    printf("Printing GameBoard of size(%d,%d):\n",NUM_COLS,NUM_ROWS);
    printf("   0 1 2 3 4 5 6\n");
    printf("   -------------\n");
    for(y=NUM_ROWS-1;y>=0;y--){
        printf("%d |",y);
        for(x=0;x<NUM_COLS;x++){
            chipColor = getChipAt(cfBoard,x,y);
            printf("%d ",chipColor);
        }
        printf("\n");
    }
}

/*
* addChipAt:
* adds the chip to the specified column.
*
* Revision Hisotry:
* 6/13/2015 (JB): Initial Version
*/

void addChipAt(cfBoardStruct *cfBoard, int column, chipColorEnum chipColor){
    int i;
    chipColorEnum tmpChipColor;
    for(i=0;i<NUM_ROWS;i++){
        tmpChipColor = getChipAt(cfBoard,column,i);
        if(tmpChipColor == BLANK_CHIP){
            setChipAt(cfBoard,column,i,chipColor);
            return;
        }
    }
    fprintf(stderr,"Cannot add to column it is full");
}
cfBoardStruct *getCurrentBoard(){
    return curBoard;
}
/* disableAddChip: Disables the ability to add chips
 * after someone has won.
 *
 * Revision History:
 * 6/16/2015 (JV): Initial Version.
 *
 */
void disableMouseFunction(int disable){
    disableMouse = disable;
}
/* alterTurn(): counts total moves and changes player accordingly.
 * returns the player.
 *
 * Revision History:
 * 6/15/2015 (JV): Initial version
 */
unsigned char alterTurn(){
    totalMoves++;
    return (totalMoves%2)+1;
}
/*
 * mouseResponder:
 * y RANGE
 * 63-736
 * left button released at (896,627)
 * X RANGE
 * Column1 = 26 - 170
 * Column2 = 171 - 300
 * Column3 = 301 - 432
 * Column4 = 433 - 569
 * Column5 = 570 - 702
 * Column6 = 703 - 835
 * Column7 = 836 - 976
 *
 *
 * Revision History:
 * 6/13/2015 (JV): Initial version
 * 6/16/2015 (JV): Revised magic numbers and if to switch
 */
void mouseResponder(int x, int y, int pause){
    int columnPosition = -1;
    chipColorEnum playerColor;
    switch(player){
        case PLAYER_ONE:
            playerColor = BLACK_CHIP;
            break;
        case PLAYER_TWO:
            playerColor = RED_CHIP;
            break;
    }
    //The 0-6 are the rows of the board.
    if(mousePos.yCordPress > 63 && mousePos.yCordPress < 736 && disableMouse == 0) {
        switch (mousePos.xCordPress) {
            case COL1_LOW ... COL1_HIGH:
                columnPosition = 0;
                break;
            case COL2_LOW ... COL2_HIGH:
                columnPosition = 1;
                break;
            case COL3_LOW ... COL3_HIGH:
                columnPosition = 2;
                break;
            case COL4_LOW ... COL4_HIGH:
                columnPosition = 3;
                break;
            case COL5_LOW ... COL5_HIGH:
                columnPosition = 4;
                break;
            case COL6_LOW ... COL6_HIGH:
                columnPosition = 5;
                break;
            case COL7_LOW ... COL7_HIGH:
                columnPosition = 6;
                break;
            default:
                break;
        }
        if(columnPosition != -1){
            player = alterTurn();
            addChipAt(&boardState,columnPosition, playerColor);
            if (computerOn) {
                playMoveComputer();
            }
        }
    }
    /*
     Fixes but with clicking then scolling. This would
     cause to pieced to be placed as scrolled.
     */
    mousePos.yCordPress = 0;
    mousePos.xCordPress = 0;
}


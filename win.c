#include "win.h"

unsigned long long blacks ;
unsigned long long reds;
unsigned long long *verticalWins;
unsigned long long *horizontalWins;
unsigned long long *diagonalWins;

/* initializeDiagonal: initializes the possible wins diagonally
 * does this once in the creation of the board. 24 Total.
 *
 * Revision History:
 * 6/22/2015 (JV): Initial Version.
 *
 */
void intitializeDiagonal(){
    int startOfAlorithm = 0;
    unsigned long long storeNextWin = DIAGONAL_FORWARD;
    diagonalWins = (unsigned long long *)calloc(TOTAL_DIAGONAL_WINS,sizeof(unsigned long long));
    diagonalWins[startOfAlorithm] = storeNextWin;
    for (startOfAlorithm = 1; startOfAlorithm < HALF_OF_DIAGANOLS; startOfAlorithm++) {
        if (startOfAlorithm%SHIFT_NEXT_ROW != 0) {
            storeNextWin >>= NEXT_WIN;
            diagonalWins[startOfAlorithm] = storeNextWin;
        }
        else{
            storeNextWin >>= SHIFT_NEXT_ROW;
            diagonalWins[startOfAlorithm] = storeNextWin;
        }
        
    }
    storeNextWin = DIAGONAL_BACKWARDS;
    diagonalWins[HALF_OF_DIAGANOLS] = storeNextWin;
    for (startOfAlorithm = HALF_OF_DIAGANOLS+1; startOfAlorithm < TOTAL_DIAGONAL_WINS; startOfAlorithm++) {
        if (startOfAlorithm%SHIFT_NEXT_ROW != 0) {
            storeNextWin >>= NEXT_WIN;
            diagonalWins[startOfAlorithm] = storeNextWin;
        }
        else{
            storeNextWin >>= SHIFT_NEXT_ROW;
            diagonalWins[startOfAlorithm] = storeNextWin;
        }
        
    }

    
}
/* initializeVertical: initializes the possible wins vertically
 * does this once in the creation of the board. 21 Total.
 *
 * Revision History:
 * 6/22/2015 (JV): Initial Version.
 *
 */
void initializeVertical(){
    int startOfAlorithm = 0;
    unsigned long long storeNextWin = VERTICAL;
    
    verticalWins = (unsigned long long *)calloc(TOTAL_VERTICAL_WINS,sizeof(unsigned long long));
    verticalWins[startOfAlorithm] = storeNextWin;
    for (startOfAlorithm = 1; startOfAlorithm < TOTAL_VERTICAL_WINS; startOfAlorithm++){
        storeNextWin >>= NEXT_WIN;
        verticalWins[startOfAlorithm] = storeNextWin;
    }
}
/* initializeHorizontal: initializes the possible wins horizontally
 * does this once in the creation of the board. 24 total.
 *
 * Revision History:
 * 6/22/2015 (JV): Initial Version.
 *
 */
void initializeHorizontal(){
    int startOfAlorithm = 0;
    unsigned long long storeNextWin = HORIZONTAL;
    
    horizontalWins = (unsigned long long *)calloc(TOTAL_HORIZONTAL_WINS,sizeof(unsigned long long));
    horizontalWins[startOfAlorithm] = storeNextWin;
    
    for (startOfAlorithm = 1; startOfAlorithm < TOTAL_HORIZONTAL_WINS; startOfAlorithm++){
        if(startOfAlorithm%SHIFT_NEXT_ROW != 0){
            storeNextWin >>= NEXT_WIN;
            horizontalWins[startOfAlorithm] = storeNextWin;
        }
        else{
            storeNextWin >>= SHIFT_NEXT_ROW;
            horizontalWins[startOfAlorithm] = storeNextWin;
        }
    }
    
}
/* checkWin: checks to see if there is a win when placing a chip.
 *
 *
 * Revision History:
 * 6/22/2015 (JV): Initial Version.
 *
 */
int checkWin(int x, int y, char chipColor){
    int i;
    long long winningState;
    int rowCheck = y*4;
    if (chipColor == 1) {
        reds |= FIRST_BIT>>(y*COLUMNS + x);
    }
    if (chipColor == 2) {
        blacks |= FIRST_BIT>>(y*COLUMNS + x);
    }
    //Horizontal Win Check
    for (i = 0; i < 4; i++) {
        winningState = horizontalWins[rowCheck + i];
        if ((winningState&blacks) == winningState) {
            return chipColor;
        }
        if ((winningState&reds) == winningState) {
            return chipColor;
        }
    }
    //Vertical Win Check
    for (i = 0; i < TOTAL_VERTICAL_WINS; i+=7) {
        if ((verticalWins[x + i]&blacks) == verticalWins[x + i]) {
            return chipColor;
        }
        if ((verticalWins[x + i]&reds) == verticalWins[x + i]) {
            return chipColor;
        }
    }
    //Diagnal Win Check
    for (i = 0; i < TOTAL_DIAGONAL_WINS; i++){
        if ((diagonalWins[i]&reds) == diagonalWins[i]){
            return chipColor;
        }
        if ((diagonalWins[i]&blacks) == diagonalWins[i]){
            return chipColor;
        }
    }
    return 0;
}
/* resetWin: resets the black board and red board
 *
 *
 * Revision History:
 * 6/22/2015 (JV): Initial Version.
 *
 */
void resetWin(){
    blacks = 0;
    reds = 0;
}
/* freeWinAllocations: frees all memory used in storing wins.
 *
 *
 * Revision History:
 * 6/22/2015 (JV): Initial Version.
 *
 */
void freeWinAllocations(){
    free(verticalWins);
    free(horizontalWins);
    free(diagonalWins);
}
unsigned long long getBlackChipPositions(){
    return blacks;
}
unsigned long long getRedChipPositions(){
    return reds;
}

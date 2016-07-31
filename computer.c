#include "computer.h"
int computerOn = 0;

void initiateComputer(){
    resetBoard();
    computerOn = 1;
}
void playMoveComputer(){
    while (player == 2) {
        disableMouseFunction(1);
        addChipAt(&boardState, 0, RED_CHIP);
        player = alterTurn();
        disableMouseFunction(0);
        
    }
}
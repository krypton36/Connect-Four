#ifndef WIN_H
#define WIN_H

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define ROWS 6
#define COLUMNS 7
#define FIRST_BIT 0x8000000000000000
#define HORIZONTAL 0xF000000000000000
#define VERTICAL 0x8102040000000000
#define DIAGONAL_FORWARD 0x8080808000000000
#define DIAGONAL_BACKWARDS 0x1041040000000000
#define HALF_OF_DIAGANOLS 12
#define SHIFT_NEXT_ROW 4
#define START_ALGORITHM 1
#define NEXT_WIN 1
#define TOTAL_HORIZONTAL_WINS 24
#define TOTAL_VERTICAL_WINS 21
#define TOTAL_DIAGONAL_WINS 24


void initializeHorizontal();
void initializeVertical();
void intitializeDiagonal();
int checkWin(int x, int y, char chipColor);
void resetWin();
void freeWinAllocations();
unsigned long long getBlackChipPositions();
unsigned long long getRedChipPositions();
#endif


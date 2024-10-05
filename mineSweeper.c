#include "mineSweeper.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "colorPrint.h"
/*
checks if the rows,cols,level are legal and changes to default
*/
bool
isLegal(GameBoard **g, int *rows, int *cols, int *level) { 
    if (*rows > MAX_BOARD_DIM) {
        *rows = MAX_BOARD_DIM;
        (*g)->rows = *rows;
    }
    if (*cols > MAX_BOARD_DIM) {
        *cols = MAX_BOARD_DIM;
        (*g)->cols = *cols;
    }
    if (*rows <= 0) {
        *rows = 4;
        (*g)->rows = *rows;
    }
    if (*cols <= 0) {
        *cols = 4;
        (*g)->cols = *cols;
    }
    return TRUE;
    if (*level != EASY || *level != MEDIUM || *level != HARD) {
        *level = EASY;
    }
}
/*
intialize a board depending on the rows,cols,level.
*/
bool
initBoard(GameBoard *g, int rows, int cols, int level) {
    if (isLegal(&g, &rows, &cols, &level) == FALSE) { // if its illegal it'll set it everything to default.
        g->hiddenTiles = rows * cols;
        g->board = (Tile **) malloc(rows * sizeof(Tile *)); // creates a 2d array using malloc(rows)
        for (int i = 0; i < rows; i++) {
            g->board[i] = (Tile *) malloc(cols * sizeof(Tile));// creates a 2d array using malloc(cols)
        }
    } //else it'll intialize the board normally.
    g->rows = rows;
    g->cols = cols;
    g->hiddenTiles = rows * cols;
    g->board = (Tile **) malloc(rows * sizeof(Tile *));
    for (int i = 0; i < rows; i++) {
        g->board[i] = (Tile *) malloc(cols * sizeof(Tile));
    }
    populateMines(g, level); // to spread the mines on the board
    markNumbers(g); // to mark the number of mines that are close to a specific tile
    return TRUE;
}

/*
creates the mines randomly on the board while keeping in mind its rowsXcols&level
*/
void
populateMines(GameBoard *g, int level) {
    int easylvl, midlvl, hardlvl;
    if(level!=EASY|| level!=MEDIUM|| level!=HARD){ // legal level else turn to default
     level=EASY;
    }
    int rowsXcols = (g->rows) * (g->cols);
    int randomizer_rows = 0;
    int randomizer_cols = 0;
    if (level == EASY) {
        easylvl = ((double) rowsXcols * EASY_LEVEL_PERCENT) / 100; //creates EASY_LEVEL_MINES
        g->totalMines = easylvl;
    }
    if (level == MEDIUM) {
        midlvl = ((double) rowsXcols * MEDIUM_LEVEL_PERCENT) / 100;//creates MEDIUM_LEVEL_MINES
        g->totalMines = midlvl;
    }
    if (level == HARD) {
        hardlvl = ((double) rowsXcols * HARD_LEVEL_PERCENT) / 100; //creates HARD_LEVEL_MINES
        g->totalMines = hardlvl;
    }
    for (int j = 0; j < g->totalMines; j++) { // randomize the mines on the board
        randomizer_rows = rand() % (g->rows); //randomize a row in range
        randomizer_cols = rand() % (g->cols);//randomize a col in range
        if (level == EASY) {
            if (j < easylvl) {
                if (g->board[randomizer_rows][randomizer_cols].isMine == FALSE) {
                    g->board[randomizer_rows][randomizer_cols].isMine = TRUE;
                } else {
                    j--; // if theres already a mine there it'll randmoize and choose another mine
                    // so it wont skip a mine.
                }
            }
        }

        if (level == MEDIUM) {
            if (j < midlvl) {
                if (g->board[randomizer_rows][randomizer_cols].isMine == FALSE) {
                    g->board[randomizer_rows][randomizer_cols].isMine = TRUE;
                } else {
                    j--;// if theres already a mine there it'll randmoize and choose another mine
                    // so it wont skip a mine.
                }
            }
        }
        if (level == HARD) {
            if (j < hardlvl) {
                if (g->board[randomizer_rows][randomizer_cols].isMine == FALSE) {
                    g->board[randomizer_rows][randomizer_cols].isMine = TRUE;
                } else {
                    j--;// if theres already a mine there it'll randmoize and choose another mine
                    // so it wont skip a mine.
                }
            }
        }
    }
}
/*
marks the numbers of mines that are near a specific tile.
*/
void
markNumbers(GameBoard *g) {
    for (int i = 0; i < g->rows; i++) {
        for (int j = 0; j < g->cols; j++) {
            if (i < g->rows && j < g->cols) {
                if (g->board[i][j].isMine == FALSE) {
                    if (i - 1 >= 0 && j - 1 >= 0) {
                        if (g->board[i - 1][j - 1].isMine == TRUE) {
                            g->board[i][j].numOfMines += 1;
                        }
                    }
                    if (j - 1 >= 0) {
                        if (g->board[i][j - 1].isMine == TRUE) {
                            g->board[i][j].numOfMines += 1;
                        }
                    }
                    if (j - 1 >= 0 && i + 1 < g->rows) {
                        if (g->board[i + 1][j - 1].isMine == TRUE) {
                            g->board[i][j].numOfMines += 1;
                        }
                    }
                    if (i - 1 >= 0) {
                        if (g->board[i - 1][j].isMine == TRUE) {
                            g->board[i][j].numOfMines += 1;
                        }
                    }
                    if (i + 1 < g->rows) {
                        if (g->board[i + 1][j].isMine == TRUE) {
                            g->board[i][j].numOfMines += 1;
                        }
                    }
                    if (i - 1 >= 0 && j + 1 < g->cols) {
                        if (g->board[i - 1][j + 1].isMine == TRUE) {
                            g->board[i][j].numOfMines += 1;
                        }
                    }
                    if (j + 1 < g->cols) {
                        if (g->board[i][j + 1].isMine == TRUE) {
                            g->board[i][j].numOfMines += 1;
                        }
                    }
                    if (i + 1 < g->rows && j + 1 < g->cols) {
                        if (g->board[i + 1][j + 1].isMine == TRUE) {
                            g->board[i][j].numOfMines += 1;
                        }
                    }
                }
            }
        }
    }
}
/*
sets the tile as clicked(visible) on the board 
depending on if there are mines near the tile or not(spreads the click)
if it clicked on a mine its gameover
*/
void
clickTile(GameBoard *g, int row, int col) {
    if (row < 0 || col < 0 || row > g->rows || col > g->cols) { // checks if legal
        return;
    } 
     if (g->board[row][col].isVisible == TRUE) { //if already clicked
        return;
    } 
    else {
      
        if (g->board[row][col].isVisible == FALSE
            && g->board[row][col].isFlagged == TRUE) { //if flagged
            return;
        }
    }
    if (g->board[row][col].isVisible == FALSE
        && g->board[row][col].isFlagged == FALSE) {
         
         if (g->board[row][col].isMine == TRUE) { //if there is a mine its K.O
            g->isMineClicked = TRUE;
            printf("LOSER HAHA"); //GameOver
            exit(0);
        }
        if (g->board[row][col].numOfMines > 0) { // clicks it normally
            g->board[row][col].isVisible = TRUE;
            g->hiddenTiles--; // has to lessen the tiles just to know if we won
            return;
        }
        
        if (g->board[row][col].numOfMines==0) { // to spread the clicks if there are no mines near (recursivly of course)
            g->board[row][col].isVisible=TRUE;
            g->hiddenTiles--;// has to lessen the tiles just to know if we won
            if (row - 1 >= 0 && col - 1 >= 0) { // out of bounds stuff
                clickTile(g, row - 1, col - 1);
            }
            if (col - 1 >= 0) {// out of bounds stuff
                clickTile(g, row, col - 1);
            }
            if (row - 1 >= 0) {// out of bounds stuff
                clickTile(g, row - 1, col);
            }
            if (row - 1 >= 0 && col + 1 < g->cols) {// out of bounds stuff
                clickTile(g, row - 1, col + 1);
            
            }
            if (row + 1 < g->rows && col - 1 >= 0) {// out of bounds stuff
                clickTile(g, row + 1, col - 1);
                
            }
            if (row + 1 < g->rows) {// out of bounds stuff
                clickTile(g, row + 1, col);
               
            }
            if (col + 1 < g->cols) {// out of bounds stuff
                clickTile(g, row, col + 1);
                
            }
            if (col + 1 < g->cols && row + 1 < g->rows) {// out of bounds stuff
                clickTile(g, row + 1, col + 1);
            }
        }
    }
}
/*
puts a flag on top of a tile 
depending on the rows/cols and if its clicked or not/flagged or not
*/
void
flagTile(GameBoard *g, int row, int col) {
 if(g->board[row][col].isVisible==TRUE){
  return;
 }
   if(g->board[row][col].isFlagged==TRUE){
    g->board[row][col].isFlagged=FALSE;
   }
   else{
    g->board[row][col].isFlagged=TRUE;
   }
}

/*
prints the board using colorPrint,2 for loops one for the rows,one for the cols
while also checking if we're pointing at that exact tile (cursorCoords)
paints colors depending on each condition
*/
void
printBoard(GameBoard *g, int cursorCoords[2]) {
    for(int i=0;i<g->rows;i++){
     for(int j=0;j<g->cols;j++){
      
      if(i==cursorCoords[0] && j==cursorCoords[1]){ // if we're on that exact tile through the loops
       if(g->board[i][j].isVisible==TRUE){ 
       colorPrint(FG_White,BG_Blue,ATT_Scratch,"%d ",g->board[i][j].numOfMines); 
       }// colorprints the numOfMines on the tile
        
       
       else{
         colorPrint(FG_White,BG_Blue,ATT_Def,"  ");
       }// colorprints the cursor we're moving on the board
        
      }
      else{
       if(g->board[i][j].isVisible==FALSE){
          if(g->board[i][j].isFlagged==TRUE){
          colorPrint(FG_White,BG_Cyan,ATT_Underline,"F "); //colorPrints the flag on the board
          }
          else
        colorPrint(FG_White, BG_White, ATT_Hidden,"  "); //prints default board
       }
      else{
        colorPrint(FG_White,BG_Black,ATT_Scratch,"%d ",g->board[i][j].numOfMines);
      }// colorprints the numOfMines on the tile
     }
    }
    printf("\n");
    }
}
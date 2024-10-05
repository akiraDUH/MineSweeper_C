#include <stdio.h>
#include <stdlib.h>
#include "mineSweeper.h"
#include "colorPrint.h"
#include <time.h>
#include "getch.h"


int
main() {
    int rows, cols, level;
    char moves,dummy; //one for the commands and one as a dummy
    int cursor[] = {0, 0}; //default cursor
    srand(time(NULL)); // to start the timer so the random used in populatemines is actually random
    printf ("Enter Rows: ");
    scanf ("%d", &rows);
    printf ("Enter Cols: ");
    scanf ("%d", &cols);
    printf ("Enter Level: ");
    scanf ("%d", &level);
    dummy=getch(); // used this for the Enter of the scanf above^
    GameBoard *board = malloc(sizeof(GameBoard)); // creates a GameBoard
    initBoard(board, rows, cols, level); //intializes the GameBoard
    printBoard(board,cursor); //prints the GameBoard on the screen
    while (board->isMineClicked == FALSE) { // if no mine is clicked continue
          moves = getch(); // the actual command
        if (moves == CLICK_TILE) { // if pressed on the tile
            clickTile(board,cursor[0], cursor[1]); // clicks the tile that we are in
            clearScreen(); // cleans the screan for printing
            printBoard(board,cursor); // prints the board with the clicked tile/s
            if(board->totalMines==board->hiddenTiles){ // if the player won or not
             printf("You won.., but at what cost ?");// You Won!
             exit(0);// closes the program
            }
        }
        if (moves == FLAG_TILE) {// put a flag on the tile
            flagTile(board,cursor[0],cursor[1]);//the one we are pointing on
            clearScreen();
            printBoard(board,cursor);
        }
        if (moves == QUIT) { // quit the game
            printf("You Quit the game");//exits the game
            exit(0);
        }
        if (moves == LEFT) { //moves left
            if (cursor[1] - 1 < 0) {
                asm("nop"); // doesnt do anything of its illegal and moves to else
            } 
            else {
                cursor[1]-=1; //moves left
                clearScreen();
                printBoard(board, cursor);
            }
        }
        if (moves == RIGHT) {//moves right
             if (cursor[1] + 1 >= board->rows) {
                asm("nop");
            }
             else {
                cursor[1]+=1;//moves right
                clearScreen();
                printBoard(board, cursor);
            }
        } 
           
        if (moves == UP) {//moves UP
                if (cursor[0] - 1 < 0) {
                    asm("nop");

                } 
                else {
                    cursor[0]-=1;//moves UP
                    clearScreen();
                    printBoard(board, cursor);
                }
            }
        if (moves == DOWN) {//moves DOWN
                if (cursor[0]+1 > board->cols-1) {
                    asm("nop");

                }
                 else {
                cursor[0]+=1;  //moves DOWN
                clearScreen();
                printBoard(board, cursor);
                }
            } 
           
        }
    return TRUE;
    }
    


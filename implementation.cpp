#include "specification.h"

#include <iostream>                // for general IO
#include <ctime>
#include <cstdlib>
#include <windows.h>              // for COLOR!
#include <algorithm>

using namespace std;

// CONSTRUCTOR
SlidingPuzzle::SlidingPuzzle() {
     rows = 3;
     cols = 3;

     theBoard = new int* [3];
     for (int i = 0; i < 3; i++) {
          theBoard[i] = new int[3];
     }
}

// OVERLOAD CONSTRUCTOR
SlidingPuzzle::SlidingPuzzle(int width, int height) {
     this->rows = width;
     this->cols = height;

     theBoard = new int* [width];
     for (int i = 0; i < width; i++) {
          theBoard[i] = new int[height];
     }
}

// DESTRUCTOR
SlidingPuzzle::~SlidingPuzzle() {

     for (int i = 0; i < rows; i++) {
          delete[] theBoard[i];
     }
     delete[] theBoard;
}


void SlidingPuzzle::InitializeBoard() {

     theBoard = new int* [rows];
     for (int i = 0; i < rows; i++) {
          theBoard[i] = new int[cols];
     }

     int count = 1;

     for (int r = 0; r < rows; r++) {
          for (int c = 0; c < cols; c++) {
               theBoard[r][c] = count;
               count++;
          }
     }
     theBoard[rows - 1][cols - 1] = 0; // create empty space
}


bool SlidingPuzzle::isBoardSolved() {

     int** ppBoard = reinterpret_cast<int**>(&theBoard); //makes everything work

     bool isSolved = false;
     int count = 1;

     for (int i = 0; i < rows; i++) {
          for (int j = 0; j < cols; j++) {
               if (ppBoard[i][j] != count) { //if board is not sequential, solved is false 
                    return isSolved;
               }
               count++;
               if (count == rows * cols) {
                    isSolved = true; //if board is sequential, solved is true
               }
          }
     }
     return isSolved;
}


bool SlidingPuzzle::slideTile(int directionCode) {

     bool legalMoves[4] = { true, true, true, true }; //[0] = up, [1] = down, [2] = left, [3] = right
     int emptyRow;
     int emptyCol;

     for (int row = 0; row < rows; row++) {
          for (int col = 0; col < cols; col++) {
               if (theBoard[row][col] == 0) // locate empty space
               {
                    emptyRow = row;
                    emptyCol = col;

                    //sliding the tiles
                    switch (directionCode) {

                    // SLIDE_UP
                    case 1:
                         if (emptyRow < rows - 1) {
                              swap(theBoard[emptyRow][emptyCol], theBoard[emptyRow + 1][emptyCol]); //if able to make move, legalmove is true
                              return legalMoves[1];
                         }
                    // SLIDE_DOWN
                    case 2:
                         if (emptyRow > 0) {
                              swap(theBoard[emptyRow][emptyCol], theBoard[emptyRow - 1][emptyCol]);
                              return legalMoves[0];
                         }
                    //SLIDE_RIGHT
                    case 3:
                         if (emptyCol < cols - 1) {
                              swap(theBoard[emptyRow][emptyCol], theBoard[emptyRow][emptyCol + 1]);
                              return legalMoves[3];
                         }
                     //SLIDE_LEFT
                    case 4:
                         if (emptyCol > 0) {
                              swap(theBoard[emptyRow][emptyCol], theBoard[emptyRow][emptyCol - 1]);
                              return legalMoves[2];
                         }
                    default:
                         break;
                    }
               }
          }
     }
     return false;
}

void SlidingPuzzle::scrambleBoard() {
     srand(unsigned(time(nullptr)));
     int move;
     for (int i = 0; i < 100000; i++) //Series of random moves
     {
          move = rand() % 4 + 1;
          slideTile(move);
     }
}

void SlidingPuzzle::PrintBoard() {
     HANDLE hConsole;
     hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
     int n = 1;
     for (int i = 0; i < rows; i++) {
          for (int j = 0; j < cols; j++) {
               if (theBoard[i][j] == 0) {
                    SetConsoleTextAttribute(hConsole, 7); //Prints pivot symbol in default color 
                    cout << " * ";
               }
               else {
                    if (theBoard[i][j] == n) { // if tile is in solved location, color green
                         SetConsoleTextAttribute(hConsole, 10);
                         n++;
                    }
                    else
                         SetConsoleTextAttribute(hConsole, 12); //else, set to red
                    if (theBoard[i][j] < 10) // Print a 0 first if # < 10
                         cout << "0";
                    cout << theBoard[i][j] << " ";
               }
          }
          cout << endl;
     }
     SetConsoleTextAttribute(hConsole, 7);
}


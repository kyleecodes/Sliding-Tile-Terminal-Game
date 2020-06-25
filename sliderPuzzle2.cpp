#include "specification.h"

#pragma warning(disable:4996)

#include <iostream>                // for general IO
#include <conio.h>                // for getche()

using namespace std;

#define UNSET            -1        // used to arbitrarily indicate an undetermined state in a construct

// Direction Codes
#define SLIDE_UP          1      // pass to slideTile() to trigger UP movement
#define SLIDE_DOWN        2      // pass to slideTile() to trigger DOWN movement
#define SLIDE_LEFT        3      // pass to slideTile() to trigger LEFT movement
#define SLIDE_RIGHT       4      // pass to slideTile() to trigger RIGHT movement


int main() {
     // Declarations
     unsigned char keyStroke;                // holds the user's keystrokes as they come in
     string input;
     int directionCode = UNSET;
     int row;
     int col;

     // initializing memory 
     SlidingPuzzle theGame;


     // obtain user input 
     system("CLS");
     cout << "\n\n Choose your row size (3 to 10): ";
     cin >> row;
     if (row < 3 || row > 10)
          cout << "\n\n Please choose a size between 3-10." << endl;

     system("CLS");
          cout << "\n\n Now choose your column size (3 to 10): ";
     cin >> col;
     if (row < col || col > 10)
          cout << "\n\n Please choose a size between 3-10." << endl;
     system("CLS");


     // set up board 
     theGame = SlidingPuzzle(row, col);

     theGame.InitializeBoard();

     theGame.PrintBoard();


     // scramble board 
     cout << "Press enter to begin" << endl;
     cin.get();
     cout << "Scrambling board..." << endl;
     theGame.scrambleBoard();
     cout << "Scrambling complete, press enter to continue" << endl;
     cin.get();

     system("CLS");
     theGame.PrintBoard();
     cout << endl << endl;

     // make a move
     cout << "[W - Up] [S - Right] [A - Left] [D - Down]" << endl;
     cout << "Input: ";
     while (!theGame.isBoardSolved()) { //if not solved, keep making moves
          keyStroke = getche();
          system("CLS");

          switch (tolower(keyStroke)) {
          case 'd':
               directionCode = SLIDE_UP;
               theGame.slideTile(directionCode);
               input = "Down";
               break;
          case 'w':
               directionCode = SLIDE_DOWN;
               theGame.slideTile(directionCode);
               input = "Up";
               break;
          case 's':
               directionCode = SLIDE_LEFT;
               theGame.slideTile(directionCode);
               input = "Right";
               break;
          case 'a':
               directionCode = SLIDE_RIGHT;
               theGame.slideTile(directionCode);
               input = "Left";
               break;
          default:
               break;
          }

          theGame.PrintBoard();
          cout << endl << endl;
          cout << "[W - Up] [S - Right] [A - Left] [D - Down] \n" << "Your choice is: " << input;

     }
     cout << endl;
     cout << "BOARD SOLVED" << endl;
     theGame.~SlidingPuzzle(); //deallocate memory once board is solved.
     system("PAUSE");
     return 0;
}





#ifndef __SLIDINGPUZZLE__
#define __SLIDINGPUZZLE__


#include <iostream>
#include <cstring>

using namespace std;

// CLASS SlidingPuzzle
class SlidingPuzzle {
private:

     int** theBoard;
     int rows;
     int cols;


public:

     // CONSTRUCTORS
     SlidingPuzzle();


     // OVERLOAD CONSTRUCTOR
     SlidingPuzzle(int width, int height);

     // DESTRUCTOR
     ~SlidingPuzzle();

     // METHODS
     void InitializeBoard();

     bool isBoardSolved();

     bool slideTile(int directionCode);

     void scrambleBoard();

     void PrintBoard();

};


#endif
//
//  myFunctions.h
//  ImageComponentLabeling
//
//  Created by Tyler Tivadar on 4/15/19.
//

#ifndef myFunctions_h
#define myFunctions_h

#include "myStructs.h"
#include "stack.h"
#include "stack.cpp"

void getParameters(int&, double&);
void createGrids(pixel**&, pixel**&, int, double);
void displayGrids(pixel**, pixel**, int);
void scanGrids(pixel**&, pixel**&, int);
void scanByDepthFirst(pixel**&, int, int, int);
void scanByBreadthFirst(pixel**&, int, int, int);

#endif /* myFunctions_h */

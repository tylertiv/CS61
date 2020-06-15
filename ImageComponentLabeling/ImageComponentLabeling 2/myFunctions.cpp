//
//  myFunctions.cpp
//  ImageComponentLabeling
//
//  Created by Tyler Tivadar on 4/15/19.
//

#include <iostream>
#include <queue>
#include <iomanip>
#include "myFunctions.h"

using namespace std;

void getParameters(int& dimension, double& density)
{ // get user input
    do
    {
        cout << "Please enter an image dimension between 5 and 20 pixels: ";
        cin >> dimension;
        cout << endl;
    } // repeats until user enters valid information
    while(dimension < 5 || dimension > 20);
    
    do
    {
        cout << "Please enter an image density between 0 and 1.0: ";
        cin >> density;
        cout << endl;
    } // repeats until user enters valid information
    while(density < 0 || density > 1);
}

void createGrids(pixel** &dfsGrid, pixel** &bfsGrid, int dimension, double density)
{
    // create array of arrays for each board
    // created with dimension + 2 for border to make search easier
    dfsGrid = new pixel* [dimension + 2];
    bfsGrid = new pixel* [dimension + 2];
    
    for (int i = 0; i < dimension + 2; i++)
    { // initialize each secondary array in the array of arrays
        dfsGrid[i] = new pixel [dimension + 2];
        bfsGrid[i] = new pixel [dimension + 2];
    }
    
    int r; double myR;
    
    // seed random integer
    srand((unsigned int)time(NULL));
    for(int row = 1; row <= dimension; row++)
        for(int col = 1; col <= dimension; col++)
        { // for each board space, generate random number to determine if it is a 1 or 0
            r = rand();
            myR = (double)r / INT_MAX;
            if(myR < density)
                dfsGrid[row][col].label = bfsGrid[row][col].label = 1;
            else
                dfsGrid[row][col].label = bfsGrid[row][col].label = 0;
        }
    
    // initialize border wall of 0's to make search easier
    for (int i = 0; i <= dimension + 1; i++)
    {
        dfsGrid[0][i].label = dfsGrid[dimension + 1][i].label = bfsGrid[0][i].label = bfsGrid[dimension + 1][i].label = 0; // bottom and top
        dfsGrid[i][0].label = dfsGrid[i][dimension + 1].label = bfsGrid[i][0].label = bfsGrid[i][dimension + 1].label = 0; // left and right
    }
}

void displayGrids(pixel** dfsGrid, pixel** bfsGrid, int dimension)
{
    cout << "Grid for Depth First Search:" << endl;
    for(int row = 0; row <= dimension + 1; row++)
    {
        for(int col = 0; col <= dimension + 1; col++)
            cout << right << setw(4) << dfsGrid[row][col].label << ","
                 << left << setw(2) << dfsGrid[row][col].order;
        cout << endl;
    }
    
    cout << endl << "Grid for Breadth First Search:" << endl;
    for(int row = 0; row <= dimension + 1; row++)
    {
        for(int col = 0; col <= dimension + 1; col++)
            cout << right << setw(4) << bfsGrid[row][col].label << ","
                 << left << setw(2) << bfsGrid[row][col].order;
        cout << endl;
    }
    
    cout << endl;
}

void scanGrids(pixel** &dfsGrid, pixel** &bfsGrid, int dimension)
{
    int componentLabel = 1;
    for(int row = 1; row <= dimension; row++)
        for(int col = 1; col <= dimension; col++)
            if(dfsGrid[row][col].label == 1)
            { //if the current component is part of an unlabeled component, label the component by depth first and breadth first search
                componentLabel++;
                scanByDepthFirst(dfsGrid, componentLabel, row, col);
                scanByBreadthFirst(bfsGrid, componentLabel, row, col);
            }
                
}

void scanByDepthFirst(pixel** &dfsGrid, int componentLabel, int row, int col)
{
    // initalize offsets of neighbors for ease of seach
    position offset[4];
    offset[0].row = 0; offset[0].col = 1;   // right
    offset[1].row = 1; offset[1].col = 0;   // down
    offset[2].row = 0; offset[2].col = -1;  // left
    offset[3].row = -1; offset[3].col = 0;  // up
    
    // declare and initialize variables
    stack<position> dfsStack;
    int orderFound = 1;
    int option = 0;
    int lastOption = 3;
    
    // label the first pixel of the component
    position here = {row, col};
    dfsGrid[row][col].label = componentLabel;
    dfsGrid[row][col].order = orderFound;
    
    do
    { // continues searching until stack is empty, will break then as all pixels have been labeled
        int r = 0, c = 0;
    
        while (option <= lastOption)
        { // loops until a neighbor pixel is found, or until all options have been checked
            r = here.row + offset[option].row;
            c = here.col + offset[option].col;
            if (dfsGrid[r][c].label == 1) break;
            option++; // next option
        }
        
        if (option <= lastOption)
        { //option was found, proceed in a depth first manner to check that direction
            ++orderFound;
            dfsStack.push(here);
            here.row = r;
            here.col = c;
            dfsGrid[r][c].label = componentLabel;
            dfsGrid[r][c].order = orderFound;
            option = 0;
        }
        else
        { //option was not found, check if stack has other directions to check,
          //if it doesnt, stack should be empty and all pixels of component labled
            if (dfsStack.empty())
                break;
            position next = dfsStack.top();
            dfsStack.pop();
            if (next.row == here.row)
                option = 2 + next.col - here.col;
            else option = 3 + next.row - here.row;
            here = next;
        }
    }
    while(true);
    
}

void scanByBreadthFirst(pixel** &bfsGrid, int componentLabel, int row, int col)
{
    position offset[4];
    offset[0].row = 0; offset[0].col = 1;   // right
    offset[1].row = 1; offset[1].col = 0;   // down
    offset[2].row = 0; offset[2].col = -1;  // left
    offset[3].row = -1; offset[3].col = 0;  // up
    
    queue<position> bfsQueue;
    
    position neighbor;
    
    int orderFound = 1;
    int numberNeighbors = 4;
    
    position here = {row, col};
    bfsGrid[row][col].label = componentLabel;
    bfsGrid[row][col].order = orderFound++;
    
    do
    { // continues scan until queue is empty, will then break as all pixels have been labeled
        for(int i = 0; i < numberNeighbors; i++)
        { // for each neighbor, check if it is part of compnent
            neighbor.row = here.row + offset[i].row;
            neighbor.col = here.col + offset[i].col;
            
            if(bfsGrid[neighbor.row][neighbor.col].label == 1)
            { // if it is part of component, label and put in queue for further exploration later
                bfsGrid[neighbor.row][neighbor.col].label = componentLabel;
                bfsGrid[neighbor.row][neighbor.col].order = orderFound++;
                bfsQueue.push(neighbor);
            }
        }
        
        // will break if no more options in queue to explore, else will explore next option in queue
        if(bfsQueue.empty())
            break;
        here = bfsQueue.front();
        bfsQueue.pop();
    }
    while (true);
}

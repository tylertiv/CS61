//
//  main.cpp
//  ImageComponentLabeling
//
//  Created by Tyler Tivadar on 4/15/19.
//

#include <iostream>
#include "myFunctions.h"

using namespace std;

int main()
{
    // declare variables needed
    int dimension = -1;
    double density = -1;
    
    pixel **dfsGrid, **bfsGrid;
    
    // welcome and get user input
    cout << "Welcome to the Image Component Labeling Machine" << endl << endl;
    getParameters(dimension, density);
    createGrids(dfsGrid, bfsGrid, dimension, density);
    
    // output randomly generated grid
    cout << "Grids before Scan:" << endl;
    displayGrids(dfsGrid, bfsGrid, dimension);
    
    // perform the scan by dfs and bfs
    scanGrids(dfsGrid, bfsGrid, dimension);
    
    // output scanned grids
    cout << "Grids after Scan:" << endl;
    displayGrids(dfsGrid, bfsGrid, dimension);
    
    return 0;
}

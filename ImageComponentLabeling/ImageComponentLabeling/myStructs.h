//
//  myStructs.h
//  ImageComponentLabeling
//
//  Created by Tyler Tivadar on 4/15/19.
//

#ifndef myStructs_h
#define myStructs_h

struct position
{
    int row,  // row number of position
    col;  // column number of position
    
    operator int() const {return row;}
};

struct pixel
{
    int label = 0;
    int order = 0;
};

#endif /* myStructs_h */

/*
 * Image Component Labeling
 * Project 1
 * Tyler Tivadar
 * 1-15-2019
 *
 * Purpose and usage of this application
 *   . . .
 *   . . .
 *
 */


// . . .
// . . .
// . . .


// global variables

/*
 * pixel should be redesigned as an object, instead of int, with two fields, 
 * as described in the Assignment Specification document  
 */

#include Postition.h

int **pixel;
int size;      // number of rows and columns in the image

// functions
void welcome()
{
   // Optional code goes here
}

void inputImage()
{// Input the image.
   cout << "Enter image size" << endl;
   cin >> size;

   // create and input the pixel array
   make2dArray(pixel, size + 2, size + 2);
   cout << "Enter the pixel array in row-major order" << endl;
   /*
    * Either ask user for input grid or generate random numbers (zeros and ones)
    */
   for (int i = 1; i <= size; i++)
      for (int j = 1; j <= size; j++)
          // cin >> pixel[i][j]... ;
}

void labelComponents()
{// Label the components.

   // initialize offsets
   position offset[4];
   offset[0].row = 0; offset[0].col = 1;   // right
   offset[1].row = 1; offset[1].col = 0;   // down
   offset[2].row = 0; offset[2].col = -1;  // left
   offset[3].row = -1; offset[3].col = 0;  // up
   
   // initialize wall of 0 pixels
   for (int i = 0; i <= size + 1; i++)
   {
      // Your code goes here
   }

   int numOfNbrs = 4; // neighbors of a pixel position

   // scan all pixels labeling components
   arrayQueue<position> q;
   position here, nbr;
   int id = 1;  // component id
   for (int r = 1; r <= size; r++)      // row r of image
      for (int c = 1; c <= size; c++)   // column c of image
        if (pixel[r][c].label == 1)
        {

            /*
             *  New image Component
             *
             *  Your code goes here
             */
   

        } // end of if, for c, and for r
}

void outputImage()
{// Output labeled image.

   cout << "The labeled image is" << endl;
   for (int i = 1; i <= size; i++)
   {
      for (int j = 1; j <= size; j++)
         // cout << pixel[i][j]... << "  ";
      cout << endl;
   }
}

void main()
{
   welcome();
   inputImage();
   labelComponents();
   outputImage();
}

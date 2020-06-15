//
//  stack.cpp
//  ImageComponentLabeling
//
//  Adapted from sample code for Rat in Maze
//  by Tyler Tivadar on 4/19/19.
//

#include "stack.h"
#include <algorithm> // needed for min() function

using namespace std;

template<class T>
stack<T>::stack(int initialCapacity)
{// Constructor.
    if (initialCapacity < 1)
        exit(1);
    arrayLength = initialCapacity;
    stackArr = new T[arrayLength];
    stackTop = -1;
}

template<class T>
T& stack<T>::top()
{
    if (stackTop == -1)
        exit(1);
    return stackArr[stackTop];
}

template<class T>
void stack<T>::pop()
{
    if (stackTop == -1)
        exit(1);
    stackArr[stackTop--].~T();  // destructor for T
}

template<class T>
void stack<T>::push(const T& theElement)
{
    if (stackTop == arrayLength - 1)
    {
        changeLength1D(stackArr, arrayLength, 2 * arrayLength);
        arrayLength *= 2;
    }
    stackArr[++stackTop] = theElement;
}

template<class T>
void stack<T>::changeLength1D(T*& a, int oldLength, int newLength)
{
    if (newLength < 0)
        exit(1);
    
    T* temp = new T[newLength];              // new array
    int number = min(oldLength, newLength);  // number to copy
    copy(a, a + number, temp);
    delete [] a;                             // deallocate old memory
    a = temp;
}

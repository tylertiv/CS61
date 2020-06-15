//
//  stack.hpp
//  ImageComponentLabeling
//
// Adapted from sample code for Rat in Maze
//  by Tyler Tivadar on 4/19/19.
//

#ifndef stack_h
#define stack_h

#include <stdio.h>

using namespace std;

template<class T>
class stack
{
public:
    stack<T>(int initialLength = 10);
    ~stack() {delete [] stackArr;}
    
    bool empty() const {return stackTop == -1;}
    int size() const {return stackTop + 1;}
    
    T& top();
    void pop();
    void push(const T& theElement);

private:
    int stackTop;         // current top of stack
    int arrayLength;      // stack capacity
    T *stackArr;
    
    void changeLength1D(T*& a, int oldLength, int newLength);
};
#endif /* stack_h */

//
//  PriorityQueue.hpp
//  DiscreteEventSimulation
//
//  Implements a MIN priority queue
//  Created by Tyler Tivadar on 5/26/19.
//  Copyright © 2019 Tyler Tivadar. All rights reserved.
//

#ifndef PriorityQueue_h
#define PriorityQueue_h

#include <vector>

template <class key>
class MinPQ
{
public:
    MinPQ(int size);                     //create a priority queue with given keys
    ~MinPQ();
    void push(key v);                //insert a key into the priority queue
    key pop();                      //return and remove the element with tsmallestkey
    bool empty() {return N == 0;}      //is the priority queue empty?
    key top() {return pq[1];}         //  return the element with the smallest key
    int size() {return N;}               //number of entries in the priority queue

private:
    void sink(int, int);
    void swim(int);
    bool greater(int i, int j) { return pq[i] > pq[j];}
    void exch(int i, int j) { key t = pq[i]; pq[i] = pq[j]; pq[j] = t; }

    int N;
    key* pq;
};

template<class key>
MinPQ<key>::MinPQ(int size)
{
    N = 0;
    pq = new key[size+1];
}

template<typename key>
MinPQ<key>::~MinPQ()
{
    delete[] pq;
}

template<class key>
void MinPQ<key>::push(key x)
{
    pq[++N] = x;
    swim(N);
}

template<class key>
key MinPQ<key>::pop()
{
    key max = pq[1];
    exch(1, N--);
    sink(1, N);
    pq[N+1] = NULL;
    return max;
}

template<class key>
void MinPQ<key>::sink(int k, int n)
{
    while (2*k <= N)
    {
        int j = 2*k;
        if (j < N && greater(j, j+1)) j++;
        if (!greater(k, j)) break;
        exch(k, j);
        k = j;
    }
}

template<class key>
void MinPQ<key>::swim(int k)
{
    while (k > 1 && greater(k/2, k))
    {
        exch(k, k/2);  //parent of
        k = k/2;    //node k is at k/2
    }
}

#endif  /* PriorityQueue_hpp */


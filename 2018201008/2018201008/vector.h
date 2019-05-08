#ifndef VECTOR_H
#define VECTOR_H

class vector
{
  public:

    int * array;
    int max_size;
    int start_index;
    int end_index;
    vector();
    vector(int n,int x);
    void push_back(int x);
    void pop_back();
    void insert(int index,int x);
    void erase(int index);
    int operator[](int index);
    int size();
    int front();
    int back();
};

#endif

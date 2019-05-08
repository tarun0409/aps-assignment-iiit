#include<iostream>
#include<stdlib.h>
#include "vector.h"

using namespace std;
vector::vector()
{
  start_index = 0;
  end_index = 0;
  max_size = 0;
}

vector::vector(int n,int x)
{
  array = (int *)calloc(n,sizeof(int));
  max_size = n;
  start_index = 0;
  end_index = 0;
  while(end_index<n)
  {
    array[end_index] = x;
    end_index++;
  }
}

void vector::push_back(int x)
{
  if(max_size<=0)
  {
    array = (int *)calloc(1,sizeof(int));
    max_size = 1;
  }
  else if(end_index>=max_size)
  {
    max_size = max_size*2;
    int * new_array = (int *)calloc(max_size,sizeof(int));
    for(int i=start_index; i<end_index; i++)
    {
      new_array[i] = array[i];
    }
    array = new_array;
  }
  array[end_index] = x;
  end_index++;
}

void vector::pop_back()
{
  end_index--;
  if(end_index<=(max_size/2))
  {
    max_size = max_size/2;
    if(max_size<=0)
    {
      return;
    }
    int * new_array = (int *)calloc(max_size,sizeof(int));
    for(int i=start_index; i<end_index; i++)
    {
      new_array[i] = array[i];
    }
    array = new_array;
  }
}

void vector::insert(int index,int x)
{
  if(index<start_index || index>=end_index)
  {
    cout<<"\nArray index out of bounds.\n";
    exit(0);
  }
  if(end_index>=max_size)
  {
    max_size = max_size*2;
    int * new_array = (int *)calloc(max_size,sizeof(int));
    for(int i=start_index; i<end_index; i++)
    {
      new_array[i] = array[i];
    }
    array = new_array;
  }
  for(int i=(end_index-1); i>=index; i--)
  {
    array[i+1] = array[i];
  }
  array[index] = x;
  end_index++;
}

void vector::erase(int index)
{
  if(index<start_index || index>=end_index)
  {
    cout<<"\nArray index out of bounds.\n";
    exit(0);
  }
  for(int i=(index+1); i<end_index; i++)
  {
    array[i-1] = array[i];
  }
  end_index--;
  if(end_index<=(max_size/2))
  {
    max_size = max_size/2;
    if(max_size<=0)
    {
      return;
    }
    int * new_array = (int *)calloc(max_size,sizeof(int));
    for(int i=start_index; i<end_index; i++)
    {
      new_array[i] = array[i];
    }
    array = new_array;
  }
}

int vector::operator[](int index)
{
  if(index<start_index || index>=end_index)
  {
    cout<<"\nArray index out of bounds.\n";
    exit(0);
  }
  return array[index];
}

int vector::size()
{
  return end_index;
}

int vector::front()
{
  if(end_index==0)
  {
    cout<<"\nArray index out of bounds\n";
    exit(0);
  }
  return array[start_index];
}

int vector::back()
{
  if(end_index==0)
  {
    cout<<"\nArray index out of bounds\n";
    exit(0);
  }
  return array[end_index-1];
}

#include<iostream>
#include<stdlib.h>

using namespace std;

class vector
{
	public:
	
	int * array;
	int max_size;
	int start_index;
	int end_index;
	
	vector()
	{
		array = (int *)calloc(1,sizeof(int));
		start_index = 0;
		end_index = 0;
		max_size = 1;
	}
	
	vector(int n,int x)
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
	
	void push_back(int x)
	{
		if(end_index<max_size)
		{
			array[end_index] = x;
			end_index++;
		}
		else
		{
			max_size = max_size*2;
			int * new_array = (int *)calloc(max_size,sizeof(int));
			for(int i=start_index; i<end_index; i++)
			{
				new_array[i] = array[i];
			}
			array = new_array;
			array[end_index] = x;
			end_index++;
		}
	}
	
	void pop_back()
	{
		end_index--;
		if(end_index<=(max_size/2))
		{
			max_size = max_size/2;
			max_size = (max_size<=0)?1:max_size;
			int * new_array = (int *)calloc(max_size,sizeof(int));
			for(int i=start_index; i<end_index; i++)
			{
				new_array[i] = array[i];
			}
			array = new_array;
		}
	}
	
	
	int operator[](int index)
	{
		if(index<start_index || index>=end_index)
		{
			cout<<"\nArray index out of bounds.\n";
			exit(0);
		}
		return array[index];
	}
	
	int size()
	{
		return end_index;
	}
};



int main()
{
	vector vec;
	for(int i=1; i<=32; i++)
	{
		vec.push_back(i);
		cout<<endl<<"Pushed "<<i<<" size="<<vec.size()<<" max size = "<<vec.max_size<<endl;
	}
	for(int i=32; i>=1; i--)
	{
		vec.pop_back();
		cout<<endl<<"Popped "<<i<<" size="<<vec.size()<<" max size = "<<vec.max_size<<endl;
	}
	return 0;
}
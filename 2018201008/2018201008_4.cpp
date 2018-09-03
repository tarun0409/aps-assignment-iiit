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
		start_index = 0;
		end_index = 0;
		max_size = 0;
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
	
	void pop_back()
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
	
	void insert(int index,int x)
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
	
	void erase(int index)
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
	
	int front()
	{
		if(end_index==0)
		{
			cout<<"\nArray index out of bounds\n";
			exit(0);
		}
		return array[start_index];
	}
	
	int back()
	{
		if(end_index==0)
		{
			cout<<"\nArray index out of bounds\n";
			exit(0);
		}
		return array[end_index-1];
	}
	
};



int main()
{
	vector vec;
	for(int i=1; i<=100; i++)
	{
		vec.push_back(i);
		cout<<endl<<"Pushed "<<i<<" size="<<vec.size()<<" max size = "<<vec.max_size<<endl;
	}
	for(int i=1; i<=30; i++)
	{
		vec.erase(6);
		cout<<endl<<"Erased "<<i<<" size="<<vec.size()<<" max size = "<<vec.max_size<<endl;
	}
	cout<<endl;
	for(int i=0; i<vec.size(); i++)
	{
		cout<<vec[i]<<"  ";
	}
	cout<<endl;
	return 0;
}
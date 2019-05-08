#include<iostream>
#include<algorithm>
#include<vector>
#include<string>

using namespace std;

struct node
{
  int value;
  int way;
};

class min_priority_queue
{
	public:

	struct node * pri_queue;
  long size;
	long max_size;

	min_priority_queue(long n)
	{
		pri_queue = (struct node *)malloc(n*sizeof(struct node));
		size = 0;
		max_size = n;
	}

  struct node create_node(int v, int w)
  {
    struct node new_node;
    new_node.value = v;
    new_node.way = w;
    return new_node;
  }

	long get_heap_size()
	{
		return size;
	}

	int get_min_value()
	{
		if(size==0)
		{
			cout<<"\n\nHeap is empty\n\n";
			exit(1);
		}
		return (pri_queue[0]).value;
	}
  int get_min_way()
  {
    if(size==0)
		{
			cout<<"\n\nHeap is empty\n\n";
			exit(1);
		}
		return (pri_queue[0]).way;
  }

	int get_parent(int index)
	{
		if(index==0)
		{
			return -1;
		}
		if(index%2==0)
		{
			return ((index/2)-1);
		}
		if(index%2!=0)
		{
			return (index/2);
		}
	}

	int get_left_child(int index)
	{
		int lc = (index*2) + 1;
		if(lc>=size)
		{
			return -1;
		}
		return lc;
	}

	int get_right_child(int index)
	{
		int rc = (index*2)+2;
		if(rc>=size)
		{
			return -1;
		}
		return rc;
	}

	void insert(int v, int w)
	{
		if(size>=max_size)
		{
			return;
		}
    struct node new_node = create_node(v,w);
		pri_queue[size] = new_node;
		int parent = get_parent(size);
		int curr_index = size;
		while(parent>-1)
		{
			if(((pri_queue[parent]).value)>((pri_queue[curr_index]).value))
			{
				struct node temp = pri_queue[parent];
				pri_queue[parent] = pri_queue[curr_index];
				pri_queue[curr_index] = temp;
				curr_index = parent;
				parent = get_parent(curr_index);
			}
			else
			{
				break;
			}
		}
		size++;
	}

	struct node extract_min()
	{
		if(size==0)
		{
				cout<<"\n\nHeap is empty\n\n";
				exit(1);
		}
		if(size==1)
		{
			struct node x = pri_queue[0];
			size--;
			return x;
		}
		struct node min = pri_queue[0];
		pri_queue[0] = pri_queue[size-1];
		pri_queue[size-1] = min;
		size--;
		int c_i = 0;
		int l_i = get_left_child(c_i);
		int r_i = get_right_child(c_i);
		while(l_i>=0 && l_i<size)
		{
			int min_i = c_i;
			if(((pri_queue[l_i]).value) < ((pri_queue[c_i]).value))
			{
				min_i = l_i;
			}
			if((r_i>=0 && r_i < size) && ((pri_queue[r_i]).value) < ((pri_queue[min_i]).value))
			{
				min_i = r_i;
			}
			if(c_i == min_i)
			{
				break;
			}
			else
			{
				struct node temp = pri_queue[c_i];
				pri_queue[c_i] = pri_queue[min_i];
				pri_queue[min_i] = temp;
			}
			c_i = min_i;
			l_i = get_left_child(c_i);
			r_i = get_right_child(c_i);
		}
		return min;

	}

  void print_heap()
  {
    cout<<"\n\nHEAP IS\n\n";
    for(int i=0; i<size; i++)
    {
      cout<<(pri_queue[i]).value<<"  ";
    }
    cout<<"\n\n";
  }


};

long get_file_size(FILE * fp)
{
  fseek(fp, 0L, SEEK_END);
  long sz = ftell(fp);
  rewind(fp);
  return sz;
}

char * convert_string_to_char(string str)
{
	int n = str.length();
	char * chars = (char *)malloc((n+1)*sizeof(char));
	int i;
	for(i=0; i<n; i++)
	{
		chars[i] = str[i];
	}
	chars[i] = '\0';
	return chars;
}

char * get_file_name(int w)
{
  string file_name = "temp_file";
  string way = to_string(w);
  file_name=file_name.append(way);
  file_name=file_name.append(".txt");
  char * file = convert_string_to_char(file_name);
  return file;
}


int main(int argc, char const *argv[]) {

  if(argc < 3)
  {
    cout<<"\nPlease enter name of input file and output file(space separated)\n";
    exit(1);
  }

  int K;
  cout<<"\nEnter the value of k: ";
  cin>>K;
  FILE * fr = fopen(argv[1],"r+");
  FILE * fw = fopen(argv[2],"w+");
  fclose(fw);
  long hs = get_file_size(fr);
  hs = (hs/K) + 1;

  min_priority_queue MIN = min_priority_queue(hs);

  vector<int> k_arr;
  int it = 1;
  int num;
  int k = 0;
  int way = 0;
  while(it>0)
  {
    if(k>=K)
    {
      k=0;
      sort(k_arr.begin(),k_arr.end());
      MIN.insert(k_arr[0],way);
      char * file_name = get_file_name(way);
      FILE * file = fopen(file_name,"w+");
      for(int j=1; j<k_arr.size(); j++)
      {
        fprintf(file,"%d\n",k_arr[j]);
      }
      fclose(file);
      way++;
      k_arr.clear();
    }
    it = fscanf(fr,"%d",&num);
    if(it<=0)
    {
      break;
    }
    else
    {
      k_arr.push_back(num);
      k++;
    }
  }
  if(!k_arr.empty())
  {
    sort(k_arr.begin(),k_arr.end());
    MIN.insert(k_arr[0],way);
    char * file_name = get_file_name(way);
    FILE * file = fopen(file_name,"w+");
    for(int j=1; j<k_arr.size(); j++)
    {
      fprintf(file,"%d\n",k_arr[j]);
    }
    fclose(file);
    way++;
    k_arr.clear();
  }
  FILE * out = fopen(argv[2],"a");
  while(MIN.get_heap_size() != 0)
  {
    int e = MIN.get_min_value();
    int w = MIN.get_min_way();
    MIN.extract_min();
    char * file_name = get_file_name(w);
    FILE * tr = fopen(file_name,"r");
    vector<int> temp_vec;
    int num;
    while(fscanf(tr,"%d",&num) > 0)
    {
      temp_vec.push_back(num);
    }
    fclose(tr);
    if(!temp_vec.empty())
    {
        num = temp_vec[0];
        MIN.insert(num,w);
        FILE * tw = fopen(file_name,"w+");
        for(int i=1; i<temp_vec.size(); i++)
        {
          fprintf(tw,"%d\n",temp_vec[i]);
        }
        fclose(tw);
    }
    fprintf(out,"%d\n",e);
  }
  fclose(out);

  return 0;
}

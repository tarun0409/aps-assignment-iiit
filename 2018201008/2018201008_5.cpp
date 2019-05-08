#include<iostream>
#include<stdio.h>

using namespace std;

class min_priority_queue
{
    public:

    double * pri_queue;
    int size;
    int max_size;

    min_priority_queue(int n)
    {
        pri_queue = (double *)malloc(n*sizeof(double));
        size = 0;
        max_size = n;
    }

    int get_heap_size()
    {
        return size;
    }

    double get_min_element()
    {
        if(size==0)
        {
            cout<<"\n\nHeap is empty\n\n";
            exit(1);
        }
        return pri_queue[0];
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
        return -1;
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

    void insert(double x)
    {
        if(size>=max_size)
        {
            return;
        }
        pri_queue[size] = x;
        int parent = get_parent(size);
        int curr_index = size;
        while(parent>-1)
        {
            if(pri_queue[parent]>pri_queue[curr_index])
            {
                double temp = pri_queue[parent];
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

    double extract_min()
    {
        if(size==0)
        {
                cout<<"\n\nHeap is empty\n\n";
                exit(1);
        }
        if(size==1)
        {
            double x = pri_queue[0];
            size--;
            return x;
        }
        double min = pri_queue[0];
        pri_queue[0] = pri_queue[size-1];
        pri_queue[size-1] = min;
        size--;
        int c_i = 0;
        int l_i = get_left_child(c_i);
        int r_i = get_right_child(c_i);
        while(l_i>=0 && l_i<size)
        {
            int min_i = c_i;
            if(pri_queue[l_i] < pri_queue[c_i])
            {
                min_i = l_i;
            }
            if((r_i>=0 && r_i < size) && pri_queue[r_i] < pri_queue[min_i])
            {
                min_i = r_i;
            }
            if(c_i == min_i)
            {
                break;
            }
            else
            {
                double temp = pri_queue[c_i];
                pri_queue[c_i] = pri_queue[min_i];
                pri_queue[min_i] = temp;
            }
            c_i = min_i;
            l_i = get_left_child(c_i);
            r_i = get_right_child(c_i);
        }
        return min;

    }


};

class max_priority_queue
{
    public:

    double * pri_queue;
    int size;
    int max_size;

    max_priority_queue(int n)
    {
        pri_queue = (double *)malloc(n*sizeof(double));
        size = 0;
        max_size = n;
    }

    int get_heap_size()
    {
        return size;
    }

    double get_max_element()
    {
        if(size==0)
        {
            cout<<"\n\nHeap is empty\n\n";
            exit(1);
        }
        return pri_queue[0];
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
        return -1;
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

    void insert(double x)
    {
        if(size>=max_size)
        {
            return;
        }
        pri_queue[size] = x;
        int parent = get_parent(size);
        int curr_index = size;
        while(parent>-1)
        {
            if(pri_queue[parent]<pri_queue[curr_index])
            {
                double temp = pri_queue[parent];
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

    double extract_max()
    {
        if(size==0)
        {
                cout<<"\n\nHeap is empty\n\n";
                exit(1);
        }
        if(size==1)
        {
            double x = pri_queue[0];
            size--;
            return x;
        }
        double max = pri_queue[0];
        pri_queue[0] = pri_queue[size-1];
        pri_queue[size-1] = max;
        size--;
        int c_i = 0;
        int l_i = get_left_child(c_i);
        int r_i = get_right_child(c_i);
        while(l_i>=0 && l_i<size)
        {
            int max_i = c_i;
            if(pri_queue[l_i] > pri_queue[c_i])
            {
                max_i = l_i;
            }
            if((r_i>=0 && r_i < size) && pri_queue[r_i] > pri_queue[max_i])
            {
                max_i = r_i;
            }
            if(c_i == max_i)
            {
                break;
            }
            else
            {
                double temp = pri_queue[c_i];
                pri_queue[c_i] = pri_queue[max_i];
                pri_queue[max_i] = temp;
            }
            c_i = max_i;
            l_i = get_left_child(c_i);
            r_i = get_right_child(c_i);
        }
        return max;

    }


};

int main()
{
    int N;
    scanf("%d",&N);
    int W = ((N+4)/2);
    double median = 0;
    max_priority_queue MAX = max_priority_queue(W);
    min_priority_queue MIN = min_priority_queue(W);
    for(int i=0; i<N; i++)
    {
        double e;
        scanf("%lf",&e);
        if(MAX.get_heap_size()==0)
        {
            MAX.insert(e);
            median = e;
        }
        else
        {
            if(e<=median)
            {
                if(MAX.get_heap_size() > MIN.get_heap_size())
                {
                    double f = MAX.extract_max();
                    MIN.insert(f);
                }
                MAX.insert(e);
            }
            else
            {
                if(MIN.get_heap_size() > MAX.get_heap_size())
                {
                    double f = MIN.extract_min();
                    MAX.insert(f);
                }
                MIN.insert(e);
            }
            if(MAX.get_heap_size() > MIN.get_heap_size())
            {
                median = MAX.get_max_element();
            }
            else if(MIN.get_heap_size() > MAX.get_heap_size())
            {
                median = MIN.get_min_element();
            }
            else
            {
                double x = MAX.get_max_element();
                double y = MIN.get_min_element();
                median = ((x+y)/2);
            }
        }
        printf("%0.1lf",median);
        if(i!=(N-1))
        {
                cout<<"\n";
        }
    }
    return 0;
}

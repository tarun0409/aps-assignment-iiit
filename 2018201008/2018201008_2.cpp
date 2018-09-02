#include<iostream>
#include<queue>
using namespace std;

struct node
{
	int value;
	struct node * left_child;
	struct node * right_child;
	struct node * parent;
	int height;
	int balance_factor;
};

struct k_struct
{
	int k;
	int kse;
};

struct node * root = NULL;

struct node * create_node(int val)
{
	struct node * new_node = (struct node *)malloc(sizeof(struct node));
	new_node->value = val;
	new_node->left_child = NULL;
	new_node->right_child = NULL;
	new_node->parent = NULL;
	new_node->height = 1;
	new_node->balance_factor = 0;
	return new_node;
}

void update_height(struct node * curr_node)
{
	int max_h = -1;
	if(curr_node->left_child!=NULL)
	{
		if((curr_node->left_child->height) > max_h)
		{
			max_h = curr_node->left_child->height;
		}
	}
	if(curr_node->right_child!=NULL)
	{
		if((curr_node->right_child->height) > max_h)
		{
			max_h = curr_node->right_child->height;
		}
	}
	if(max_h>-1)
	{
		curr_node->height = (max_h+1);
	}
	else if(max_h==-1)
	{
		curr_node->height = 1;
	}
}

void update_balance_factor(struct node * curr_node)
{
	int l_h = 0;
	int r_h = 0;
	if(curr_node->value == 4)
	{
		int x = 0;
		x++;
	}
	if(curr_node->left_child!=NULL)
	{
		l_h = curr_node->left_child->height;
	}
	if(curr_node->right_child!=NULL)
	{
		r_h = curr_node->right_child->height;
	}
	curr_node->balance_factor = (l_h-r_h);
}

void left_left_rotation(struct node * curr_node)
{
	struct node * temp = curr_node ->right_child;
	curr_node->right_child = curr_node->parent;
	curr_node->parent->left_child = temp;
	if(temp!=NULL)
	{
		temp->parent = curr_node->parent;
	}
	if(curr_node->parent == root)
	{
		root = curr_node;
		curr_node->parent->parent = curr_node;
		curr_node->parent = NULL;
	}
	else
	{
		if((curr_node->parent->parent->value) > (curr_node->parent->value))
		{
			curr_node->parent->parent->left_child = curr_node;
		}
		else
		{
			curr_node->parent->parent->right_child = curr_node;
		}
		struct node * temp_parent = curr_node->parent;
		curr_node->parent = curr_node->parent->parent;
		temp_parent->parent = curr_node;
	}
}

void right_right_rotation(struct node * curr_node)
{
	struct node * temp = curr_node->left_child;
	curr_node->left_child = curr_node->parent;
	curr_node->parent->right_child = temp;
	if(temp!=NULL)
	{
		temp->parent = curr_node->parent;
	}
	if(curr_node->parent==root)
	{
		root = curr_node;
		curr_node->parent->parent = curr_node;
		curr_node->parent = NULL;
	}
	else
	{
		if((curr_node->parent->parent->value) > (curr_node->parent->value))
		{
			curr_node->parent->parent->left_child = curr_node;
		}
		else
		{
			curr_node->parent->parent->right_child = curr_node;
		}
		struct node * temp_parent = curr_node->parent;
		curr_node->parent = curr_node->parent->parent;
		temp_parent->parent = curr_node;
	}
}
void left_right_rotation(struct node * curr_node)
{
	struct node * temp1 = curr_node->left_child;
	curr_node->left_child = curr_node->parent;
	curr_node->parent->right_child = temp1;
	if(temp1!=NULL)
	{
		temp1->parent = curr_node->parent;
	}
	curr_node->parent->parent->left_child = curr_node;
	struct node * temp2 = curr_node->parent;
	curr_node->parent = curr_node->parent->parent;
	temp2->parent = curr_node;
}

void right_left_rotation(struct node * curr_node)
{
	struct node * temp1 = curr_node->right_child;
	curr_node->right_child = curr_node->parent;
	curr_node->parent->left_child = temp1;
	if(temp1!=NULL)
	{
		temp1->parent = curr_node->parent;
	}
	curr_node->parent->parent->right_child = curr_node;
	struct node * temp2 = curr_node->parent;
	curr_node->parent = curr_node->parent->parent;
	temp2->parent  = curr_node;
}

void check_and_balance_tree(struct node * curr_node)
{
	if(curr_node==NULL)
	{
		return;
	}
	if(curr_node->balance_factor>1)
	{
		if(curr_node->left_child->balance_factor > 0)
		{
			struct node * temp_curr = curr_node->left_child;
			left_left_rotation(curr_node->left_child);
			if(temp_curr->left_child!=NULL)
			{
				update_height(temp_curr->left_child);
				update_balance_factor(temp_curr->left_child);
			}
			if(temp_curr->right_child!=NULL)
			{
				update_height(temp_curr->right_child);
				update_balance_factor(temp_curr->right_child);
			}
			update_height(temp_curr);
			update_balance_factor(temp_curr);
		}
		else if(curr_node->left_child->balance_factor<0)
		{
			left_right_rotation(curr_node->left_child->right_child);
			struct node * temp_curr = curr_node->left_child;
			left_left_rotation(curr_node->left_child);
			if(temp_curr->left_child!=NULL)
			{
				update_height(temp_curr->left_child);
				update_balance_factor(temp_curr->left_child);
			}
			if(temp_curr->right_child!=NULL)
			{
				update_height(temp_curr->right_child);
				update_balance_factor(temp_curr->right_child);
			}
			update_height(temp_curr);
			update_balance_factor(temp_curr);
		}
	}
	else if(curr_node->balance_factor<-1)
	{
		if(curr_node->right_child->balance_factor < 0)
		{
			struct node * temp_curr = curr_node->right_child;
			right_right_rotation(curr_node->right_child);
			if(temp_curr->left_child!=NULL)
			{
				update_height(temp_curr->left_child);
				update_balance_factor(temp_curr->left_child);
			}
			if(temp_curr->right_child!=NULL)
			{
				update_height(temp_curr->right_child);
				update_balance_factor(temp_curr->right_child);
			}
			update_height(temp_curr);
			update_balance_factor(temp_curr);
		}
		else if(curr_node->right_child->balance_factor>0)
		{
			right_left_rotation(curr_node->right_child->left_child);
			struct node * temp_curr = curr_node->right_child;
			right_right_rotation(curr_node->right_child);
			if(temp_curr->left_child!=NULL)
			{
				update_height(temp_curr->left_child);
				update_balance_factor(temp_curr->left_child);
			}
			if(temp_curr->right_child!=NULL)
			{
				update_height(temp_curr->right_child);
				update_balance_factor(temp_curr->right_child);
			}
			update_height(temp_curr);
			update_balance_factor(temp_curr);
		}
	}
}

struct node * find_predecessor(struct node * curr_node)
{
	if(curr_node==NULL)
	{
		return NULL;
	}
	if(curr_node->left_child == NULL)
	{
		return curr_node;
	}
	struct node * temp = curr_node->left_child;
	while(temp->right_child!=NULL)
	{
		temp = temp->right_child;
	}
	return temp;
}

int insert_node(struct node * curr_node, struct node * new_node)
{
	int status;
	if(root==NULL)
	{
		root = new_node;
		return 1;
	}
	if((new_node->value) == (curr_node->value))
	{
		return 0;
	}
	if((new_node->value) < (curr_node->value))
	{
		if(curr_node->left_child==NULL)
		{
			curr_node->left_child = new_node;
			new_node->parent = curr_node;
			update_height(curr_node);
			update_balance_factor(curr_node);
			return 1;
		}
		else
		{
			status = insert_node((curr_node->left_child) , new_node);
			if(status)
			{
				update_height(curr_node);
				update_balance_factor(curr_node);
				check_and_balance_tree(curr_node);
			}
		}
	}
	else if((new_node->value) > (curr_node->value))
	{
		if(curr_node->right_child==NULL)
		{
			curr_node->right_child = new_node;
			new_node->parent = curr_node;
			update_height(curr_node);
			update_balance_factor(curr_node);
			return 1;
		}
		else
		{
			status =  insert_node((curr_node->right_child), new_node);
			if(status)
			{
				update_height(curr_node);
				update_balance_factor(curr_node);
				check_and_balance_tree(curr_node);
			}
		}
	}
	return status;
}

int insert(int new_val)
{
	return insert_node(root,create_node(new_val));
}

struct node * find_node(struct node * curr_node, int target)
{
	struct node * dest = NULL;
	if(root==NULL)
	{
		return NULL;
	}
	if((curr_node->value) == target)
	{
		return curr_node;
	}
	else if(((curr_node->value) > target) && curr_node->left_child!=NULL)
	{
		dest = find_node(curr_node->left_child, target);
	}
	else if(((curr_node->value)<target) && curr_node->right_child!=NULL)
	{
		dest = find_node(curr_node->right_child, target);
	}
	return dest;
}

struct node * find(int target)
{
	return find_node(root,target);
}

int remove(int val)
{
	struct node * curr_node = find(val);
	if(curr_node==NULL)
	{
		return 0;
	}
	if(curr_node->left_child==NULL)
	{
		if(curr_node==root)
		{
			root = curr_node->right_child;
			if(curr_node->right_child!=NULL)
			{
				curr_node->right_child->parent = NULL;
			}
		}
		else
		{
			if(curr_node->parent->left_child == curr_node)
			{
				curr_node->parent->left_child = curr_node->right_child;
			}	
			else if(curr_node->parent->right_child == curr_node)
			{
				curr_node->parent->right_child = curr_node->right_child;
			}	
			if(curr_node->right_child!=NULL)
			{
				curr_node->right_child->parent = curr_node->parent;
			}		
		}
		curr_node = curr_node->parent;
	}
	else
	{
		struct node * pred = find_predecessor(curr_node);
		if(pred->value == 3)
		{
				int x;
		}
		curr_node->value = pred->value;
		
		if(pred->parent == root)
		{
			root = pred->left_child;
			if(pred->left_child!=NULL)
			{
				pred->left_child->parent = NULL;
			}
		}
		else
		{
			if(pred->parent->left_child == pred)
			{
				pred->parent->left_child = pred->left_child;
			}
			else if(pred->parent->right_child == pred)
			{
				pred->parent->right_child = pred->left_child;
			}
			if(pred->left_child!=NULL)
			{
				pred->left_child->parent = pred->parent;
			}
		}
		curr_node = pred->parent;
	}
	
	while(curr_node!=NULL)
	{
		update_height(curr_node);
		update_balance_factor(curr_node);
		check_and_balance_tree(curr_node);
		curr_node = curr_node->parent;
	}
	return 1;
}

struct k_struct find_kth_smallest(struct node * curr_node, struct k_struct ks)
{
	if(curr_node==NULL)
	{
		return ks;
	}
	ks = find_kth_smallest(curr_node->left_child, ks);
	int set = 0;
	if(ks.k>0)
	{
		ks.k--;
		if(ks.k==0)
		{
			set = 1;
		}
	}
	if(set)
	{
		ks.kse = curr_node->value;
	}
	ks = find_kth_smallest(curr_node->right_child, ks);
	return ks;
}

int find_kth_smallest(int k)
{
	struct k_struct ks;
	ks.k = k;
	ks.kse = 0;
	ks = find_kth_smallest(root,ks);
	return ks.kse;
}

void print_tree()
{
	if(root==NULL)
	{
		cout<<"\nTree is empty\n";
		return;
	}
	queue<struct node *> bfsq;
	bfsq.push(root);
	while(!bfsq.empty())
	{
		struct node * curr_node = bfsq.front();
		bfsq.pop();
		int p;
		if(curr_node->parent==NULL)
		{
			p=-1;
		}
		else
		{
			p = curr_node->parent->value;
		}
		cout<<"("<<curr_node->value<<"  "<<curr_node->height<<"  "<<curr_node->balance_factor<<"  "<<p<<")";
		if(curr_node->left_child!=NULL)
		{
			bfsq.push((curr_node->left_child));
		}
		if(curr_node->right_child!=NULL)
		{
			bfsq.push((curr_node->right_child));
		}
	}
	cout<<"\n";
}

int main()
{
	insert(30);
	insert(15);
	insert(40);
	insert(10);
	insert(25);
	insert(35);
	insert(50);
	insert(5);
	cout<<find_kth_smallest(4);
	cout<<"\n";
	return 0;
}
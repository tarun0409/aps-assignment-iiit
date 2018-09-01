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
	curr_node->parent->parent->right_child = curr_node;
	struct node * temp2 = curr_node->parent;
	curr_node->parent = curr_node->parent->parent;
	temp2->parent  = curr_node;
}

void check_and_balance_tree(struct node * curr_node)
{
	if(curr_node->balance_factor>1)
	{
		if(curr_node->left_child->balance_factor > 0)
		{
			cout<<endl<<"Left-Left-Imbalance"<<endl;
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
			cout<<endl<<"Left-Right-Imbalance"<<endl;
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
			cout<<endl<<"Right-Right-Imbalance"<<endl;
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
			cout<<endl<<"Right-Left-Imbalance"<<endl;
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

void print_tree()
{
	if(root==NULL)
	{
		return;
	}
	queue<struct node *> bfsq;
	bfsq.push(root);
	while(!bfsq.empty())
	{
		struct node * curr_node = bfsq.front();
		bfsq.pop();
		cout<<"("<<curr_node->value<<"  "<<curr_node->height<<"  "<<curr_node->balance_factor<<")";
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
	//insert_node(root, create_node(4));
	//insert_node(root, create_node(3));
	//insert_node(root, create_node(2));
	//insert_node(root, create_node(8));
	//insert_node(root, create_node(9));
	//insert_node(root, create_node(5));
	
	insert_node(root, create_node(22));
	insert_node(root, create_node(14));
	insert_node(root, create_node(28));
	insert_node(root, create_node(8));
	insert_node(root, create_node(19));
	insert_node(root, create_node(25));
	insert_node(root, create_node(31));
	insert_node(root, create_node(23));
	insert_node(root, create_node(27));
	insert_node(root, create_node(37));
	insert_node(root, create_node(26));
	insert_node(root, create_node(34));
	insert_node(root, create_node(40));
	insert_node(root, create_node(29));
	insert_node(root, create_node(33));
	insert_node(root, create_node(32));
	cout<<"\n";
	print_tree();
	return 0;
}
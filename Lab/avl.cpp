#include<iostream>
#include<fstream>
#include<iomanip>
#include<cstdlib>
#include<time.h>
using namespace std; 

struct Node 
{  
	int key; 
	struct Node *left; 
	struct Node *right; 
	int height; 
}; 

int max(int a, int b); 

int height(struct Node *N) 
{ 
	if (N == NULL) 
		return 0; 
	return N->height; 
} 

int max(int a, int b) 
{ 
	return (a > b)? a : b; 
} 

struct Node* newNode(int key) 
{ 
	struct Node* node = (struct Node*)malloc(sizeof(struct Node)); 
	node->key = key; 
	node->left = NULL; 
	node->right = NULL; 
	node->height = 1;
	return(node); 
} 
 
struct Node *rightRotate(struct Node *y) 
{ 
	struct Node *x = y->left; 
	struct Node *T2 = x->right; 

	x->right = y; 
	y->left = T2; 

	y->height = max(height(y->left), 
					height(y->right)) + 1; 
	x->height = max(height(x->left), 
					height(x->right)) + 1; 

	return x; 
} 

struct Node *leftRotate(struct Node *x) 
{ 
	struct Node *y = x->right; 
	struct Node *T2 = y->left; 

	y->left = x; 
	x->right = T2; 
 
	x->height = max(height(x->left),	 
					height(x->right)) + 1; 
	y->height = max(height(y->left), 
					height(y->right)) + 1; 

	return y; 
} 

int getDiff(struct Node *N) 
{ 
	if (N == NULL) 
		return 0; 
	return height(N->left) - height(N->right); 
} 
 
struct Node* insert(struct Node* node, int key) 
{ 
	if (node == NULL) 
		return(newNode(key)); 

	if (key < node->key) 
		node->left = insert(node->left, key); 
	else if (key > node->key) 
		node->right = insert(node->right, key); 
	else
		return node; 

	node->height = 1 + max(height(node->left), 
						height(node->right)); 

	int diff = getDiff(node); 

	if (diff > 1 && key < node->left->key) 
		return rightRotate(node); 

	if (diff < -1 && key > node->right->key) 
		return leftRotate(node); 
 
	if (diff > 1 && key > node->left->key) 
	{ 
		node->left = leftRotate(node->left); 
		return rightRotate(node); 
	} 
 
	if (diff < -1 && key < node->right->key) 
	{ 
		node->right = rightRotate(node->right); 
		return leftRotate(node); 
	} 

	return node; 
}

void postorder(Node* p, int indent=0)
{
    if(p != NULL)
    {
    	cout<< p->key << "\n ";
        if(p->left) postorder(p->left, indent+4);
        if(p->right) postorder(p->right, indent+4);
        if (indent) 
        {
            std::cout << std::setw(indent) << ' ';
    	}
    }
}

void inOrder(struct Node *root) 
{ 
	ofstream file;
	if(root != NULL) 
	{  
		inOrder(root->left); 
		file.open("output.txt",ios::app);
		file<< root->key << " ";
		file.close();
		inOrder(root->right); 
	} 
} 
void Level(struct Node* root, int level) 
{ 
	if (root == NULL) 
		return; 
	if (level == 1) 
		cout<<root->key<<" "; 
	else if (level > 1) 
	{ 
		Level(root->left, level-1); 
		Level(root->right, level-1); 
	} 
} 
/*
void print_tree(struct Node* root) 
{ 
	int h = height(root); 
	int i; 
	for (i=1; i<=h; i++) 
	{ 
		Level(root, i); 
		cout<<endl; 
	} 
} 
*/
int main() 
{ 
	struct Node *root = NULL;
	int n;
	srand(time(NULL));
	ofstream outfile;
	outfile.open("input.txt",ios::out);
	int range = rand()%50 + 51;
	for(int i=0;i<range;i++)
	{
		n = rand()%200+1;
		outfile<<n<<" ";
	}
	outfile.close();
	ifstream infile;
	infile.open("input.txt",ios::in);
	for(int i=0;i<range;i++)
	{
		infile>>n;
		root = insert(root, n);
	}
	infile.close();
	ofstream f;
	f.open("output.txt",ios::out);
	f.close();
	inOrder(root);
	cout << "\nThe AVL Tree is: \n"; 
	postorder(root);
	return 0; 
} 

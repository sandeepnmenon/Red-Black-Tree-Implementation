#include <stdlib.h>
#define BLACK 0
#define RED 1
#define DOUBLE_BLACK 2

class RBTNode
{
	
	public:
	bool color;
	
	int data;
	
	RBTNode* parent;
	RBTNode* left;
	RBTNode* right;
	
	RBTNode(int data)
	{
		this->data = data;
		parent = left = right = NULL;
	}
	
};

class RBT
{

	RBTNode* root;
	
	RBT(int data)
	{
		root = NULL;
	}
	RBTNode* getMinValueNode(RBTNode *subRoot)
	{
		RBTNode *current = subRoot;
		while(current->left != NULL)
			current = current->left;
	
		return current;

	}

	RBTNode* getInorderSuccessor(RBTNode *node)
	{
		if(node->right != NULL)
			return getMinValueNode(node->right);
	
		RBTNode *parentNode = node->parent;
		while( parentNode!=NULL and node==parentNode->right)
		{
			node=parentNode;
			parentNode=parentNode->parent;
		}
		return parentNode;

	}


	RBTNode* getGrandParent(RBTNode *node)
	{
		if( (node != NULL) and (node->parent != NULL) )
			return node->parent->parent;
		return NULL;

	}

	RBTNode* getUncle(RBTNode *node)
	{
		RBTNode *grandParent = getGrandParent(node);
	
		if(grandParent == NULL)
			return NULL;
		if(node->parent == grandParent->left)
			return grandParent->right;
		if(node->parent == grandParent->right)
			return grandParent->left;

	}

	void rotateLeft(RBTNode *&root, RBTNode *&node)
	{
		RBTNode *rightNode = node->right;
		
		node->right = rightNode->left;
		
		if(node->right != NULL)
			node->right->parent = node;
		
		nodeRight->parent = node->parent;
		
		if(node->parent ==NULL)
			root = nodeRight;
		else if(node == node->parent->left)
			node->parent->left= nodeRight;
		else
			node->parent->right = nodeRight;
			
		nodeRight->left = node;
		node->parent = nodeRight;
	}
	
	void rotateRight(RBTNode *&root, RBTNode *&node)
	{
		RBTNode *nodeLeft = node->left;
		node->left = nodeLeft->right;
		
		if(node->left != NULL)
			node->left->parent = node;
			
		nodeLeft->parent = node->parent;
		
		if(node->parent == NULL)
			root = nodeLeft;
		else if(node == node->parent->left)
			node->parent->left = nodeLeft;
		else
			node->parent->right = nodeLeft;
			
		nodeLeft->right = node;
		node->parent = nodeLeft;
	}
	
	void fixInsertViolation(RBTNode *&root, RBTNode *&node)
	{
		RBTNode *paretnNode = node->parent;
		RBTNode *grandParentNode = getGrandParent(node);
		
		//Case 1 : If node is root
		if(parentNode==NULL)
		{
			root->color = BLACK;
		}
		else
		{
			//Case 2: Parent is black
			if(parentNode->color == RED)
			{
				return ; //Valid tree
			}
			//Case 3 : Parent is Red
			else
			{
			
			}
		
		}
		
	}
	
	void insertNode(RBTNode *root, int data)
	{
		RBTNode newNode = new RBTNode(data);
		
		this->root = BSTInsert(this->root,newNode);
		
		fixInsertViolation(this->root, newNode);
		

	}

};

RBTNode* BSTInsert(RBTNode *root, RBTNode *node)
	{
		if(root ==NULL)
			return node;
		if(root->data > node->data)
		{
			root->left = BSTInsert(root->left,node);
			root->left->parent = root;
		}
		else if(root->data < node->data)
		{
			root->right = BSTInsert(root->right,node);
			root->right->parent =root;
		}
	
		return root;

	}

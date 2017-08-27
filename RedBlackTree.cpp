#include <bits/stdc++.h>
#define BLACK 0
#define RED 1
#define DOUBLE_BLACK 2
#define newline cout<<endl;
using namespace std;


class RBTNode
{
	
	public:
	int color;
	
	int data;
	
	RBTNode* parent;
	RBTNode* left;
	RBTNode* right;
	
	RBTNode(int data)
	{
		this->data = data;
		parent = left = right = NULL;
		color = RED;
	}
	
};
void inorderTraversal(RBTNode *root)
{
	if(root != NULL)
	{
		inorderTraversal(root->left);
		cout<<root->data<<" ";
		inorderTraversal(root->right);	
	}
}

void preorderTraversal(RBTNode *root)
{
	if(root != NULL)
	{
		cout<<root->data<<" ";
		preorderTraversal(root->left);
		preorderTraversal(root->right);	
	}
}
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

class RedBlackTree
{

	
	
	public:
	
	RBTNode* root;
	
	RedBlackTree(int data)
	{
		root = new RBTNode(data);
		root->color = BLACK;
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

	void rotateLeft(RBTNode *node)
	{
		RBTNode *rightNode = node->right;
		RBTNode *nodeParent = node->parent;
		node->right = rightNode->left;
		
		if(node->right != NULL)
			node->right->parent = node;
		
		rightNode->parent = nodeParent;
		
		if(node->parent ==NULL)
			this->root = rightNode;
		else if(node == node->parent->left)
			node->parent->left= rightNode;
		else
			node->parent->right = rightNode;
			
		rightNode->left = node;
		node->parent = rightNode;
	}
	
	void rotateRight(RBTNode *node)
	{
		RBTNode *nodeLeft = node->left;
		node->left = nodeLeft->right;
		
		if(node->left != NULL)
			node->left->parent = node;
		
		
		nodeLeft->parent = node->parent;
		
		if(node->parent == NULL)
			this->root = nodeLeft;
		else if(node == node->parent->left)
			node->parent->left = nodeLeft;
		else
			node->parent->right = nodeLeft;
			
		nodeLeft->right = node;
		node->parent = nodeLeft;

		//cout<<root->data<<" "<<root->right->data<<endl;
	}
	
	
	void fixInsertViolation(RBTNode *&node)
	{
		if(node->parent == NULL)
			node->color = BLACK;
		else
			fixParentNode(node);
	}
	void fixParentNode(RBTNode *&node)
	{
		if(node->parent->color == BLACK)
			return ;
		else
			fixRedUncleNode(node);	
	}
	
	void fixRedUncleNode(RBTNode *&node)
	{
		RBTNode *uncle = getUncle(node);
		
		if( (uncle != NULL) and (uncle->color == RED) )
		{
			node->parent->color = BLACK;
			uncle->color = BLACK;
			RBTNode *grandParent = getGrandParent(node);
			grandParent->color = RED;
			fixInsertViolation(grandParent);
		}
		else
			fixBlackUncleNode(node);
	}
	
	void fixBlackUncleNode(RBTNode *&node)
	{
		RBTNode *grandParent = getGrandParent(node);
		
		if(grandParent == NULL)
			return ;

		if( (node == node->parent->right) and (node->parent == grandParent->left) )
		{
			rotateLeft(node->parent);
			node = node->left;
		}
		else if( (node == node->parent->left) and (node->parent == grandParent->right) )
		{	
			
			rotateRight( node->parent);
			
			node = node->right;
		}
		else
		{
			node->parent->color = BLACK;
			grandParent->color = RED;
			
			if(node == node->parent->left)
				rotateRight( grandParent);
			else
				rotateLeft( grandParent);
		}
		
	}
	
	
	void insertNode(int data)
	{
		RBTNode *newNode = new RBTNode(data);
		
		this->root = BSTInsert(this->root,newNode);
		
		fixInsertViolation(newNode);
		
	}

};



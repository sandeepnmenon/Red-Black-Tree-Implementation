#include <iostream>
#include <stdlib.h>
#include <algorithm>
#define BLACK 0
#define RED 1
#define DOUBLE_BLACK 2
#define newline cout<<endl;
using namespace std;

//Red Black Tree Node
class RBTNode
{
	
	int color;	
	int data;
	
	public:
	RBTNode* parent;
	RBTNode* left;
	RBTNode* right;
	
	RBTNode(int data)
	{
		this->data = data;
		parent = left = right = NULL;
		color = RED;
	}

	void setColor(int color)
	{
		this->color = color;
	}

	int getColor()
	{
		return this->color;
	}

	int getData()
	{
		return this->data;
	}

	void setData(int data)
	{
		this->data = data;
	}
	
};

//Insert node in a Binary Search Tree
RBTNode* BSTInsert(RBTNode *root, RBTNode *node)
	{
		if(root ==NULL)
			return node;
		if(root->getData() > node->getData())
		{
			root->left = BSTInsert(root->left,node);
			root->left->parent = root;
		}
		else if(root->getData() < node->getData())
		{
			root->right = BSTInsert(root->right,node);
			root->right->parent =root;
		}
	
		return root;

	}

//Red Black Tree class
class RedBlackTree
{

	RBTNode* root;
	
	public:
	RedBlackTree(int data)
	{
		root = new RBTNode(data);
		root->setColor(BLACK);
	}

	RBTNode* getRoot()
	{
		return root;
	}

	//Swapping colors of two nodes
	void swapNodeColor(RBTNode *nodeA, RBTNode *nodeB)
	{
		int tempColor = nodeA->getColor();
		nodeA->setColor(nodeB->getColor());
		nodeB->setColor(tempColor);

	}

	RBTNode* getMinValueNode(RBTNode *subRoot)
	{
		RBTNode *current = subRoot;
		while(current->left != NULL)
			current = current->left;
	
		return current;

	}


	int getBlackHeight(RBTNode *root)
	{
		if(root==NULL)
			return 0;
		if(root->getColor()== BLACK)
		{
			return 1+max(getBlackHeight(root->left),getBlackHeight(root->right));
		}
		else
			return max(getBlackHeight(root->left),getBlackHeight(root->right));
	}

	RBTNode* getMaxValueNode(RBTNode *root)
	{
		if(root==NULL)
			return NULL;
		else if (root->right==NULL)
			return root;
		else
			return getMaxValueNode(root->right);
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

	void rotateLeft(RBTNode *&node)
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
	
	void rotateRight(RBTNode *&node)
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
	
	//Fixes Red Black Tree propertied after inserting a node	
	void fixInsertViolation(RBTNode *&node)
	{

		RBTNode *parentNode = NULL;
	    RBTNode *grandParentNode = NULL;
	 
	 	//If node is root then color node to black
	 	//If node is red it's parent should not be red
	    while ((node != root) and (node->getColor() != BLACK) and (node->parent->getColor() == RED))
	    {
	 
	        parentNode = node->parent;
	        grandParentNode = getGrandParent(node);
	 
	        /*  Case : A
	            Parent of node is left child of Grand-parent of node */
	        if (parentNode == grandParentNode->left)
	        {
	 
	            RBTNode *uncleNode = grandParentNode->right;
	 
	            /* Case : 1
	               The uncle of node is also red
	               Only Recoloring required */
	            if (uncleNode != NULL and uncleNode->getColor() == RED)
	            {
	                grandParentNode->setColor(RED);
	                parentNode->setColor(BLACK);
	                uncleNode->setColor(BLACK);
	                node = grandParentNode;
	            }
	 
	            else
	            {
	                /* Case : 2
	                   node is right child of its parent
	                   Left-rotation required */
	                if (node == parentNode->right)
	                {
	                    rotateLeft(parentNode);
	
	                    node = parentNode;
	                    parentNode = node->parent;
	                }
	 
	                /* Case : 3
	                   node is left child of its parent
	                   Right-rotation required */
	                rotateRight(grandParentNode);
	                swapNodeColor(parentNode, grandParentNode);
	                node = parentNode;
	            }
	        }
	 
	        /* Case : B
	           Parent of node is right child of Grand-parent of node */
	        else
	        {
	            RBTNode *uncleNode = grandParentNode->left;
	 
	            /*  Case : 1
	                The uncle of node is also red
	                Only Recoloring required */
	            if ((uncleNode != NULL) && (uncleNode->getColor() == RED))
	            {
	                grandParentNode->setColor(RED);
	                parentNode->setColor(BLACK);
	                uncleNode->setColor(BLACK);
	                node = grandParentNode;
	            }
	            else
	            {
	                /* Case : 2
	                   node is left child of its parent
	                   Right-rotation required */
	                if (node == parentNode->left)
	                {
	                    rotateRight(parentNode);
	                    node = parentNode;
	                    parentNode = node->parent;
	                }
	 
	                /* Case : 3
	                   node is right child of its parent
	                   Left-rotation required */
	                rotateLeft(grandParentNode);
	                swapNodeColor(parentNode, grandParentNode);
	                node = parentNode;
	            }
	        }
	    }
	 
	    root->setColor(BLACK);
	}
	
	void insertNode(int data)
	{
		RBTNode *newNode = new RBTNode(data);
		
		this->root = BSTInsert(this->root,newNode);

		fixInsertViolation(newNode);
		
	}

	void inorderTraversal(RBTNode *root)
	{
		if(root != NULL)
		{
			inorderTraversal(root->left);
			cout<<root->getData()<<" ";
			inorderTraversal(root->right);	
		}
	}


	void preorderTraversal(RBTNode *root)
	{
		if(root != NULL)
		{
			cout<<root->getData()<<" ";
			preorderTraversal(root->left);
			preorderTraversal(root->right);	
		}
	}

};



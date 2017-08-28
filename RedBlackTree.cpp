#include <iostream>
#include <stdlib.h>
#include <algorithm>
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
		RBTNode *grandParentNode = getGrandParent(node);

		if(grandParentNode == NULL)
			return ;

		if( (node == node->parent->right) and (node->parent == grandParentNode->left) )
		{
			rotateLeft(node->parent);
			node = node->left;
		}
		else if( (node == node->parent->left) and (node->parent == grandParentNode->right) )
		{	
			
			rotateRight( node->parent);
			node = node->right;
		}
		else
		{
			node->parent->color = BLACK;
			grandParentNode->color = RED;
			
			if(node == node->parent->left)
				rotateRight( grandParentNode);
			else
				rotateLeft( grandParentNode);
		}
		
	}
	
	void fixInsertViolation(RBTNode *&root, RBTNode *&pt)
	{

		RBTNode *parent_pt = NULL;
	    RBTNode *grand_parent_pt = NULL;
	 
	    while ((pt != root) && (pt->color != BLACK) &&
	           (pt->parent->color == RED))
	    {
	 
	        parent_pt = pt->parent;
	        grand_parent_pt = pt->parent->parent;
	 
	        /*  Case : A
	            Parent of pt is left child of Grand-parent of pt */
	        if (parent_pt == grand_parent_pt->left)
	        {
	 
	            RBTNode *uncle_pt = grand_parent_pt->right;
	 
	            /* Case : 1
	               The uncle of pt is also red
	               Only Recoloring required */
	            if (uncle_pt != NULL && uncle_pt->color == RED)
	            {
	                grand_parent_pt->color = RED;
	                parent_pt->color = BLACK;
	                uncle_pt->color = BLACK;
	                pt = grand_parent_pt;
	            }
	 
	            else
	            {
	                /* Case : 2
	                   pt is right child of its parent
	                   Left-rotation required */
	                if (pt == parent_pt->right)
	                {
	                    rotateLeft(parent_pt);
	                    pt = parent_pt;
	                    parent_pt = pt->parent;
	                }
	 
	                /* Case : 3
	                   pt is left child of its parent
	                   Right-rotation required */
	                rotateRight(grand_parent_pt);
	                swap(parent_pt->color, grand_parent_pt->color);
	                pt = parent_pt;
	            }
	        }
	 
	        /* Case : B
	           Parent of pt is right child of Grand-parent of pt */
	        else
	        {
	            RBTNode *uncle_pt = grand_parent_pt->left;
	 
	            /*  Case : 1
	                The uncle of pt is also red
	                Only Recoloring required */
	            if ((uncle_pt != NULL) && (uncle_pt->color == RED))
	            {
	                grand_parent_pt->color = RED;
	                parent_pt->color = BLACK;
	                uncle_pt->color = BLACK;
	                pt = grand_parent_pt;
	            }
	            else
	            {
	                /* Case : 2
	                   pt is left child of its parent
	                   Right-rotation required */
	                if (pt == parent_pt->left)
	                {
	                    rotateRight(parent_pt);
	                    pt = parent_pt;
	                    parent_pt = pt->parent;
	                }
	 
	                /* Case : 3
	                   pt is right child of its parent
	                   Left-rotation required */
	                rotateLeft(grand_parent_pt);
	                swap(parent_pt->color, grand_parent_pt->color);
	                pt = parent_pt;
	            }
	        }
	    }
	 
	    root->color = BLACK;
	}
	
	void insertNode(int data)
	{
		RBTNode *newNode = new RBTNode(data);
		
		this->root = BSTInsert(this->root,newNode);

		fixInsertViolation(this->root,newNode);
		
	}

	int blackheight(RBTNode *root)
	{
		if(root==NULL)
			return 0;
		if(root->color== BLACK)
		{
			return 1+max(blackheight(root->left),blackheight(root->right));
		}
		else
			return max(blackheight(root->left),blackheight(root->right));
	}

	RBTNode* greatestElememt(RBTNode *root)
	{
		if(root==NULL)
			return NULL;
		else if (root->right==NULL)
			return root;
		else
			return greatestElememt(root->right);
	}

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

};



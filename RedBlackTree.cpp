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

	RBTNode (int data,int color)
	{
		this->data = data;
		this->color = color;
		parent = left = right = NULL;
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

	RedBlackTree()
	{

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
		if(root==NULL ||root->getData()==-1)
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

	RBTNode* getNodeToDeletePosition(RBTNode *root,int key)
	{
		if(root == NULL)
			return root;
		//If key is in left subtree
		if(key < root->getData())
			return getNodeToDeletePosition(root->left,key);
		//If key is in right subtree
		else if (key > root->getData())
			return getNodeToDeletePosition(root->right,key);

		//Key is at root
		if(root->left == NULL or root->right == NULL)
			return root;
		
		RBTNode *temp = getMaxValueNode(root->left);
		root->setData(temp->getData());
		return getNodeToDeletePosition(root->left,temp->getData());
	}

	void fixDeleteViolation(RBTNode *node)
	{
		if (node == NULL)
	        return;

	    if (node == root) 
	    {
	        root = NULL;
	        return;
	    }

	    //If one of node or it's child is red
	    if (node->getColor() == RED || node->left->getColor() == RED || node->right->getColor() == RED) 
	    {
	        RBTNode *child = node->left != NULL ? node->left : node->right;

	        //if node is left child
	        if (node == node->parent->left) 
	        {
	            node->parent->left = child;
	            if (child != NULL)
	            {	
	            	child->parent = node->parent;
	            	child->setColor(BLACK);
	            }
	            delete (node);
	        } 
	        //if node is right child
	        else 
	        {
	            node->parent->right = child;
	            if (child != NULL)
	            {   
	            	child->parent = node->parent;
	            	child->setColor(BLACK);
	        	}	
	            delete (node);
	        }
	    }
	    //if both node and it's child is black 
	    else 
	    {
	        RBTNode *sibling = NULL;
	        RBTNode *parent = NULL;
	        RBTNode *ptr = node;
	        ptr->setColor(DOUBLE_BLACK);
	        while (ptr != root and ptr->getColor() == DOUBLE_BLACK) 
	        {
	            parent = ptr->parent;
	            //If ptr is left child
	            if (ptr == parent->left) 
	            {
	                sibling = parent->right;

		                if(!sibling->right)
						{
							sibling->right = new RBTNode(-1,BLACK);
							sibling->right->parent = sibling;
						}
						if(!sibling->left)
						{
							sibling->left = new RBTNode(-1,BLACK);
							sibling->left->parent = sibling;
						}
	                //If sibling is red
	                //Make sibling black
	                //Make parent red
	                //Rotate parent left
	                if (sibling->getColor() == RED) 
	                {
	                    sibling->setColor(BLACK);
	                    parent->setColor(RED);
	                    //cout<<root->getData();
	                    rotateLeft(parent);

	                } 
	                //If sibling is black
	                else 
	                {
	                	//If both children of sibling are black
	                	//Make sibling red
	                	//If parent is red, make it black
	                	//If parent is black,make it double black
	                    if (sibling->left->getColor() == BLACK and sibling->right->getColor() == BLACK) 
	                    {
	                        sibling->setColor(RED);
	                        if(parent->getColor() == RED)
	                            parent->setColor(BLACK);
	                        else
	                            parent->setColor( DOUBLE_BLACK);
	                        ptr = parent;
	                    } 
	                    else 
	                    {
	                        if (sibling->right->getColor() == BLACK) {
	                            sibling->left->setColor( BLACK);
	                            sibling->setColor( RED);
	                            rotateRight(sibling);
	                            sibling = parent->right;
	                        }
	                        sibling->setColor( parent->getColor());
	                        parent->setColor( BLACK);
	                        sibling->right->setColor( BLACK);
	                        rotateLeft(parent);
	                        break;
	                    }
	                }
	            } 
	            else 
	            {
	                sibling = parent->left;
	                if(!sibling->right)
						{
							sibling->right = new RBTNode(-1,BLACK);
							sibling->right->parent = sibling;
						}
						if(!sibling->left)
						{
							sibling->left = new RBTNode(-1,BLACK);
							sibling->left->parent = sibling;
						}
	                if (sibling->getColor() == RED) {
	                    sibling->setColor( BLACK);
	                    parent->setColor( RED);
	                    rotateRight(parent);
	                } else {
	                    if (sibling->left->getColor() == BLACK and sibling->right->getColor() == BLACK) {
	                        sibling->setColor( RED);
	                        if (parent->getColor() == RED)
	                            parent->setColor( BLACK);
	                        else
	                            parent->setColor( DOUBLE_BLACK);
	                        ptr = parent;
	                    } else {
	                        if (sibling->left->getColor() == BLACK) {
	                            sibling->right->setColor( BLACK);
	                            sibling->setColor( RED);
	                            rotateLeft(sibling);
	                            sibling = parent->left;
	                        }
	                        sibling->setColor( parent->getColor());
	                        parent->setColor( BLACK);
	                        sibling->left->setColor( BLACK);
	                        rotateRight(parent);
	                        break;
	                    }
	                }
	            }
	        }
	        if (node == node->parent->left)
	            node->parent->left = NULL;
	        else
	            node->parent->right = NULL;
	        delete(node);
	        root->setColor( BLACK);
	    }

	}
	void deleteNode(int data)
	{
		RBTNode *nodeToDelete = getNodeToDeletePosition(this->root,data);
		if(!nodeToDelete->right)
		{
			nodeToDelete->right = new RBTNode(-1,BLACK);
			nodeToDelete->right->parent = nodeToDelete;
		}
		if(!nodeToDelete->left)
		{
			nodeToDelete->left = new RBTNode(-1,BLACK);
			nodeToDelete->left->parent = nodeToDelete;
		}
		fixDeleteViolation(nodeToDelete);
	}

	void inorderTraversal(RBTNode *root)
	{
		if(root != NULL and root->getData()!=-1)
		{
			inorderTraversal(root->left);
			cout<<root->getData()<<" ";
			inorderTraversal(root->right);	
		}
	}


	void preorderTraversal(RBTNode *root)
	{
		if(root != NULL and root->getData()!=-1)
		{
			cout<<root->getData()<<" ";
			preorderTraversal(root->left);
			preorderTraversal(root->right);	
		}
	}


	RBTNode* findNodewithBlackHeightLeft(RBTNode *node,int p)
	{
		if(getBlackHeight(node)==p)
		{
			return node;
		}
		else 
			return findNodewithBlackHeightLeft(node->left,p);
	}

	RBTNode* findNodewithBlackHeightRight(RBTNode *node,int p)
	{
		if(getBlackHeight(node)==p)
		{
			return node;
		}
		else 
			return findNodewithBlackHeightRight	(node->right,p);
	}
	

};



#include "RedBlackTree.cpp"
#include <bits/stdc++.h>
using namespace std;

RedBlackTree* createRedBlackTree(int nodeValues[],int n)
{
	RedBlackTree *rbt = new RedBlackTree();

	for(int i=0 ; i < n; ++i)
	{
		rbt->insertNode(nodeValues[i]);
	}

	return rbt;
}

void printTreeTraversals(RedBlackTree *rbt,int index)
{
	cout<<"Inorder Traversal of RBT "<<index;
	newline
	rbt->inorderTraversal(rbt->getRoot());
	newline
	cout<<"Preorder Traversal of RBT "<<index;
	newline
	rbt->preorderTraversal(rbt->getRoot());
	newline
}
int main()
{
	int nodesToInsert[]={1,2,3};
	int nodesToDelete[]={6,4,3,5,2};
	
	RedBlackTree *rbt1 = createRedBlackTree(nodesToInsert,sizeof(nodesToInsert)/sizeof(int));

	printTreeTraversals(rbt1,1);

	int nodesToInsert2[]={4,5,6,7,8,9};
	RedBlackTree *rbt2 = createRedBlackTree(nodesToInsert2,sizeof(nodesToInsert2)/sizeof(int));

	printTreeTraversals(rbt2,3);

	merge(rbt1,rbt2);
	printTreeTraversals(rbt2,4);
}

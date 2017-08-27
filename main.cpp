#include "RedBlackTree.cpp"
#include <bits/stdc++.h>
using namespace std;

int main()
{
	int nodesToInsert[]={6,4,3,5,2};
	int nodesToDelete[]={6,4,3,5,2};
	
	RedBlackTree *rbt = new RedBlackTree(1);
	for(int i=0 ; i<sizeof(nodesToInsert)/sizeof(int); ++i)
		rbt->insertNode(nodesToInsert[i]);

	RBTNode *root = rbt->root;

	inorderTraversal(root);

}

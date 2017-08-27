#include "RedBlackTree.cpp"
#include <bits/stdc++.h>
using namespace std;

int main()
{
	int insertNodes[]={1,4,3,5,2};
	int deleteNodes[]={1,4,3,5,2};
	
	RedBlackTree *rbt = new RedBlackTree(1);
	
	RBTNode *root = rbt->root;

	inorderTraversal(root);

}

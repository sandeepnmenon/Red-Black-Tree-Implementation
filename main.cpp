#include "RedBlackTree.cpp"
#include <bits/stdc++.h>
using namespace std;

void inorderTraversal(RBTNode *root)
{
	inorderTraversal(root->left);
	cout<<root->data<<" ";
	inorderTraversal(root->right);	

}
int main()
{
	int insertNodes[]={1,2,3,4,5};
	int deleteNodes[]={1,2,3,4,5};
	



}

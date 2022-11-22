#include<iostream>

struct BstNode {
	int data;
	BstNode* left;
	BstNode* right;
};

BstNode* GetNewNode(int data) {
	BstNode* newNode = new BstNode();
	newNode->data = data;
	newNode->left = newNode->right = NULL; //intialise left and right to NULL
	return newNode;
}

BstNode* Insert(BstNode* root, int data) {
	if (root == NULL) {
		root = GetNewNode(data);
		return root;
	}
	else if (data <= root->data) {
		root->left = Insert(root->left, data);
	}
	else {
		root->right = Insert(root->right, data);
	}
	return root;
}

bool Search(BstNode* root, int data) {
	if (root == NULL) return false;
	else if (root->data == data) return true;
	else if (data <= root->data) return Search(root->left, data);
	else return Search(root->right, data);
}

int FindMin(BstNode* root)
{
	if (root == NULL) {
		std::cout << "[ERROR] Tree is empty." << std::endl;
		return -1;
	}
	while (root->left != NULL)
	{
		root = root->left;
	}
	return root->data;
}

int FindMax(BstNode* root)
{
	if (root == NULL) {
		std::cout << "[ERROR] Tree is empty." << std::endl;
		return -1;
	}
	else if (root->right == NULL) {
		return root->data;
	}
	return FindMax(root->right);
}
//Number of edges of longest route from leaf to root
int FindHeight(BstNode* root)
{
	if (root == NULL) return -1;
	int leftHeight = FindHeight(root->left);
	int rightHeight= FindHeight(root->right);
	return leftHeight > rightHeight ? leftHeight+1 : rightHeight+1;
}

int main()
{
	BstNode* root = NULL; //pointer to root node
	root = Insert(root, 15);
	root = Insert(root, 10);
	root = Insert(root, 20);
	root = Insert(root, 25);
	root = Insert(root, 8);
	root = Insert(root, 12);
	root = Insert(root, 34);

	int number;
	std::cout << "Enter a number: ";
	std::cin >> number;
	if (Search(root, number) == true) {
		std::cout << "Found!\n";
	}
	else std::cout << "Not Found\n";

	int max = FindMax(root);
	int min = FindMin(root);

	std::cout << "The maximum number in the tree is " << max << std::endl;
	std::cout << "The minimum number in the tree is " << min << std::endl;

	std::cout << "The height of the tree is " << FindHeight(root) << std::endl;
}
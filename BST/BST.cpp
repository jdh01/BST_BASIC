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

BstNode* FindMinPtr(BstNode* root)
{
	if (root == NULL) {
		std::cout << "[ERROR] Tree is empty." << std::endl;
		return root;
	}
	while (root->left != NULL)
	{
		root = root->left;
	}
	return root;
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

bool IsBinarySearchTree(BstNode* root)
{
	if (root == NULL) return true;

	/* false if the max of the left is > than us */
	if (root->left != NULL && FindMin(root->left) > root->data)
		return 0;

	/* false if the min of the right is <= than us */
	if (root->right != NULL && FindMin(root->right) < root->data)
		return 0;

	/* false if, recursively, the left or right is not a BST*/
	if (!IsBinarySearchTree(root->left) || !IsBinarySearchTree(root->right))
		return 0;

	/* passing all that, it's a BST */
	return 1;
}

BstNode* DeleteNode(BstNode* root, int data)
{
	if (root == NULL) return root;
	else if (data < root->data) root->left = DeleteNode(root->left, data);
	else if (data > root->data) root->right = DeleteNode(root->right, data);
	else
	{
		//Case 1 : No Child
		if (root->left == NULL && root->right == NULL) {
			delete root;
			root = NULL;
		}
		//Case 2 : One Child
		else if (root->left == NULL) {
			BstNode* temp = root;
			root = root->right;
			delete temp;
		}
		else if (root->right == NULL) {
			BstNode* temp = root;
			root = root->left;
			delete temp;
		}
		//Case 3 : 2 Children
		else {
			BstNode* temp = FindMinPtr(root->right);
			root->data = temp->data;
			root->right = DeleteNode(root->right, temp->data);
		}
		return root;
	}

}

int main()
{
	BstNode* root = NULL; //pointer to root node
	root = Insert(root, 7);
	root = Insert(root, 4);
	root = Insert(root, 9);
	/*
	root = Insert(root, 1);
	root = Insert(root, 6);*/

	int number;
	std::cout << "Enter a number: ";
	std::cin >> number;
	if (Search(root, number) == true) {
		std::cout << "Found!\n";
	}
	else std::cout << "Not Found\n";

	int maxValue = (FindMax(root));
	int minValue = (FindMin(root));

	std::cout << "The maximum number in the tree is " << maxValue << std::endl;
	std::cout << "The minimum number in the tree is " << minValue << std::endl;

	std::cout << "The height of the tree is " << FindHeight(root) << std::endl;

	if (IsBinarySearchTree(root))
	{
		std::cout << "This is a BST!" << std::endl;
	}
	else
	{
		std::cout << "This is NOT a BST!" << std::endl;
	}
	root = DeleteNode(root, 6);
}
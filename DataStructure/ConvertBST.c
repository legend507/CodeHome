/*
Given an array where elements are sorted in ascending order, convert it to a height balanced BST.
*/
typedef struct bst_node{
	int data;
	bst_node* left;
	bst_node* right;
}bst_node;

bst_node* convertoBSTHelper(int arr[], int left, int right){
	if (left > right)
		return NULL;

	int mid = (left + right)>>2;

	bst_node* node = new bst_node();
	node->data = arr[mid];
	node->left = convertoBSTHelper(arr, left, mid-1);
	node->right = convertoBSTHelper(arr, mid+1, right);

	return node;
}

bst_node* sortedArrayConvertoBST(int arr[], int len){
	return convertoBSTHelper(arr, 0, len-1);
}

/*
 * convert sorted list to BST
*/
struct TNode* sortedListToBST(struct LNode *head)
{
    /*Count the number of nodes in Linked List */
    int n = countLNodes(head);
 
    /* Construct BST */
    return sortedListToBSTRecur(&head, n);
}
 
struct TNode* sortedListToBSTRecur(struct LNode **head_ref, int n)
{
    /* Base Case */
    if (n <= 0)
        return NULL;
 
    /* Recursively construct the left subtree */
    struct TNode *left = sortedListToBSTRecur(head_ref, n/2);
 
    /* Allocate memory for root, and link the above constructed left 
       subtree with root */
    struct TNode *root = newNode((*head_ref)->data);
    root->left = left;
 
    /* Change head pointer of Linked List for parent recursive calls */
    *head_ref = (*head_ref)->next;
 
    /* Recursively construct the right subtree and link it with root 
      The number of nodes in right subtree  is total nodes - nodes in 
      left subtree - 1 (for root) which is n-n/2-1*/
    root->right = sortedListToBSTRecur(head_ref, n-n/2-1);
 
    return root;
}

/*Write a function isBST(BinaryTree *node) to verify if a given binary tree is a Binary Search Tree (BST) or not.*/
bool isBstLessThan(bst_node* tree, int val){
	if (!tree)
		return true;
	return (tree->data < val &&
		isBstLessThan(tree->left, val)&&
		isBstLessThan(tree->right, val));
}

bool isBstGreaterThan(bst_node* tree, int val){
	if (!tree)
		return true;
	return (tree->data > val &&
		isBstGreaterThan(tree->left, val) &&
		isBstGreaterThan(tree->right, val));
}

bool isBstBruteForce(bst_node* tree){
	if (!tree)
		return true;

	return (isBstLessThan(tree->left, tree->data)&&
		isBstGreaterThan(tree->right, tree->data)&&
		isBstBruteForce(tree->left)&&
		isBstBruteForce(tree->right));
}

// more better solution
bool isBstHelper(bst_node* tree, int min, int max){
	if (!tree)
		return true;

	if (tree->data > min && tree->data < max)
		return (isBstHelper(tree->left, min, tree->data)&&
		isBstHelper(tree->right, tree->data, max));
	else
		return false;
}

bool isBst(bst_node* tree){
	if (!tree)
		return true;

	return isBstHelper(tree, INT_MIN, INT_MAX);
}

// the third solution
bool isBstInorderHelper(bst_node* tree, int& prev){
	if (!tree)
		return true;

	// bug version
	//return (isBstInorderHelper(tree->left, prev)&&
	//	(tree->data > prev)&&(prev = tree->data)&&
	//	isBstInorderHelper(tree->right, prev));
	if (isBstInorderHelper(tree->left, prev)){
		if (tree->data > prev){
			prev = tree->data;
			return isBstInorderHelper(tree->right, prev);
		}else
			return false;
	}else
		return false;
}

bool isBstInorder(bst_node* tree){
	int prev = INT_MIN;

	return isBstInorderHelper(tree, prev);
}

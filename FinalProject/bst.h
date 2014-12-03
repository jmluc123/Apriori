/* ***
*    co-Author:  Joshua Lucier
*  Last Update:  October 31, 2014
*        Class:  CSI-281
*     Filename:  bst.h
*
*  Description:
*      Binary Search Tree data structure.
*
*  Certification of Authenticity:
*     I certify that this assignment is entirely my own work.
**********************************************************************/

#ifndef BST_H
#define BST_H

#include "header.h"

using namespace std;

template <typename T>
class BST
{
private:
	BST_Node<T> *mRootNode;

	BST(T data, BST_Node<T> *left, BST_Node<T> *right);

	BST(T data);

	bool bfs(Queue<BST_Node<T>*>* queue, const T &searchKey);	//Breadth-First Search

	void clear(BST_Node<T> *&node);

	void destroySubtree(BST_Node<T> *node);

	bool dfs(BST_Node<T> *node, const T &searchKey); //Depth-First Search

	void displayInOrder(BST_Node<T> *node);

	void displayPreOrder(BST_Node<T> *node);

	void displayPostOrder(BST_Node<T> *node);

	void displayTree(BST_Node<T> *node, int tab);

	int getHeight(BST_Node<T> *&node, int &max, int layer);

	void inOrder(BST_Node<T> *&node);

	void insert(BST_Node<T> *&node, const T &data);

	int leafCounter(BST_Node<T> *&root);

	void leavesCount(BST_Node<T> *node, int &count);

	int nodeCounter(BST_Node<T> *&root);

	void nodesCount(BST_Node<T> *node, int &count);

	void makeDeletion(BST_Node<T> *&node);

	void remove(BST_Node<T> *node, const T &searchKey);

	string path(BST_Node<T> *node);

	void postOrder(BST_Node<T> *&node);

	void preOrder(BST_Node<T> *&node);

	void printPath(T searchKey);

	void traverse(BST_Node<T> *&root, BST_Node<T> *&leaf, T data);

public:
	BST();
	~BST();

	bool bfs(T searchKey);		//Breadth-First Search
	bool dfs(T searchKey);		//Depth-First Search
	int  getHeight();
	void insert(T data);
	bool isEmpty();
	bool isExist(T searchKey);
	int  leavesCount();
	int  nodesCount();
	void remove(T searchKey);
	void showInOrder(); 		//Inorder Display
	void showPreOrder();  	//Preorder Display
	void showPostOrder();  	//Postorder Display
	void showTree();
};

/*        Pre:  None
*     Post:  Initialize a binary search tree
*  Purpose: initalize a binary search tree
*************************************************************************/
template <typename T>
BST<T>::BST()
{
	//add your code
	mRootNode = new BST_Node<T>();
}

/*        Pre: Another BST may exist or BST nodes may have been initialized
*     Post: initializes a new BST with nodes passed
*  Purpose: initialize a new BST with nodes
*********************************************/
template <typename T>
BST<T>::BST(T data, BST_Node<T> *left, BST_Node<T> *right)
{
	mRootNode = new BST_Node<T>(data, left, right);
}

/*        Pre: None
*     Post: Creates a BST with 1 node containing the passed value
*  Purpose: create a BST with a root node
*********************************************/
template <typename T>
BST<T>::BST(T data)
{
	mRootNode = new BST_Node<T>(data);
}

/*        Pre: BST is initialized
*     Post: delete all nodes in BST
*  Purpose: delete all nodes in BST
*********************************************/
template <typename T>
BST<T>::~BST()
{
	clear(mRootNode);
}

/*        Pre: A bst is initialized
*     Post: returns true if searchKey passed exists in BST
*  Purpose: use breadth-first-search to search for a key
*********************************************/
template <typename T>
bool BST<T>::bfs(T searchKey)
{
	Queue<BST_Node<T>*>* queue = new Queue<BST_Node<T>*>();
	bool found = bfs(queue, searchKey);
	delete queue;
	return found;
}

/*        Pre: bfs public function is called
*     Post: returns true if searchKey from bfs function is found
*  Purpose: the actual explicit loop for breadth first search utilizing a queue
*********************************************/
template <typename T>
bool BST<T>::bfs(Queue<BST_Node<T>*>* queue, const T &searchKey)
{
	BST_Node<T>* node = mRootNode;
	if (node == NULL) return false;
	if (node->mData == searchKey) return true;
	queue->enqueue(node);
	while (!queue->isEmpty())
	{
		node = queue->dequeue();
		if (node->mData == searchKey) return true;
		if (node->mLeft != NULL) queue->enqueue(node->mLeft);
		if (node->mRight != NULL) queue->enqueue(node->mRight);
	}
	return false;
}

/*        Pre: BST is initialized
*     Post: deletes nodes
*  Purpose: delete all nodes in a BST
*********************************************/
template <typename T>
void BST<T>::clear(BST_Node<T> *&node)
{
	if (node->mLeft)
	{
		clear(node->mLeft);
		node->mLeft = NULL;
	}
	if (node->mRight)
	{
		clear(node->mRight);
		node->mRight = NULL;
	}
	delete node;
}

/*        Pre: public dfs function has been called
*     Post: returns true if passed value is found in BST
*  Purpose: actual recursive function to find a value using depth first search
*********************************************/
template <typename T>
bool BST<T>::dfs(BST_Node<T> *node, const T &searchKey)
{
	if (node == NULL) return false;
	if (node->mData == searchKey) return true;
	bool left = dfs(node->mLeft, searchKey);
	if (left) return true;
	bool right = dfs(node->mRight, searchKey);
	if (right) return true;
	return false;
}

/*        Pre: BST is initialized
*     Post: returns true if passed value is found in BST
*  Purpose: calls recursive BST function to find value
*********************************************/
template <typename T>
bool BST<T>::dfs(T searchKey)
{
	return dfs(mRootNode, searchKey);
}

/*        Pre: BST is initialized
*     Post: returns number of layers in BST
*  Purpose: Find the height of a BST
*********************************************/
template <typename T>
int BST<T>::getHeight()
{
	int max = 0;
	int layer = 0;
	return getHeight(mRootNode, max, layer);
}

/*        Pre: BST is initialized and public getHeight function is called
*     Post: returns number of layers in BST
*  Purpose: use a recursive method to find the height of a BST
*********************************************/
template <typename T>
int BST<T>::getHeight(BST_Node<T> *&node, int &max, int layer)
{
	//height = 0 with one node according to NIST
	if (node == NULL)
	{
		return 0;
	}
	int count = 1;
	int left = getHeight(node->mLeft, max, layer) + count;
	int right = getHeight(node->mRight, max, layer) + count;
	if (left > right) return left;
	return right;
}

/*        Pre: BST is initialized
*     Post: prints every node with "in-order" traversal.
*  Purpose: get in-order traversal order
*********************************************/
template <typename T>
void BST<T>::inOrder(BST_Node<T> *&node)
{
	if (node != NULL)
	{
		inOrder(node->mLeft);
		cout << node->mData << ", ";
		inOrder(node->mRight);
	}
}

/*        Pre: BST is initialized
*     Post: a BST node is added to the BST
*  Purpose:  add a BST node to the BST using the rules of the BST
*********************************************/
template <typename T>
void BST<T>::insert(T data)
{
	BST_Node<T> *node = new BST_Node<T>(data);
	BST_Node<T> *leaf;
	traverse(mRootNode, leaf, data);
	if (data > leaf->mData) leaf->mRight = node;
	else if (data < leaf->mData) leaf->mLeft = node;
	else delete node;  //number is already present
}

/*        Pre: BST is initialized
*     Post: returns number of nodes in the tree
*  Purpose: get the number of nodes in the BST
*********************************************/
template <typename T>
int BST<T>::nodesCount()
{
	return nodeCounter(mRootNode);
}

/*        Pre: BST is initialized and public nodesCount function is called
*     Post: returns number of nodes in the BST
*  Purpose: use recursion to count each node in the BST
*********************************************/
template <typename T>
int BST<T>::nodeCounter(BST_Node<T> *&root)
{
	if (root == NULL) return 0;
	int count = 1;
	count = nodeCounter(root->mLeft) + count;
	count = nodeCounter(root->mRight) + count;
	return count;
}

/*        Pre: BST is initialized
*     Post: Prints all nodes in post-order
*  Purpose: use post-order traversal to recursively print all nodes in BST
*********************************************/
template <typename T>
void BST<T>::postOrder(BST_Node<T> *&node)
{
	if (node != NULL)
	{
		postOrder(node->mLeft);
		postOrder(node->mRight);
		cout << node->mData << ", ";
	}
}

/*        Pre:  BST is initialized
*     Post: Prints all nodes in pre-order
*  Purpose: use pre-order traversal to recursively print all nodes in BST
*********************************************/
template <typename T>
void BST<T>::preOrder(BST_Node<T> *&node)
{
	if (node != NULL)
	{
		cout << node->mData << ", ";
		preOrder(node->mLeft);
		preOrder(node->mRight);
	}
}

/*        Pre:
*     Post:
*  Purpose:
*********************************************/
template <typename T>
void BST<T>::printPath(T searchKey)
{

}

/*        Pre: BST is initialized
*     Post: if a node contains the given value it is removed
*  Purpose: uses rules of the BST to remove a node
*********************************************/
template <typename T>
void BST<T>::remove(T searchKey)
{
	remove(mRootNode, searchKey);
}

/*        Pre: BST is initialized and public remove function is called
*     Post: if a node contains the given value it is removed
*  Purpose: uses rules of BST to remove a node
*********************************************/
template <typename T>
void BST<T>::remove(BST_Node<T> *node, const T &searchKey)
{
	if (node == NULL) return;
	if (node->mLeft != NULL)
	{
		if (node->mLeft->mData == searchKey)
		{
			BST_Node<T>* replacement;
			BST_Node<T>* rParent;
			if (node->mLeft->mLeft != NULL)
			{
				rParent = node->mLeft;
				replacement = node->mLeft->mLeft;
				while (replacement->mRight != NULL)
				{
					rParent = replacement;
					replacement = replacement->mRight;
				}
				replacement->mRight = node->mLeft->mRight;
				rParent->mRight = NULL;
				delete node->mLeft;
				node->mLeft = replacement;
			}
			else if (node->mLeft->mRight != NULL)
			{
				rParent = node->mLeft;
				replacement = node->mLeft->mRight;
				while (replacement->mLeft != NULL)
				{
					rParent = replacement;
					replacement = replacement->mLeft;
				}
				replacement->mLeft = node->mLeft->mLeft;
				rParent->mLeft = NULL;
				delete node->mLeft;
				node->mLeft = replacement;
			}
			else
			{
				replacement = node->mLeft;
				node->mLeft = NULL;
				delete replacement;
			}
		}
	}
	if (node->mRight != NULL)
	{
		if (node->mRight->mData == searchKey)
		{
			BST_Node<T>* replacement;
			BST_Node<T>* rParent;
			if (node->mRight->mLeft != NULL)
			{
				rParent = node->mRight;
				replacement = node->mRight->mLeft;
				while (replacement->mRight != NULL)
				{
					rParent = replacement;
					replacement = replacement->mRight;
				}
				replacement->mRight = node->mRight->mRight;
				rParent->mRight = NULL;
				delete node->mRight;
				node->mRight = replacement;
			}
			else if (node->mRight->mRight != NULL)
			{
				rParent = node->mRight;
				replacement = node->mRight->mRight;
				while (replacement->mLeft != NULL)
				{
					rParent = replacement;
					replacement = replacement->mLeft;
				}
				replacement->mLeft = node->mRight->mLeft;
				rParent->mLeft = NULL;
				delete node->mRight;
				node->mRight = replacement;
			}
			else
			{
				replacement = node->mRight;
				node->mRight = NULL;
				delete replacement;
			}
		}
	}

	if (mRootNode->mData == searchKey)
	{
		BST_Node<T>* replacement;
		BST_Node<T>* parent;
		if (mRootNode->mLeft != NULL)
		{
			parent = mRootNode;
			replacement = mRootNode->mLeft;
			while (replacement->mRight != NULL)
			{
				parent = replacement;
				replacement = replacement->mRight;
			}
			replacement->mRight = mRootNode->mRight;
			parent->mRight = NULL;
			delete mRootNode;
			mRootNode = replacement;
			return;
		}
		else if (mRootNode->mRight != NULL)
		{
			parent = mRootNode;
			replacement = mRootNode->mRight;
			while (replacement->mLeft != NULL)
			{
				parent = replacement;
				replacement = replacement->mLeft;
			}
			replacement->mLeft = mRootNode->mLeft;
			parent->mLeft = NULL;
			delete mRootNode;
			mRootNode = replacement;
			return;
		}
		else
		{
			delete mRootNode;
			mRootNode = NULL;
			return;
		}
	}
	remove(node->mLeft, searchKey);
	remove(node->mRight, searchKey);
}

/*        Pre: BST is initialized
*     Post: Displays all nodes in BST in-order
*  Purpose: Display all nodes in BST in-order
*********************************************/
template <typename T>
void BST<T>::showInOrder()
{
	cout << "Tree in In-Order: ";
	inOrder(mRootNode);
	cout << endl << endl;
}

/*        Pre: BST is initialized
*     Post: Display all nodes in BST in post-order
*  Purpose: Display all nodes in BST in post-order
*********************************************/
template <typename T>
void BST<T>::showPostOrder()
{
	cout << "Tree in post-order: ";
	postOrder(mRootNode);
	cout << endl << endl;
}

/*        Pre: BST is initialized
*     Post:Display all nodes in BST in pre-order
*  Purpose:Display all nodes in BST in pre-order
*********************************************/
template <typename T>
void BST<T>::showPreOrder()
{
	cout << "Tree in pre-order: ";
	preOrder(mRootNode);
	cout << endl << endl;
}

/*        Pre: BST is initialized
*     Post: Display all nodes in BST in pre-order
*  Purpose: Display all nodes in BST in pre-order
*********************************************/
template <typename T>
void BST<T>::showTree()
{
	cout << "Tree in pre-order: ";
	preOrder(mRootNode);
	cout << endl << endl;

}

/*        Pre: BST is initialized and insert funciton is called
*     Post: assigns BST node pointer to the correct leaf node for adding data
*  Purpose: recursively find best leaf for data insertion
*********************************************/
template <typename T>
void BST<T>::traverse(BST_Node<T> *&root, BST_Node<T> *&leaf, T data)
{
	if (root == NULL) return;
	leaf = root;
	if (data > leaf->mData)
	{
		if (leaf->mRight) traverse(leaf->mRight, leaf, data);
	}
	else if (data < leaf->mData)
	{
		if (leaf->mLeft) traverse(leaf->mLeft, leaf, data);
	}
}

/*        Pre: BST is initialized
*     Post: returns the number of leaves in a BST
*  Purpose:get the number of leaves in a BST
*********************************************/
template <typename T>
int BST<T>::leavesCount()
{
	return leafCounter(mRootNode);
}

/*        Pre: BST is initialized and leavesCount is called
*     Post: returns the number of leaf nodes in the BST
*  Purpose: get the number of leaf nodes in a BST
*********************************************/
template <typename T>
int BST<T>::leafCounter(BST_Node<T> *&root)
{
	int count = 0;
	if (root == NULL) return count;
	if (!root->mLeft && !root->mRight) return 1;
	if (root->mLeft) count = leafCounter(root->mLeft) + count;
	if (root->mRight) count = leafCounter(root->mRight) + count;
	return count;
}

//add your functions
//for each function, you need add your header: Pre, Post, Purpose

#endif
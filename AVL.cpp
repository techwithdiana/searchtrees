/*
 * AVL.cpp
 *
 *  Created on: Mar 5, 2022
 *      Author: Diana
 */

#include <iostream>
#include <string>
#include <fstream>
#include <math.h>
#include "AVL.h"

using namespace std;

AVL::node* AVL::insert(node* n, int value)
{
	if (n == NULL) {
		//create new node with required value
		n = new node;
		n->key = value;
		n->height = 0;
		n->left = n->right = NULL;
		return n;
	}
	else if (value < n->key) {
		//node should be created to the left side of the tree
		n->left = insert(n->left, value);
	}
	else if (value > n->key) {
		//node should be created to the right side of the tree
		n->right = insert(n->right, value);
	}
	else {
		return n;
	}

	//update height
	n->height = max(findHeight(n->left), findHeight(n->right)) + 1;

	//rebalance tree
	if (findHeight(n->left) - findHeight(n->right) > 1) {
		//unbalanced to the left side
		if (value < n->left->key) {
			n = rightRotate(n);
		}
		else {
			n = leftRightRotate(n);
		}
	}
	else if (findHeight(n->left) - findHeight(n->right) < -1) {
		//unbalanced to the right side
		if (value > n->right->key) {
			n = leftRotate(n);
		}
		else {
			n = rightLeftRotate(n);
		}
	}

	return n;
}

// Function to find a key in AVL tree
AVL::node* AVL::find(node* n, int value)
{
	if (n == NULL) {
		return NULL;
	}
	else if (value < n->key) {
		//search for node on the left side of the tree
		return find(n->left, value);
	}
	else if (value > n->key) {
		//search for node on the right side of the tree
		return find(n->right, value);
	}
	else {
		//node found
		return n;
	}
}

AVL::node* AVL::deleteNode(node* n, int value)
{
	node* temp;

	// Element not found
	if (n == NULL) {
		return NULL;
	}
	// Searching for element
	else if (value < n->key) {
		//search for node on the left side of the tree
		n->left = deleteNode(n->left, value);
	}
	else if (value > n->key) {
		//search for node on the right side of the tree
		n->right = deleteNode(n->right, value);
	}
	else if (n->left && n->right) {
		//delete node and rearrange right branch if case we have bought
		temp = findMin(n->right);
		n->key = temp->key;
		n->right = deleteNode(n->right, temp->key);
	}
	// With one or zero child
	else {
		//delete node and free memory
		temp = n;
		if (n->left == NULL) {
			n = n->right;
		}
		else if (n->right == NULL) {
			n = n->left;
		}
		else {
			n = NULL;
		}
		delete temp;
	}
	//return if node was deleted
	if (n == NULL) {
		return n;
	}

	//update height
	n->height = max(findHeight(n->left), findHeight(n->right)) + 1;

	// If node is unbalanced
	if (findHeight(n->left) - findHeight(n->right) > 1) {
		if (findHeight(n->left->left) - findHeight(n->left->right) > 0) {
			n = rightRotate(n);
		}
		else {
			n = leftRightRotate(n);
		}
	}
	else if (findHeight(n->left) - findHeight(n->right) < -1) {
		if (findHeight(n->right->left) - findHeight(n->right->right) > 0) {
			n = rightLeftRotate(n);
		}
		else {
			n = leftRotate(n);
		}
	}

	return n;
}

AVL::node* AVL::rightRotate(node*& n)
{
	node* u = n->left;
	node* r = u->right;
	//rotate to right
	u->right = n;
	n->left = r;
	// Update heights
	n->height = max(findHeight(n->left), findHeight(n->right)) + 1;
	u->height = max(findHeight(u->left), findHeight(u->right)) + 1;

	statsAVL.rNo++;
	return u;
}

AVL::node* AVL::leftRotate(node*& n)
{
	node* u = n->right;
	node* l = u->left;
	//rotate to left
	u->left = n;
	n->right = l;
	// Update heights
	n->height = max(findHeight(n->left), findHeight(n->right)) + 1;
	u->height = max(findHeight(u->left), findHeight(u->right)) + 1;

	statsAVL.lNo++;
	return u;
}

AVL::node* AVL::leftRightRotate(node*& n)
{
	statsAVL.lrNo++;
	statsAVL.lNo--;
	statsAVL.rNo--;
	n->left = leftRotate(n->left);
	return rightRotate(n);
}

AVL::node* AVL::rightLeftRotate(node*& n)
{
	statsAVL.rlNo++;
	statsAVL.lNo--;
	statsAVL.rNo--;
	n->right = rightRotate(n->right);
	return leftRotate(n);
}

AVL::node* AVL::findMin(node* n)
{
	if (n == NULL) {
		return NULL;
	}
	else if (n->left == NULL) {
		//node with minimum value found
		return n;
	}
	else {
		//search on the left branch for minimum value
		return findMin(n->left);
	}
}

int AVL::findHeight(node* n)
{
	return (n == NULL ? -1 : n->height);
}

void AVL::fillDisplay(node* n, int depth, int offSet, int offSetChange, char** displayTree) {
	if (n == NULL) {
		return;
	}

	// fill key at the appropriate position
	std::string dataString = std::to_string(n->key);
	dataString.copy(&displayTree[depth][offSet - 2], dataString.size());

	fillDisplay(n->left, depth + 1, offSet - offSetChange, offSetChange / 2, displayTree);
	fillDisplay(n->right, depth + 1, offSet + offSetChange, offSetChange / 2, displayTree);
}

AVL::AVL()
{
	root = NULL;
	statsAVL.deletionNo = 0;
	statsAVL.insertNo = 0;
	statsAVL.searchNo = 0;
	statsAVL.lNo = 0;
	statsAVL.rNo = 0;
	statsAVL.lrNo = 0;
	statsAVL.rlNo = 0;
}

void AVL::insert(int value, std::ofstream& outFile)
{
	stats oldStatsAVL;
	oldStatsAVL = statsAVL;

	//output inserted value to screen and output file
	cout << "Inserts: " << value << endl;
	outFile << "Inserts: " << value << endl;

	root = insert(root, value);

	//check number of rotations
	cout << "Rotations: ";
	outFile << "Rotations: ";
	//check number of L rotations
	if (statsAVL.lNo - oldStatsAVL.lNo > 0) {
		cout << statsAVL.lNo - oldStatsAVL.lNo << " L; ";
		outFile << statsAVL.lNo - oldStatsAVL.lNo << " L; ";
		statsAVL.insertNo = statsAVL.insertNo + statsAVL.lNo - oldStatsAVL.lNo;
	}
	//check number of R rotations
	if (statsAVL.rNo - oldStatsAVL.rNo > 0) {
		cout << statsAVL.rNo - oldStatsAVL.rNo << " R; ";
		outFile << statsAVL.rNo - oldStatsAVL.rNo << " R; ";
		statsAVL.insertNo = statsAVL.insertNo + statsAVL.rNo - oldStatsAVL.rNo;
	}
	//check number of LR rotations
	if (statsAVL.lrNo - oldStatsAVL.lrNo > 0) {
		cout << statsAVL.lrNo - oldStatsAVL.lrNo << " LR; ";
		outFile << statsAVL.lrNo - oldStatsAVL.lrNo << " LR; ";
		statsAVL.insertNo = statsAVL.insertNo + statsAVL.lrNo - oldStatsAVL.lrNo;
	}
	//check number ofRL rotations
	if (statsAVL.rlNo - oldStatsAVL.rlNo > 0) {
		cout << statsAVL.rlNo - oldStatsAVL.rlNo << " RL; ";
		outFile << statsAVL.rlNo - oldStatsAVL.rlNo << " RL; ";
		statsAVL.insertNo = statsAVL.insertNo + statsAVL.rlNo - oldStatsAVL.rlNo;
	}

	statsAVL.insertNo++;

	cout << endl;
	outFile << endl;
}

void AVL::search(int value, std::ofstream& outFile) {
	statsAVL.searchNo++;
	if (find(root, value) != NULL) {
		//output result to screen and output file
		cout << "Value " << value << " was found" << endl;
		outFile << "Value " << value << " was found" << endl;
	}
	else {
		//output result to screen and output file
		cout << "Value " << value << " was not found" << endl;
		outFile << "Value " << value << " was not found" << endl;
	}
}

void AVL::deleteNode(int value, std::ofstream& outFile)
{
	stats oldStatsAVL;
	oldStatsAVL = statsAVL;

	//output inserted value to screen and output file
	cout << "Deletion: " << value << endl;
	outFile << "Deletion: " << value << endl;

	root = deleteNode(root, value);

	//check number of rotations
	cout << "Rotations: ";
	outFile << "Rotations: ";
	//check number of L rotations
	if (statsAVL.lNo - oldStatsAVL.lNo > 0) {
		cout << statsAVL.lNo - oldStatsAVL.lNo << " L; ";
		outFile << statsAVL.lNo - oldStatsAVL.lNo << " L; ";
		statsAVL.deletionNo = statsAVL.deletionNo + statsAVL.lNo - oldStatsAVL.lNo;
	}
	//check number of RR rotations
	if (statsAVL.rNo - oldStatsAVL.rNo > 0) {
		cout << statsAVL.rNo - oldStatsAVL.rNo << " R; ";
		outFile << statsAVL.rNo - oldStatsAVL.rNo << " R; ";
		statsAVL.deletionNo = statsAVL.deletionNo + statsAVL.rNo - oldStatsAVL.rNo;
	}
	//check number of LR rotations
	if (statsAVL.lrNo - oldStatsAVL.lrNo > 0) {
		cout << statsAVL.lrNo - oldStatsAVL.lrNo << " LR; ";
		outFile << statsAVL.lrNo - oldStatsAVL.lrNo << " LR; ";
		statsAVL.deletionNo = statsAVL.deletionNo + statsAVL.lrNo - oldStatsAVL.lrNo;
	}
	//check number of RL rotations
	if (statsAVL.rlNo - oldStatsAVL.rlNo > 0) {
		cout << statsAVL.rlNo - oldStatsAVL.rlNo << " RL; ";
		outFile << statsAVL.rlNo - oldStatsAVL.rlNo << " RL; ";
		statsAVL.deletionNo = statsAVL.deletionNo + statsAVL.rlNo - oldStatsAVL.rlNo;
	}

	statsAVL.deletionNo++;

	cout << endl;
	outFile << endl;
}

void AVL::printTree(std::ofstream& outFile)
{
	// find the height of the tree
	int height = findHeight(root);
	if (height < 0) {
		height = 0;
	}
	// create a display table
	int displayTreeHeight = height + 1;
	int displayTreeWidth = pow(2, height) * 4;
	char** displayTree = new char* [displayTreeHeight];
	for (int i = 0; i < displayTreeHeight; i++) {
		displayTree[i] = new char[displayTreeWidth];
		for (int j = 0; j < displayTreeWidth; j++) {
			displayTree[i][j] = ' ';
		}
	}

	//fill display table
	fillDisplay(root, 0, displayTreeWidth / 2, displayTreeWidth / 4, displayTree);

	//write table to file and screen
	for (int i = 0; i < displayTreeHeight; i++) {
		for (int j = 0; j < displayTreeWidth; j++) {
			cout << displayTree[i][j];
			outFile << displayTree[i][j];
		}
		cout << endl;
		outFile << endl;
	}

	//free memory
	for (int i = 0; i < displayTreeHeight; i++) {
		delete[] displayTree[i];
	}
	delete[] displayTree;

	//display tree height
	cout << "Tree height is: " << height << endl;
	outFile << "Tree height is: " << height << endl;
}



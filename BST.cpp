/*
 * BTS.CPP
 *
 *  Created on: Mar 3, 2022
 *      Author: Diana
 */
#include <iostream>
#include <string>
#include <fstream>
#include <math.h>
#include"BST.h"
using namespace std;



BST::node* BST::insert(node* n, int value)
{
	if (n == NULL) {
		//create new node with required value
		n = new node;
		n->key = value;
		n->left = n->right = NULL;
	}
	else if (value < n->key) {
		//node should be created to the left side of the tree
		n->left = insert(n->left, value);
	}
	else if (value > n->key) {
		//node should be created to the right side of the tree
		n->right = insert(n->right, value);
	}

	return n;
}

BST::node* BST::find(node* n, int value) {
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

BST::node* BST::deleteNode(node* n, int value) {
	node* temp;
	if (n == NULL) {
		return NULL;
	}
	else if (value < n->key) {
		//search for node on the left side of the tree
		n->left = deleteNode(n->left, value);
	}
	else if (value > n->key) {
		//search for node on the right side of the tree
		n->right = deleteNode(n->right, value);
	}
	else if (n->left && n->right)
	{
		//delete and rearrange right branch if case we have bought
		temp = findMin(n->right);
		n->key = temp->key;
		n->right = deleteNode(n->right, n->key);
	}
	else
	{
		//delete node and free memory
		temp = n;
		if (n->left == NULL) {
			n = n->right;
		}
		else if (n->right == NULL) {
			n = n->left;
		}
		delete temp;
	}

	return n;
}

BST::node* BST::findMin(node* n)
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

int BST::findHeight(node* n)
{
	if (n == NULL) {
		//no children, height is 0
		return -1;
	}
	else {
		//chose max height between left and right side
		return std::max(findHeight(n->left), findHeight(n->right)) + 1;
	}
}

void BST::fillDisplay(node* n, int depth, int offSet, int offSetChange, char** displayTree) {
	if (n == NULL) {
		return;
	}

	// fill key at the appropriate position
	std::string dataString = std::to_string(n->key);
	dataString.copy(&displayTree[depth][offSet - 2], dataString.size());

	fillDisplay(n->left, depth + 1, offSet - offSetChange, offSetChange / 2, displayTree);
	fillDisplay(n->right, depth + 1, offSet + offSetChange, offSetChange / 2, displayTree);
}

BST::BST() {
	root = NULL;
	statsBTS.deletionNo = 0;
	statsBTS.insertNo = 0;
	statsBTS.searchNo = 0;
}

void BST::insert(int value, std::ofstream& outFile) {

	//output inserted value to screen and output file
	cout << "Inserts: " << value << endl;
	outFile << "Inserts: " << value << endl;

	root = insert(root, value);
	statsBTS.insertNo++;
}

void BST::search(int value, std::ofstream& outFile) {
	statsBTS.searchNo++;
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

void BST::deleteNode(int value, std::ofstream& outFile) {
	//output inserted value to screen and output file
	cout << "Deletion: " << value << endl;
	outFile << "Deletion: " << value << endl;

	root = deleteNode(root, value);

	statsBTS.deletionNo++;
}

void BST::printTree(std::ofstream& outFile) {
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

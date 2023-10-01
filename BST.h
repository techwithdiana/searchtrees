/*
 * BTS.h
 *
 *  Created on: Mar 3, 2022
 *      Author: Diana
 */

#ifndef SRC_BST_H_
#define SRC_BST_H_

#include<ostream>
#include "ST.h"

class BST : public ST {

    struct node {
        int key;
        node* left;
        node* right;
    };

    struct stats {
        int searchNo;
        int insertNo;
        int deletionNo;
    };

    node* root;

    node* insert(node* n, int value);

    node* find(node* n, int value);

    node* deleteNode(node* n, int value);

    node* findMin(node* n);

    int findHeight(node* n);

    void fillDisplay(node* n, int depth, int offSet, int offSetChange, char** displayTree);

public:
    BST();

    stats statsBTS;

    void insert(int value, std::ofstream& outFile);

    void search(int value, std::ofstream& outFile);

    void deleteNode(int value, std::ofstream& outFile);

    void printTree(std::ofstream& outFile);

};

#endif /* SRC_BST_H_ */

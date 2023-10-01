/*
 * AVL.h
 *
 *  Created on: Mar 5, 2022
 *      Author: Diana
 */

#ifndef SRC_AVL_H_
#define SRC_AVL_H_

#include<ostream>
#include "ST.h"

class AVL : public ST {

    struct node
    {
        int key;
        node* left;
        node* right;
        int height;
    };

    struct stats {
        int searchNo;
        int insertNo;
        int deletionNo;
        int lNo;
        int rNo;
        int lrNo;
        int rlNo;
    };

    node* root;

    node* insert(node* n, int value);

    node* find(node* n, int value);

    node* deleteNode(node* n, int value);

    node* rightRotate(node*& n);

    node* leftRotate(node*& n);

    node* leftRightRotate(node*& n);

    node* rightLeftRotate(node*& n);

    node* findMin(node* n);

    int findHeight(node* n);

    void fillDisplay(node* n, int depth, int offSet, int offSetChange, char** displayTree);

public:
    AVL();

    stats statsAVL;

    void insert(int value, std::ofstream& outFile);

    void search(int value, std::ofstream& outFile);

    void deleteNode(int value, std::ofstream& outFile);

    void printTree(std::ofstream& outFile);
};



#endif /* SRC_AVL_H_ */



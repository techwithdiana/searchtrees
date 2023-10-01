/*
 * Splay.h
 *
 *  Created on: Mar 5, 2022
 *      Author: Diana
 */

#ifndef SRC_SPLAY_H_
#define SRC_SPLAY_H_

#include<ostream>
#include "ST.h"

class Splay : public ST {

    struct node
    {
        int key;
        node* left;
        node* right;
        node* parent;
    };

    struct stats {
        int searchNo;
        int insertNo;
        int deletionNo;
        int zigNo;
        int zagNo;
        int zigzigNo;
        int zagzagNo;
        int zigzagNo;
        int zagzigNo;
    };

    node* root;

    void insert(int value);

    node* find(node* n, int value);

    void deleteNode(node* node, int value);

    void Zig(node* n);

    void Zag(node* n);

    void ZigZig(node* n);

    void ZigZag(node* n);

    void ZagZag(node* n);

    void ZagZig(node* n);

    void splay(node* n);

    void replace(node* n1, node* n2);

    node* findMin(node* n);

    int findHeight(node* n);

    void fillDisplay(node* n, int depth, int offSet, int offSetChange, char** displayTree);

public:
    Splay();

    stats statsSplay;

    void insert(int value, std::ofstream& outFile);

    void search(int value, std::ofstream& outFile);

    void deleteNode(int value, std::ofstream& outFile);

    void printTree(std::ofstream& outFile);
};

#endif /* SRC_SPLAY_H_ */



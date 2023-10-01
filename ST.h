/*
 * ST.h
 *
 *  Created on: Mar 7, 2022
 *      Author: Diana
 */

#ifndef SRC_ST_H_
#define SRC_ST_H_

class ST
{
public:

	virtual void insert(int value, std::ofstream& outFile) {};

	virtual void search(int value, std::ofstream& outFile) {};

	virtual void deleteNode(int value, std::ofstream& outFile) {};

	virtual void printTree(std::ofstream& outFile) {};

};

#endif /* SRC_ST_H_ */

/*
 * main.cpp
 *
 *  Created on: Mar 3, 2022
 *      Author: Diana
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "ST.h"
#include "BST.h"
#include "AVL.h"
#include "Splay.h"
using namespace std;

class FileHandler
{
	void processActionInsert(ST* tree, int actionValue, ofstream& outputStream) {
		//insert value in the tree
		tree->insert(actionValue, outputStream);

		//print tree
		tree->printTree(outputStream);
	}

	void processActionDelete(ST* tree, int actionValue, ofstream& outputStream) {
		//delete node
		tree->deleteNode(actionValue, outputStream);

		//print tree
		tree->printTree(outputStream);
	}

	void processActionSearch(ST* tree, int actionValue, ofstream& outputStream) {
		tree->search(actionValue, outputStream);
	}

public:
	// input files
	ifstream fileInsert, fileAction;
	// output files
	ofstream fileOutputBST, fileOutputAVL, fileOutputSplay;
	// stats file
	fstream fileOutputSummary;
	// name of the test
	string testName;

	BST treeBTS;
	AVL treeAVL;
	Splay treeSplay;

	void processInserFile(ST* tree, ofstream& outputStream) {
		// process input file
		std::string line;

		//go to beginning of file
		fileInsert.clear();
		fileInsert.seekg(0, ios::beg);

		while (std::getline(fileInsert, line))
		{
			int insertValue;
			std::istringstream iss(line);

			if (iss >> insertValue)
			{
				processActionInsert(tree, insertValue, outputStream);
			}
		}
	}

	void processActionFile(ST* tree, ofstream& outputStream) {
		// process actions file
		std::string line;

		//go to beginning of file
		fileAction.clear();
		fileAction.seekg(0, ios::beg);

		while (std::getline(fileAction, line))
		{
			std::istringstream iss(line);
			char action;
			int actionValue;

			if ((iss >> action >> actionValue) && ((action == 'S') || (action == 'I') || (action == 'D'))) {
				switch (action)
				{
				case 'S': {
					//process search
					processActionSearch(tree, actionValue, outputStream);
					break;
				}
				case 'I': {
					//process insert
					processActionInsert(tree, actionValue, outputStream);
					break;
				}
				case 'D': {
					//process deletion
					processActionDelete(tree, actionValue, outputStream);
					break;
				}
				}
			}
			else {
				cout << "error in actions file" << endl;
				outputStream << "error in actions file" << endl;
			}
		}

	}

	void outputStats(ostream& outputStream) {
		int totalBTS = treeBTS.statsBTS.searchNo + treeBTS.statsBTS.insertNo + treeBTS.statsBTS.deletionNo;
		int totalAVL = treeAVL.statsAVL.searchNo + treeAVL.statsAVL.insertNo + treeAVL.statsAVL.deletionNo;
		int totalSplay = treeSplay.statsSplay.searchNo + treeSplay.statsSplay.insertNo + treeSplay.statsSplay.deletionNo;
		//output stats
		outputStream << "          " << testName << endl;
		outputStream << "          Operation Counts" << endl;
		outputStream << endl;
		outputStream << "           BST           AVL          Splay" << endl;
		outputStream << "Search    " << treeBTS.statsBTS.searchNo << "             " << treeAVL.statsAVL.searchNo << "            " << treeSplay.statsSplay.searchNo << endl;
		outputStream << "Insert    " << treeBTS.statsBTS.insertNo << "             " << treeAVL.statsAVL.insertNo << "            " << treeSplay.statsSplay.insertNo << endl;
		outputStream << "Delete    " << treeBTS.statsBTS.deletionNo << "             " << treeAVL.statsAVL.deletionNo << "            " << treeSplay.statsSplay.deletionNo << endl;
		outputStream << "------------------------------------------" << endl;
		outputStream << "Total     " << totalBTS << "            " << totalAVL << "           " << totalSplay << endl;
	}

	void outputSummary(string fileName) {
		int totalBTS = treeBTS.statsBTS.searchNo + treeBTS.statsBTS.insertNo + treeBTS.statsBTS.deletionNo;
		int totalAVL = treeAVL.statsAVL.searchNo + treeAVL.statsAVL.insertNo + treeAVL.statsAVL.deletionNo;
		int totalSplay = treeSplay.statsSplay.searchNo + treeSplay.statsSplay.insertNo + treeSplay.statsSplay.deletionNo;

		if ((!fileOutputSummary) || (fileOutputSummary.peek() == std::ifstream::traits_type::eof())) {
			fileOutputSummary.close();
			fileOutputSummary.open(fileName, ios_base::out);

			fileOutputSummary << "          Summary" << endl;
			fileOutputSummary << "          Operation Counts" << endl;
			fileOutputSummary << endl;
			fileOutputSummary << "Test   Title                   BST                AVL               Splay" << endl;
			fileOutputSummary << "1      " << testName << "           " << totalBTS << "                " << totalAVL << "                " << totalSplay << endl;
			fileOutputSummary << "---------------------------------------------------------" << endl;
			fileOutputSummary << "Total of 1 tests:              " << totalBTS << "                 " << totalAVL << "                 " << totalSplay << endl;
			fileOutputSummary.close();
		}
		else {
			fileOutputSummary.close();
			fileOutputSummary.open(fileName, ios_base::in | ios_base::out);
			fileOutputSummary.seekg(-1, ios_base::end);

			bool findLastEntry = true;
			int entryLine = 0;
			int totalTests, totalActionsBST, totalActionsAVL, totalActionsSplay;

			while (findLastEntry) {
				// Get current byte's data
				char ch;
				fileOutputSummary.get(ch);

				if (((int)fileOutputSummary.tellg() <= 1)) {
					// file has no previous stats, print generic
					fileOutputSummary.seekg(ios_base::beg);
					fileOutputSummary << "          Summary" << endl;
					fileOutputSummary << "          Operation Counts" << endl;
					fileOutputSummary << endl;
					fileOutputSummary << "Test   Title                   BST                AVL               Splay" << endl;
					fileOutputSummary << "1      " << testName << "           " << totalBTS << "                " << totalAVL << "                " << totalSplay << endl;
					fileOutputSummary << "---------------------------------------------------------" << endl;
					fileOutputSummary << "Total of 1 tests:              " << totalBTS << "                 " << totalAVL << "                 " << totalSplay << endl;
					findLastEntry = false;
				}
				else if (ch == '\n') {
					if (entryLine == 0) {
						entryLine = 1;
						fileOutputSummary.seekg(-2, ios_base::cur);
					}
					else if (entryLine == 1) {
						string lastLine;
						int pos = fileOutputSummary.tellg();

						getline(fileOutputSummary, lastLine);

						std::istringstream iss2(lastLine);
						string bs;

						iss2 >> bs >> bs >> totalTests >> bs >> totalActionsBST >> totalActionsAVL >> totalActionsSplay;

						entryLine = 2;

						fileOutputSummary.seekg(pos);
						fileOutputSummary.seekg(-2, ios_base::cur);
					}
					else {
						fileOutputSummary << totalTests + 1 << "      " << testName << "           " << totalBTS << "                " << totalAVL << "                " << totalSplay << endl;
						fileOutputSummary << "---------------------------------------------------------" << endl;
						fileOutputSummary << "Total of " << totalTests + 1 << " tests:              " << totalActionsBST + totalBTS << "                 " << totalActionsAVL + totalAVL << "                 " << totalActionsSplay + totalSplay << endl;

						findLastEntry = false;
					}

				}
				else {
					// Move to the front of that data, then to the front of the data before it
					fileOutputSummary.seekg(-2, ios_base::cur);
				}
			}
			fileOutputSummary.close();
		}
	}

};

int main() {
	// string used to input file names
	string fileName;
	FileHandler fileHandler;

	// get test name
	cout << "Enter Test Name: ";

	cin >> fileHandler.testName;

	// get fileInsert name
	do
	{
		cout << "Enter input file for inserts: ";
		cin >> fileName;
		// open file and check if it was possible to open and file is not enpty
		fileHandler.fileInsert.open(fileName, ios_base::in);
		if (!fileHandler.fileInsert) {
			cerr << "Can't open input file!";
		}
		if (fileHandler.fileInsert.peek() == std::ifstream::traits_type::eof())
		{
			cerr << "Insert file is empty";
		}
	} while ((!fileHandler.fileInsert) || (fileHandler.fileInsert.peek() == std::ifstream::traits_type::eof()));

	// get fileAction name
	do
	{
		cout << "Enter input file for actions: ";
		cin >> fileName;
		// open file and check if it was possible to open and file is not enpty
		fileHandler.fileAction.open(fileName, ios_base::in);
		if (!fileHandler.fileAction) {
			cerr << "Can't open actions file!";
		}
		if (fileHandler.fileAction.peek() == std::ifstream::traits_type::eof())
		{
			cerr << "Actions file is empty";
		}
	} while ((!fileHandler.fileAction) || (fileHandler.fileAction.peek() == std::ifstream::traits_type::eof()));

	// get fileOutputBST name
	cout << "Enter output file for BST tree: ";
	cin >> fileName;
	// open file
	fileHandler.fileOutputBST.open(fileName, ios_base::out);

	// get fileOutputAVL name
	cout << "Enter output file for AVL tree: ";
	cin >> fileName;
	// open file
	fileHandler.fileOutputAVL.open(fileName, ios_base::out);

	// get fileOutputSplay name
	cout << "Enter output file for Splay tree: ";
	cin >> fileName;
	// open file
	fileHandler.fileOutputSplay.open(fileName, ios_base::out);

	// get fileOutputSummary name
	cout << "Enter output file for summary: ";
	cin >> fileName;
	// open file
	fileHandler.fileOutputSummary.open(fileName, ios_base::in | ios_base::out);

	//process insert file
	cout << "------------------------------------------------------------------------" << endl;
	cout << "Inserts for BTS" << endl;
	fileHandler.processInserFile(&fileHandler.treeBTS, fileHandler.fileOutputBST);

	cout << "------------------------------------------------------------------------" << endl;
	cout << "Inserts for AVL" << endl;
	fileHandler.processInserFile(&fileHandler.treeAVL, fileHandler.fileOutputAVL);

	cout << "------------------------------------------------------------------------" << endl;
	cout << "Inserts for Splay" << endl;
	fileHandler.processInserFile(&fileHandler.treeSplay, fileHandler.fileOutputSplay);

	//process actions file
	cout << "------------------------------------------------------------------------" << endl;
	cout << "Actions for BTS" << endl;
	fileHandler.processActionFile(&fileHandler.treeBTS, fileHandler.fileOutputBST);

	cout << "------------------------------------------------------------------------" << endl;
	cout << "Actions for AVL" << endl;
	fileHandler.processActionFile(&fileHandler.treeAVL, fileHandler.fileOutputAVL);

	cout << "------------------------------------------------------------------------" << endl;
	cout << "Actions for Splay" << endl;
	fileHandler.processActionFile(&fileHandler.treeSplay, fileHandler.fileOutputSplay);

	//actions processed => output stats and summary
	fileHandler.outputStats(cout);
	fileHandler.outputStats(fileHandler.fileOutputBST);
	fileHandler.outputStats(fileHandler.fileOutputAVL);
	fileHandler.outputStats(fileHandler.fileOutputSplay);

	//process summary file
	fileHandler.outputSummary(fileName);

	//close files
	fileHandler.fileInsert.close();
	fileHandler.fileAction.close();
	fileHandler.fileOutputBST.close();
	fileHandler.fileOutputAVL.close();
	fileHandler.fileOutputSplay.close();
	fileHandler.fileOutputSummary.close();

	return 0;
}


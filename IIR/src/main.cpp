/*
 * main.cpp
 *
 *  Created on: Feb 1, 2015
 *      Author: ldhuy
 */

#include <iostream>

#include "BuildDictionary.h"
#include "BuildInvertedIndex.h"
#include "VectorSpaceModelImpl.h"
#include <map>

using namespace std;

// Global variables
unsigned int docsCount = 0;
vector<string> fileList;
vector<string> stopwords;
vector<string> docsName;

int main() {
//	string str = "The higher minimum wage signed into law Tuesday will be welcome relief for millions of workers";
//	set<string> tokens = tokenize(str, " ,.-()$;:\"'&");
//	for(set<string>::iterator it = tokens.begin();it!=tokens.end();++it) {
//		cout << *it << endl;
//	}
//	return 0;

	// Prepare
	//
	srand(time(NULL));

	// Get file list and documents' name
	//
	string path = "./res/docs";
	fileList = listFile(path);
	for (unsigned int i = 0; i < fileList.size(); ++i) {
		string rawName = fileList[i].substr(0, fileList[i].find_last_of('.'));
		docsName.push_back(rawName);
	}

	// Shorten the list for testing
	//
	fileList = vector<string>(fileList.begin(), fileList.begin() + 5);
	docsCount = fileList.size();

	// Load stopwords
	//
	stopwords = loadStopwords("./res/stopwords_en.txt");


	// Build vocabularies
	//
	set<string> vocabs = buildDict(fileList, path, stopwords);

	// Select 500 words randomly
	//
	set<string> selectedWords = selectRandomly(vocabs, 500);
	// Save to file for testing purpose
	saveVocab(selectedWords, "selected-words.txt");

	// Create inverted index
	//
	set<Term> terms = createII(selectedWords);
	// Remove stop-words
	set<Term> ii = buildInvertedIndex(terms, fileList, path, stopwords);

//	vector<int> docVect = createDocVector("2296newsML.txt", ii, docCount);


	string query;
	cin >> query;
	vector<int> queryVector = createQueryVector(query, ii, docsCount, stopwords);

	ofstream fout;
	fout.open("vector.txt");
	if (!fout.good()) {
		fout.close();
		cerr << "Error opening file to write vector for document." << endl;
		return 0;
	}

	for (unsigned int i = 0; i < queryVector.size(); ++i) {
		fout << queryVector[i] << endl;
	}

	fout.close();



	cout << "Finished.\n";
	return 0;
}

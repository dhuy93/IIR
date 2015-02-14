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
#include <time.h>

using namespace std;

// Global variables
unsigned int docsCount = 0;
vector<string> fileList;
vector<string> stopwords;
vector<string> docsNames;

int main() {
	clock_t t0 = clock();

	// Prepare
	//
	srand(time(NULL));

	// Get file list and documents' name
	//
	string path = "./res/test";
	fileList = listFile(path);

	// Shorten the list for testing
	//
	//fileList = vector<string>(fileList.begin(), fileList.begin() + 5);
	for (unsigned int i = 0; i < fileList.size(); ++i) {
		string rawName = fileList[i].substr(0, fileList[i].find_last_of('.'));
		docsNames.push_back(rawName);
	}
	docsCount = fileList.size();

	// Load stopwords
	//
	stopwords = loadStopwords("./res/stopwords_en.txt");

	// Build vocabularies
	//
	string delimiters = " ,.-()$;:\"'&";
	set<string> vocabs = buildDict(fileList, path, stopwords, delimiters);

	// Select 500 words randomly
	//
	set<string> selectedWords = selectRandomly(vocabs, 500);
	// Save to file for testing purpose
	saveVocab(selectedWords, "selected-words.txt");

	// Create inverted index
	//
	set<Term> terms = createII(selectedWords);
	// Remove stop-words
	set<Term> ii = buildInvertedIndex(terms, fileList, path, stopwords,
			delimiters);
	writeII(ii, "II.txt");

//	vector<int> docVect = createDocVector("2296newsML.txt", ii, docCount);

	string query;
	cout << "Please enter your query: \n";
	cin >> query;

//	vector<int> queryVector = createQueryVector(query, ii, docsCount, stopwords);
//	ofstream fout;
//	fout.open("vector.txt");
//	if (!fout.good()) {
//		fout.close();
//		cerr << "Error opening file to write vector for document." << endl;
//		return 0;
//	}
//	for (unsigned int i = 0; i < queryVector.size(); ++i) {
//		fout << queryVector[i] << endl;
//	}
//	fout.close();

	vector<string> result = searchRelevanceDocs(query, ii, docsNames, docsCount,
			stopwords, delimiters);
	for (unsigned int i = 0; i < result.size(); ++i) {
		cout << result[i] << endl;
	}

	cout << "Time: " << (double) (clock() - t0) / CLOCKS_PER_SEC << endl;
	cout << "Finished.\n";
	return 0;
}

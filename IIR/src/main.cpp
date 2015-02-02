/*
 * main.cpp
 *
 *  Created on: Feb 1, 2015
 *      Author: ldhuy
 */

#include <iostream>

#include "BuildDictionary.h"
#include "BuildInvertedIndex.h"

using namespace std;

int main() {

	srand(time(NULL));

	set<string> vocabs = buildDict();

	set<string> selectedWords = selectRandomly(vocabs, 500);

	set<Term> ii = createII(selectedWords);

//	string s = "write-off.";
//	string delimiters = " ,.-()$;:\"";
//
//	set<string> tokens = tokenize(s, delimiters);
//	for (set<string>::iterator it = tokens.begin(); it != tokens.end(); ++it) {
//		cout << *it << endl;
//	}

	cout << "Finished.\n";
	return 0;
}

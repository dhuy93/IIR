/*
 * BuildInvertedIndex.cpp
 *
 *  Created on: Jan 28, 2015
 *      Author: ldhuy
 */
#include "BuildInvertedIndex.h"

set<string> selectRandomly(const set<string> &words, const int &amount) {
	set<string> result;

	set<string>::iterator it;
	for (int i = 0; i < amount; ++i) {
		it = words.begin();
		int steps = rand() % amount;
		advance(it, steps);
		result.insert(*it);
	}

	return result;
}

set<Term> createII(const set<string> &vocabs) {
	set<Term> result;

	for (set<string>::iterator it = vocabs.begin(); it != vocabs.end(); ++it) {
		Term t;
		result.insert(t);
	}

	return result;
}

set<Term> buildInvertedIndex(set<Term> &terms) {
	vector<string> stopwords = loadStopwords("./res/stopwords_en.txt");

	string path = "./res/docs";
	vector<string> fileList = listFile(path);

	for (unsigned int i = 0; i < fileList.size(); ++i) {
		string filename = fileList.at(i);
		set<string> words = loadWords(path + "/" + filename, stopwords);


		for(set<Term>::iterator it = terms.begin(); it != terms.end(); ++it) {
			string str = it->getValue();

			if(find(words.begin(), words.end(), str) != words.end()) {
				const string rawName = filename.substr(0, filename.find_last_of('.'));
				Term t = *it;
				terms.erase(it);
				t.addDoc(filename.substr(0, filename.find_last_of('.')));
				terms.insert(t);
			}
		}
	}
	return terms;

}

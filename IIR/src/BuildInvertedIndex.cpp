/*
 * BuildInvertedIndex.cpp
 *
 *  Created on: Jan 28, 2015
 *      Author: ldhuy
 */
#include "BuildInvertedIndex.h"

set<string> selectRandomly(const set<string> &words, const int &amount) {
	if(amount >= words.size()) {
		return words;
	}

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
		Term t(*it);
		result.insert(t);
	}

	return result;
}

set<Term> buildInvertedIndex(const set<Term> &terms,
		const vector<string> &fileList, const string &path,
		const vector<string> &stopwords, const string &delimiters) {
	set<Term> result = terms;

	for (unsigned int i = 0; i < fileList.size(); ++i) {
		string filename = fileList.at(i);
		vector<string> words = loadWords(path + "/" + filename);
		set<string> vocabs = preprocessing(words, stopwords, delimiters);

		for (set<Term>::iterator it = result.begin(); it != result.end();
				++it) {
			string str = it->getValue();

			if (find(vocabs.begin(), vocabs.end(), str) != vocabs.end()) {
				const string rawName = filename.substr(0,
						filename.find_last_of('.'));
				Term t = *it;
				result.erase(it);

				// Count occurrence of term in the document
				int count = std::count(words.begin(), words.end(),
						t.getValue());

				t.addDoc(rawName, count);
				result.insert(t);
			}
		}
	}
	return result;

}

void writeII(const set<Term> &ii, const string &fileName) {
	ofstream fout;
	fout.open(fileName.c_str());
	if(!fout.good()) {
		cerr << "Error when writing II file.\n";
		fout.close();
		return;
	}

	for(set<Term>::iterator it = ii.begin(); it!=ii.end();++it) {
		map<string, int> docs = it->getDocs();
		fout << it->getValue() << "\t\t";
		for(map<string, int>::iterator itMap = docs.begin(); itMap != docs.end(); ++itMap) {
			fout<< "[" << itMap->first << "; " << itMap->second << "]\t";
		}
		fout << endl;
	}
}

/*
 * DictionaryGathering.cpp
 *
 *  Created on: Jan 21, 2015
 *      Author: ldhuy
 */

#include "BuildDictionary.h"

vector<string> loadStopwords(const string &filename) {
	vector<string> stopwords;
	ifstream fin;
	fin.open(filename.c_str());
	if(!fin.good()) {
		cerr << "Error opening " << filename << " file to read.\n";
		fin.close();
		return vector<string>();
	}

	while(fin.good()) {
		string word;
		fin >> word;
		stopwords.push_back(word);
	}

	fin.close();
	return stopwords;
}

vector<string> loadWords(const string &filename) {
	ifstream fin;
	fin.open(filename.c_str());
	if (!fin.good()) {
		cerr << "Error opening " << filename << " file to read.\n";
		fin.close();
		return vector<string>();
	}

	string word;
	vector<string> result;
	while (fin.good()) {
		fin >> word;

		// Pre-processing
//		string delimiters = " ,.-()$;:\"'&";
//		set<string> tokens = tokenize(word, delimiters);
//
//
//		for(set<string>::iterator it = tokens.begin();it != tokens.end(); ++it) {
//			if(find(stopwords.begin(), stopwords.end(), *it) == stopwords.end()) {
//				// The token is not in stopwords
//				result.insert(*it);
//			}
//		}

		result.push_back(word);
//		result.insert(tokens.begin(), tokens.end());
	}

	fin.close();
	return result;
}

void saveVocab(const set<string> vocabs, const string &filename) {
	ofstream fout;
	fout.open(filename.c_str());
	if (!fout.good()) {
		cerr << "Error opening " << filename << " file to write.\n";
		fout.close();
		return;
	}

	set<string>::iterator it;
	for (it = vocabs.begin(); it != vocabs.end(); ++it) {
		fout << *it << endl;
	}

	fout.close();
	return;
}

vector<string> listFile(const string &path) {
	vector<string> fileList;
	DIR *pDIR;
	struct dirent *entry;
	if ((pDIR = opendir(path.c_str())) != NULL) {
		while ((entry = readdir(pDIR)) != NULL) {
			if (strcmp(entry->d_name, ".") != 0
					&& strcmp(entry->d_name, "..") != 0) {
				fileList.push_back(entry->d_name);
			}
		}
		closedir(pDIR);
	}

	return fileList;
}

vector<string> split(const string& s, const string &delimiter) {
	string::size_type i = 0;
	string::size_type j = s.find(delimiter);

	vector<string> tokens;
	while (j != string::npos) {
		if (j - i != 0) {
			tokens.push_back(s.substr(i, j - i));
		}
		i = ++j;
		j = s.find(delimiter, j);

		if (j == string::npos)
			tokens.push_back(s.substr(i, s.length()));
	}

	return tokens;
}

set<string> tokenize(const string &str, const string &delimiters) {
	string::size_type i = 0;
	set<string> tokens;
	tokens.insert(str);

	for (unsigned int t = 0; t < delimiters.length(); ++t) {
		set<string> tempSet;
		set<string>::iterator it;
		bool found = false;	// The flag used to mark whether the delimiter is found in the tokens
		for (it = tokens.begin(); it != tokens.end(); ++it) {
			i = 0;
			string s = *it;
			string::size_type j = s.find(delimiters.at(t));
			while (j != string::npos) {
				found = true;
				if (j - i != 0) {
					found = true;
					tempSet.insert(s.substr(i, j - i));
				}
				i = ++j;
				j = s.find(delimiters.at(t), j);

				if (j == string::npos)
					tempSet.insert(s.substr(i, s.length()));
			}
		}
		if (found) {
			tokens = tempSet;
		}
	}

	return tokens;
}

set<string> preprocessing(const vector<string> &vocabs, const vector<string> &stopwords, const string &delimiters) {
	set<string> result;

//	vector<string>::iterator it;
//	for (vector<string>::iterator it = vocabs.begin(); it != vocabs.end(); ++it) {
	for (unsigned int i = 0; i < vocabs.size(); ++i) {
//		string word = *it;
		string word = vocabs[i];

//		string delimiters = " ,.-()$;:\"'&";
		set<string> tokens = tokenize(word, delimiters);


		for(set<string>::iterator it2 = tokens.begin();it2 != tokens.end(); ++it2) {
			if(find(stopwords.begin(), stopwords.end(), *it2) == stopwords.end()) {
				// The token is not in stopwords
				result.insert(*it2);
			}
		}

	}

	return result;
}

set<string> buildDict(const vector<string> fileList, const string &path, const vector<string> &stopwords, const string &delimiters) {

	set<string> vocabsList;
	for (unsigned int i = 0; i < fileList.size(); ++i) {
		string filename = fileList.at(i);
		vector<string> words = loadWords(path + "/" + filename);
//		preprocessing(vocabs);
		set<string> vocabs = preprocessing(words, stopwords, delimiters);
		vocabsList.insert(vocabs.begin(), vocabs.end());
	}

	saveVocab(vocabsList, "dictionary.txt");

	return vocabsList;
}

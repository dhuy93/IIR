/*
 * VectorSpaceModelImpl.cpp
 *
 *  Created on: Feb 2, 2015
 *      Author: ldhuy
 */

#include "VectorSpaceModelImpl.h"

vector<int> createDocVector(const string &docName, const set<Term> &ii,
		const int &docsCount) {
	vector<int> docVect(ii.size());
	set<Term>::iterator it;
	int i;

	for (it = ii.begin(), i = 0; it != ii.end(); ++it, ++i) {
		map<string, int>::iterator itMap = it->getDocs().find(docName);
		if (itMap != it->getDocs().end()) {
			int tf = 1 + log(itMap->second);
			int idf = 1 + log(docsCount / (it->getDocs().size()));
			int weight = tf * idf;
			docVect[i] = weight;
		} else {
			docVect[i] = 0;
		}
	}

	return docVect;
}

vector<int> createQueryVector(const string &query, const set<Term> &ii, const int &docsCount, const vector<string> &stopwords) {
	vector<int> queryVect(ii.size());
	set<string> tokens = tokenize(query, " ,.-()$;:\"'&");

	set<string> queryElements;
	for(set<string>::iterator it2 = tokens.begin();it2 != tokens.end(); ++it2) {
		if(find(stopwords.begin(), stopwords.end(), *it2) == stopwords.end()) {
			// The token is not in stopwords
			queryElements.insert(*it2);
		}
	}

	for (set<string>::iterator it = queryElements.begin(); it != queryElements.end(); ++it) {
		// Count occurrence of each words in query
		int occurrences = 0;
		string::size_type start = 0;
		while((start = query.find(*it, start)) != string::npos) {
			++occurrences;
			++start;
		}
		int tf;
		if (occurrences == 0) {
			tf = 0;
		} else {
			tf = 1 + log(occurrences);
		}

		set<Term>::iterator itii = std::find(ii.begin(), ii.end(), Term(it->c_str()));
		if(itii != ii.end()) {
			int pos = std::distance(ii.begin(), itii);
			int idf = 1 + log(docsCount / itii->getDocs().size());
			int weight = tf*idf;
			queryVect[pos] = weight;
		}
	}

	return queryVect;
}

vector< vector<int> > createDocumentVectors(const set<Term> &ii, const int docsCount, const vector<string> &docsName) {
 return vector< vector<int> >();
}

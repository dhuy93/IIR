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

	// Write to files
	ofstream fout;
	fout.open(string(docName + "Vector.txt").c_str());
	if (!fout.good()) {
		cerr << "Error when writing vector file for " + docName << endl;
	} else {
		for (unsigned int i = 0; i < docVect.size(); ++i) {
			fout << docVect[i] << endl;
		}
	}

	fout.close();
	return docVect;
}

vector<int> createQueryVector(const string &query, const set<Term> &ii,
		const int &docsCount, const vector<string> &stopwords,
		const string &delimiters) {
	vector<int> queryVect(ii.size());
	set<string> tokens = tokenize(query, delimiters);

	set<string> queryElements;
	for (set<string>::iterator it2 = tokens.begin(); it2 != tokens.end();
			++it2) {
		if (find(stopwords.begin(), stopwords.end(), *it2) == stopwords.end()) {
			// The token is not in stopwords
			queryElements.insert(*it2);
		}
	}

	for (set<string>::iterator it = queryElements.begin();
			it != queryElements.end(); ++it) {
		// Count occurrence of each words in query
		int occurrences = 0;
		string::size_type start = 0;
		while ((start = query.find(*it, start)) != string::npos) {
			++occurrences;
			++start;
		}
		int tf;
		if (occurrences == 0) {
			tf = 0;
		} else {
			tf = 1 + log(occurrences);
		}

		set<Term>::iterator itii = std::find(ii.begin(), ii.end(),
				Term(it->c_str()));
		if (itii != ii.end()) {
			int pos = std::distance(ii.begin(), itii);
			int idf = 1 + log(docsCount / itii->getDocs().size());
			int weight = tf * idf;
			queryVect[pos] = weight;
		}
	}

	ofstream fout;
	fout.open("QueryVector.txt");
	if (!fout.good()) {
		cerr << "Error when writing vector file for query.\n";
	} else {
		for (unsigned int i = 0; i < queryVect.size(); ++i) {
			fout << queryVect[i] << endl;
		}
	}

	fout.close();
	return queryVect;
}

vector<vector<int> > createDocumentVectors(const set<Term> &ii,
		const int &docsCount, const vector<string> &docsNames) {
	vector<vector<int> > result;

	for (unsigned int i = 0; i < docsNames.size(); ++i) {
		vector<int> docVect = createDocVector(docsNames[i], ii, docsCount);
		result.push_back(docVect);
	}

	return result;
}

double cosineSimilarity(const vector<int> &a, const vector<int> &b) {
	if (a.size() != b.size()) {
		cerr << "Error! vectors are in different dimensions.";
		return -1;
	} else {
		int sum = 0;
		double aMag = 0;
		double bMag = 0;
		for (unsigned int i = 0; i < a.size(); ++i) {
			sum += a[i] * b[i];
			aMag += (double) a[i] * (double) a[i];
			bMag += (double) b[i] * (double) b[i];
		}
		aMag = sqrt(aMag);
		bMag = sqrt(bMag);
		double denominator = aMag * bMag;
		double cosine = sum / denominator;
		return cosine;
	}
}

vector<string> searchRelevanceDocs(const string &query, const set<Term> &ii,
		const vector<string> &docsNames, const int &docsCount,
		const vector<string> &stopwords, const string &delimiters) {
	if (docsNames.size() != docsCount) {
		cerr << "Error! The size of docsNames is not equal to docsCount."
				<< endl;
		return vector<string>();
	}

	vector<int> queryVect = createQueryVector(query, ii, docsCount, stopwords,
			delimiters);
	vector<vector<int> > docsVects = createDocumentVectors(ii, docsCount,
			docsNames);
//	vector< pair<string, double> > similarities;
	multimap<double, string> similarities;

	for (unsigned int i = 0; i < docsNames.size(); ++i) {
		double similarity = cosineSimilarity(queryVect, docsVects[i]);
		similarities.insert(pair<double, string>(similarity, docsNames[i]));
	}

	vector<string> results;
	for (multimap<double, string>::iterator it = similarities.begin();
			it != similarities.end(); ++it) {
//		results.push_back(it->second);
		results.insert(results.begin(), it->second);
	}

	return results;
}

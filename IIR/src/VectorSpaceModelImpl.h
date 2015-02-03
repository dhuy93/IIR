/*
 * VectorSpaceModelImpl.h
 *
 *  Created on: Feb 2, 2015
 *      Author: ldhuy
 */

#ifndef VECTORSPACEMODELIMPL_H_
#define VECTORSPACEMODELIMPL_H_

#include <string.h>
#include <vector>
#include <set>
#include <map>
#include <math.h>
#include <algorithm>
#include "Term.h"
#include "BuildDictionary.h"

using namespace std;
/**
 * From the given name of document, the inverted index of terms and the number of documents,
 * this function create the representation vector of the document
 */
vector<int> createDocVector(const string &docName, const set<Term> &ii, const int &docsCount);

/**
 * Create the representation vector for a query
 * The query is a string of words separated by white spaces.
 */
vector<int> createQueryVector(const string &query, const set<Term> &ii, const int &docsCount, const vector<string> &stopwords);

/**
 * Create a list of representation vectors for documents in a given inverted index
 * Params:
 * 		inverted index
 * 		the number of documents
 * 		the list of documents' name
 */
vector< vector<int> > createDocumentVectors(const set<Term> &ii, const int docsCount, const vector<string> &docsName);


#endif /* VECTORSPACEMODELIMPL_H_ */

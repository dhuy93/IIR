/*
 * BuildInvertedIndex.h
 *
 *  Created on: Jan 28, 2015
 *      Author: ldhuy
 */

#ifndef BUILDINVERTEDINDEX_H_
#define BUILDINVERTEDINDEX_H_

#include <string>
#include <time.h>
#include "BuildDictionary.h"
#include "Term.h"

using namespace std;

/**
 * Select 'amount' words from the set 'words' randomly
 */
set<string> selectRandomly(const set<string> &words, const int &amount);

/**
 * Create a inverted index from a set of words
 */
set<Term> createII(const set<string> &vocabs);

/**
 * Receive a set of strings as vocabularies and build a inverted index data structure to store term-document relationship
 */
set<Term> buildInvertedIndex(const set<Term> &terms, const vector<string> &fileList, const string &path, const vector<string> &stopwords);

#endif /* BUILDINVERTEDINDEX_H_ */

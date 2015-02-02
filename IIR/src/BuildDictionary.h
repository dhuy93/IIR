/*
 * DictionaryGathering.h
 *
 *  Created on: Jan 21, 2015
 *      Author: ldhuy
 */

#ifndef BUILDDICTIONARY_H_
#define BUILDDICTIONARY_H_

#include <string.h>
#include <vector>
#include <fstream>
#include <algorithm>
#include <iostream>
#include <set>
#include <dirent.h>
#include <stdio.h>

using namespace std;


/**
 * Load stop words from file
 */
vector<string> loadStopwords(const string &filename);

/**
 * Open a file and collect a set of words in that file
 */
//vector<string> loadWords(const string &filename);
set<string> loadWords(const string &filename, const vector<string> &stopwords);

/**
 * Save list of vocabulary to a text file
 */
void saveVocab(set<string> vocabs, const string &filename);

/**
 * List all the files in the directory and its sub-directories
 */
vector<string> listFile(const string &path);

/**
 * Split the string by using delimiter and return tokens as a vector of string
 */
vector<string> split(const string &s, const string &delimiter);

/**
 * Split the string into tokens by using delimiters and return words as a vector of string
 * "delimiters" is a string, each character in this string will be used as a delimiter to split the string
 */
set<string> tokenize(const string &s, const string & delimiter);

/**
 * Pre-processing: eliminate stop-words, strip unwanted characters
 */
set<string> preprocessing(const set<string> &vocabs);

/**
 * Read content of all text files in “docs” folder to collect set of words
 * that appear in at least one document. Please write list of words in a text file named
 * "dictionary.txt", where each word is put in a single line.
 */
set<string> buildDict();

#endif /* BUILDDICTIONARY_H_ */

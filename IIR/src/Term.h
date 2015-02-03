/*
 * Term.h
 *
 *  Created on: Jan 28, 2015
 *      Author: ldhuy
 */

#ifndef TERM_H_
#define TERM_H_
#include <string>
#include <set>
#include <map>

using namespace std;

class Term {
private:
	string value;
	string docID;
	map<string, int> docs;
public:
	Term();
	Term(const string &value);
	virtual ~Term();

	// Compare operator to put this class in order in a set
	//
	bool operator<(const Term &b) const;

	// Compare operator
	//
	bool operator==(const Term &b) const;

	// Compare operator
	//
	bool operator!=(const Term &b) const;

	// Get the name of all documents that this term belong to
	//
	map<string, int> getDocs() const;

	// Get the value of the term
	//
	string getValue() const;

	// Add document contains this term
	//
	void addDoc(const string &docName, const int &count);

	// Get the number of documents contain this term
	//
	int docCounts();

};

#endif /* TERM_H_ */

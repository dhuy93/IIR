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

using namespace std;

class Term {
private:
	string value;
	string docID;
	set<string> docs;
public:
	Term();
	virtual ~Term();

	// Compare operator to put this class in order in a set
	//
	bool operator<(const Term &b) const;

	// Get the name of all documents that this term belong to
	//
	set<string> getDocs();

	// Get the value of the term
	//
	string getValue() const;

	// Add document contains this term
	//
	void addDoc(const string &docName);

	// Get the number of documents contain this term
	//
	int docCounts();

};

#endif /* TERM_H_ */

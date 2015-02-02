/*
 * Term.cpp
 *
 *  Created on: Jan 28, 2015
 *      Author: ldhuy
 */

#include "Term.h"

Term::Term() {
	// TODO Auto-generated constructor stub

}

Term::~Term() {
	// TODO Auto-generated destructor stub
}

bool Term::operator<(const Term &b) const {
	return this->value < b.value;
}

set<string> Term::getDocs() {
	return docs;
}

string Term::getValue() const {
	return this->value;
}

void Term::addDoc(const string &docName) {
	this->docs.insert(docName);
}

int Term::docCounts() {
	return docs.size();
}

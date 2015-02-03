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

Term::Term(const string &value) {
	this->value = value;
}

Term::~Term() {
	// TODO Auto-generated destructor stub
}

bool Term::operator<(const Term &b) const {
	return this->value < b.value;
}

bool Term::operator==(const Term &b) const {
	return this->value == b.value;
}

bool Term::operator!=(const Term &b) const {
	return this->value != b.value;
}

map<string, int> Term::getDocs() const {
	return docs;
}

string Term::getValue() const {
	return this->value;
}

void Term::addDoc(const string &docName, const int &count) {
	this->docs[docName] = count;
}

int Term::docCounts() {
	return docs.size();
}

#include <iostream>
#include "IntVector.h"

using std::endl;
using std::cout;

int main() {

	//test param cons default val 0
	IntVector* test2 = new IntVector(5);
	cout << "size: " << test2->size() << endl << "capacity: " << test2->capacity() << endl;

	if (test2->empty()) {
		cout << "Empty doesn't work" << endl;
	}

	cout << test2->at(2) << endl << test2->front() << endl << test2->back() << endl;

	//test delete
	delete test2;

	//_______________________________


	//test param cons default val 2
	IntVector* test3 = new IntVector(3, 2);
	cout << "size: " << test3->size() << endl << "capacity: " << test3->capacity() << endl;

	if (test3->empty()) {
		cout << "Empty doesn't works" << endl;
	}

	cout << test3->at(2) << endl << test3->front() << endl << test3->back() << endl;

	//test delete
	delete test3;

	//_______________________________

	//test default cons
	IntVector* test1 = new IntVector();
	cout << "size: " << test1->size() << endl << "capacity: " << test1->capacity() << endl;

	if (test1->empty()) {
		cout << "Empty works" << endl;
	}

	cout << test1->at(2) << endl;

	//test delete
	delete test1;

	



}

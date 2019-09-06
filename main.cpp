#include <iostream>
#include "IntVector.h"

using std::endl;

int main() {
	//test default cons
	IntVector* test1 = new IntVector();
	cout << "size: " << test1->size() << endl << "capacity: " << test1->capacity() << endl;

	//test param cons
	IntVector* test2 = new IntVector(5);



}

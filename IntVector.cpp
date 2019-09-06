#include <iostream>
#include <stdexcept>
#include "IntVector.h"


//Encapsulated (Private) Data Fields

	//stores the size of the IntVector 
	//(the number of elements currently being used)
		//unsigned sz;
	//store the size of the array
		//unsigned cap;
	//stores the address of the dynamically-allocated array of integers
		//int* data;

//Public Interface (Public Member Functions)


	IntVector::~IntVector() {
		delete[] data;
	}
	unsigned IntVector::size() const {
		return sz;
	}
	unsigned IntVector::capacity() const {
		return cap;
	}
	bool IntVector::empty() const {
		return (sz == 0)
	}
	const int& IntVector::at(unsigned index) const {
		if (index >= sz) {
			throw out_of_range("IntVector::at_range_check");
		}
		else {
			return *data[index];
		}
	}
	const int& IntVector::front() const {

	}
	const int& IntVector::back() const {

	}
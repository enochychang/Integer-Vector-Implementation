#include <iostream>
#include <stdexcept>
#include "IntVector.h"

using std::out_of_range;

//Encapsulated (Private) Data Fields

	//stores the size of the IntVector 
	//(the number of elements currently being used)
		//unsigned sz;
	//store the size of the array
		//unsigned cap;
	//stores the address of the dynamically-allocated array of integers
		//int* data;

//Public Interface (Public Member Functions)

	//Why is int value not = 0
	//Specify the default values for the arguments in the declaration but not in the definition. 
	IntVector::IntVector(unsigned size, int value) {
		sz = size;
		cap = size;
		//if init all vals of data to 0
			//ptr = new int[sz](); special syntax for value-initializing an array
				//value init->value init->zero init
				//https://stackoverflow.com/questions/2204176/how-to-initialise-memory-with-new-operator-in-c
				//https://stackoverflow.com/questions/8860780/what-does-value-initializing-something-mean
			//also member initializer list possible with new
				//https://stackoverflow.com/questions/14681714/using-new-in-a-member-initializer-list-of-constructor
			//since default parameter value
				//If the user does not supply an explicit argument for a parameter with a default argument, the default value will be used. 
				//If the user does supply an argument for the parameter, the user-supplied argument is used.
		data = new int[sz];
		for (unsigned int i = 0; i < sz; ++i) {
			//p[index] is the same as *(p+index)
			data[i] = value;
		}
	}	

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
		return (sz == 0);
	}
	const int& IntVector::at(unsigned index) const {
		if (index >= sz || index < 0) {
			throw out_of_range("IntVector::at_range_check");
		}
		else {
			return data[index];
		}
	}

	//Here's what cplusplus.com say about the back function:
 	//http://www.cplusplus.com/reference/vector/vector/back/
	//The specific part: "Calling this function on an empty container causes 
	//undefined behavior."
	//So, undefined behavior will occur if you do nothing about this in your 
	//function. So, no you should not be checking for an empty vector. Just 
	//let it crash if someone calls front or back on an empty vector. 
	//That's what the stl vector does.
	const int& IntVector::front() const {
		return data[0];

	}
	const int& IntVector::back() const {
		return data[sz-1];
	}
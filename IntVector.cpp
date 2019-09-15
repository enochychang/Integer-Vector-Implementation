#include <iostream>
#include <stdexcept>
#include "IntVector.h"

using std::out_of_range;

//Encapsulated (Private) Data Fields

	//sz vs cap
		//Size is not allowed to differ between multiple compilers. 
		//The size of a vector is the number of elements that it contains, 
		//which is directly controlled by how many elements you put into the vector.
		//Capacity is the amount of space that the vector is currently using. 
		//Under the hood, a vector just uses an array. The capacity of the 
		//vector is the size of that array. This is always equal to or 
		//larger than the size. The difference between them is the number 
		//of elements that you can add to the vector before the array under 
		//the hood needs to be reallocated.
		//https://stackoverflow.com/questions/6296945/size-vs-capacity-of-a-vector
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
		data = new int[cap];
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

	//Using brackets instead of at() because
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
		return data[sz - 1];
	}

	//Why we need 2 versions (const getter/non const accessor) for
	//at(), front(), back()
	//This way the decision on whether or not the object can be modified rests 
	//with the function using it (whether it's a const function or not)
	//OR if one uses a const object 

	//Mutators, and Private Helper Functions

	//How will non const functions know to call the non const version
	//In the case above, both members f are viable candidates. 
	//However, the non-const candidate is a better match than the const 
	//one, since no const-adjustment is needed to match it. 
	//It is therefore the best viable candidate, and therefore the 
	//potential ambiguity is resolved.
	int& IntVector::at(unsigned index) {
		if (index >= sz || index < 0) {
			throw out_of_range("IntVector::at_range_check");
		}
		else {
			return data[index];
		}
	}
	int& IntVector::front() {
		return data[0];
	}
	int& IntVector::back() {
		return data[sz - 1];
	}

	void IntVector::insert(unsigned index, int value) {
		//index > sz and not index >= sz because 
		//If the value of the iterator passed in as an argument is v.end(), 
		//where v is my vector, will this work the same as push_back()? (Yes)
		//https://stackoverflow.com/questions/5960979/using-c-vectorinsert-to-add-to-end-of-vector
		if (index > sz || index < 0) {
			throw out_of_range("IntVector::insert_range_check");
		}

		if ( (sz + 1) > cap) {
			//what if cap = 0
			//std::vector increases cap by 1
			if (cap == 0) {
				expand(1);
			}
			else {
				expand();
			}	
		}
		sz += 1;

		for (unsigned int i = sz - 1; i > index; --i) {
			at(i) = at(i - 1);
		}
		at(index) = value;
	}

	void IntVector::erase(unsigned index) {
		if (index >= sz || index < 0) {
			throw out_of_range("IntVector::erase_range_check");
		}
		for (unsigned int i = index; i < sz - 1; ++i) {
			at(i) = at(i + 1);
		}
		pop_back();
	}

	void IntVector::assign(unsigned n, int value) {
		reserve(n);
		sz = n;
		for (unsigned int i = 0; i < sz; ++i) {
			at(i) = value;
		}
	}

//This function inserts a value at the back end of the array.
//Size will be increased by 1. However, If size will become 
//larger than capacity, this function needs to first increase 
//the capacity. In other words, if capacity and size are both 
//20 when this function is called, capacity must first be 
//increased to 40 and then size can be increased to 21.
//Since other functions will also potentially need to expand 
//(double) the capacity, call the private helper function named 
//expand (see above) to do this for you.
	void IntVector::push_back(int value) {
	
		if ( (sz + 1) > cap) {
			//what if cap = 0
			//std::vector increases cap by 1
			if (cap == 0) {
				expand(1);
			}
			else {
				expand();
			}	
		}
		sz += 1;
		at(sz - 1) = value;
		
	}

	void IntVector::pop_back() {
		sz -= 1;
	}

	void IntVector::clear() {
		sz = 0;
	}

//This function resizes the vector to contain size elements.
//If size is smaller than the current size(sz), this function 
//just reduces the value of sz to size.
//If size is greater than the current size(sz), then the 
//appropriate number of elements are inserted at the end of 
//the vector, giving all of the new elements the value passed 
//in through the 2nd parameter (value).
//If the new value of size will be larger than capacity, then 
//the capacity must first be expanded by either doubling 
//(expand()) or by increasing the capacity by a specific amount 
//(expand(size - cap)), whichever results in the largest capacity. 
//Then, this function can then increase the size appropriately.
	//default param int val = 0
	void IntVector::resize(unsigned size, int value) {
		if (sz > size) {
			sz = size;
		}
		else if (sz < size) {
			// if (size > cap) {
			// 	if ( (cap * 2) > (size) ) {
			// 		expand();
			// 	}
			// 	else {
			// 		expand(size - cap);
			// 	}
			// }
			reserve(size);
			//We need to put sz = size before at() 
			//because at() checks if (index >= sz || index < 0) {
			//so we first assign sz to i, sz being the starting pos
			//where we need to fill with objects of value
			unsigned int temp = sz;
			sz = size;
			for (unsigned int i = temp; i < size; ++i) {
				at(i) = value;
			}
			
		}
	}

	void IntVector::reserve(unsigned n) {
		if (n > cap) {
			if ( (cap * 2) > (n) ) {
				//cap = 0?
				expand();
			}
			else {
				expand(n - cap);
			}
		}
	}

//Private Helper Functions

	//Be careful to properly handle the case when capacity is 0 
	//before calling expand().		
	void IntVector::expand() {
		cap *= 2;
		int* temp = new int[cap];

		for (unsigned int i = 0; i < sz; ++i) {
			temp[i] = data[i];
		}
		delete[] data;
		data = temp;
		temp = nullptr;
	}
	
	void IntVector::expand(unsigned amount) {
		cap += amount;
		int* temp = new int[cap];

		for (unsigned int i = 0; i < sz; ++i) {
			temp[i] = data[i];
		}
		delete[] data;
		data = temp;
		temp = nullptr;
	}


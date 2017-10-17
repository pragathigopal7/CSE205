#include "Dog.h"

//#include "Pet.cpp"


#include <iostream>
#include <fstream>
#include <string>

using namespace std;



	// Q2a: Define Display for Dog class
	// Define the method display that you declared within the Dog class in the header file
	// Information should be printed in the following format:
	// Name: <name>
	// Breed: <breed>
	// Type: Dog
	// (See the print_all function in hw10.cpp for proper use of this function.)

	void Dog::display() {

		cout << "Name: " << getName() << endl;
		cout << "Breed: " << getBreed() << endl;
		cout << "Type: " << "Dog" << "\n\n";
	}

	void Dog::add_pet(string name, string breed, Type type)
	{
		name = name;
		breed = breed;
		type = type;

	}














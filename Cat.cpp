#include "Cat.h"


#include <iostream>
#include <fstream>
#include <string>

using namespace std;

 



	



	// Q2b: Define Display for Cat class
	// Define the method display that you declared within the Cat class in the header file
	// Information should be printed in the following format:
	// Name: <name>
	// Breed: <breed>
	// Type: Cat


void Cat::display() {

		cout << "Name: " << getName() << endl;
		cout << "Breed: " << getBreed() << endl;
		cout << "Type: " << "Cat\t"  << "\n\n";

	}





	// (See the print_all function in hw10.cpp for proper use of this function.)


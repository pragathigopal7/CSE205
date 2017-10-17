#pragma once
#ifndef _CAT_H_
#define _CAT_H_
#include "Pet.h"


#include <string>
using namespace std;

class Cat : public Pet {

private:
	string name, breed;
	Type type;

public:
	Cat(string pet_name, string pet_breed, Type pet_type) : Pet(pet_name, pet_breed, pet_type) {
	};





	// Q1b: Create Cat Class
	// Part 1: Create a child class of the Pet class named 'Cat'
	// See the add function in hw10.cpp for proper use of this function.

	void add_pet(string name, string breed, Type type);

	// Part2: Declare constructor which accepts the same 3 parameters as the parent class Pet.
	// Pass the 3 parameters to the super constructor in the Pet class.





	// Part 3: Re-declare the method display (virtual method found inside of parent class Pet)

	void display();



};
#endif 




#include "Pet.h"

Pet::Pet(string pet_name, string pet_breed, Type pet_type) {
	name = pet_name;
	breed = pet_breed;
	type = pet_type;
}

string Pet::getName() {
	return name;
}

string Pet::getBreed() {
	return breed;
}

Type Pet::getType() {
	return type;
}
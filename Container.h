#pragma once
#ifndef _CONTAINER_H_
#define _CONTAINER_H_

#include "Pet.h"

class Container {
public:
	Pet *pet;
	Container *next;
	Container(); // constructor
};

#endif // _CONTAINER_H_
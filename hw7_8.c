// READ BEFORE YOU START:
// Please read the given Word document for the project description with an illustrartive diagram.
// You are given a partially completed program that creates a list of dogs for an adoption shelter.
// Each dog has the corresponding information: name, breed, and a linked list of checkups.
// Please read the instructions above each required function and follow the directions carefully.
// If you modify any of the given code, return types, or parameters, you risk failing test cases.
//
// Note, Textbook Section 2.10 gives a case study on complex linked list operations. 
// This project is based on that case study. Make sure you read the code in section 2.10.

// The following will be accepted as input in the following format: "name:breed"
// Example Input:	"Spot:Terrier" or "Daisy:Poodle"
// Valid name:		String containing alphabetical letters beginning with a capital letter
// Valid breed:		String containing alphabetical letters beginning with a capital letter
// Valid date:		String in the following format: "MM/DD/YYYY" ex: "01/01/2010"
// All input will be a valid length and no more than the allowed number of dogs will be added to the linked list.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// included to check for memory leaks
#define CRTDBG_MAP_ALLOC
#include <crtdbg.h>

#pragma warning(disable: 4996)

// used to create a linked list of containers, each contaning a "dog"
struct container {
	struct dog *dog;
	struct container *next;
} *list = NULL;

// used to hold dog information and linked list of "checkups"
struct dog {
	char name[30];
	char breed[30];
	struct checkup *checkups;
};

// used to create a linked list of checkups containing "dates"
struct checkup {
	char date[30];
	struct checkup *next;
};

// forward declaration of functions that have already been implemented
void flush();
void branching(char);
void helper(char);
void remove_all(struct container*);
void display(struct container*);

// the following forward declarations are for functions that require implementation

// return type		// name and parameters				// points
void				add_dog(char*, char*);				//  5
struct dog*			search_dog(char*);					//  5
void				add_checkup(char*, char*);			// 10
char*				last_checkup(char*);				// 15
void				remove_one(char*);					// 15
//													Total: 50 points for hw07

struct container*	list_of_breed(char*);				// 25
struct container*	list_by_name();						// 25
//													Total: 50 points for hw08

int main()
{
	char ch = 'i';

	printf("Dog Adoption Center\n\n");

	do
	{
		printf("Please enter your selection:\n");
		printf("\ta: add a new dog to the list\n");
		printf("\ts: search for a dog on the list\n");
		printf("\tr: remove a dog from the list\n");
		printf("\tc: add a checkup date for dog\n");
		printf("\tl: display last checkup for a dog\n");
		printf("\tn: display list of dogs by name\n");
		printf("\tb: display list of dogs of breed\n");
		printf("\tq: quit\n");
		ch = tolower(getchar());
		flush();
		branching(ch);
	} while (ch != 'q');

	remove_all(list);
	list = NULL;

	_CrtDumpMemoryLeaks(); // check for memory leaks (VS will let you know in output if they exist)

	return 0;
}

// consume leftover '\n' characters
void flush()
{
	int c;
	do c = getchar(); while (c != '\n' && c != EOF);
}

// branch to different tasks
void branching(char c)
{
	switch (c)
	{
	case 'a':
	case 's':
	case 'r':
	case 'c':
	case 'l':
	case 'b':
	case 'n': helper(c); break;
	case 'q': break;
	default: printf("Invalid input!\n");
	}
}

// This function will determine what info is needed and which function to send that info to.
// It uses values that are returned from some functions to produce the correct ouput.
// There is no implementation needed here, but you should trace the code and know how it works.
// It is always helpful to understand how the code works before implementing new features.
// Do not change anything in this function or you risk failing the automated test cases.
void helper(char c)
{
	if (c == 'a')
	{
		char input[100];

		printf("\nPlease enter the dog's info in the following format:\n");
		printf("name:breed\n");
		fgets(input, sizeof(input), stdin);

		// discard '\n' chars attached to input
		input[strlen(input) - 1] = '\0';

		char* name = strtok(input, ":"); // strtok used to parse string
		char* breed = strtok(NULL, ":");

		struct dog* result = search_dog(name);

		if (result == NULL)
		{
			add_dog(name, breed);
			printf("\nDog added to list successfully\n\n");
		}
		else
			printf("\nThat dog is already on the list\n\n");
	}
	else if (c == 's' || c == 'r' || c == 'c' || c == 'l')
	{
		char name[30];

		printf("\nPlease enter the dog's name:\n");
		fgets(name, sizeof(name), stdin);

		// discard '\n' chars attached to input
		name[strlen(name) - 1] = '\0';

		struct dog* result = search_dog(name);

		if (result == NULL)
			printf("\nThat dog is not on the list\n\n");
		else if (c == 's')
			printf("\nBreed: %s\n\n", result->breed);
		else if (c == 'r')
		{
			remove_one(name);
			printf("\nDog removed from the list\n\n");
		}
		else if (c == 'c')
		{
			char date[30];

			printf("\nPlease enter the date of the checkup:\n");
			fgets(date, sizeof(date), stdin);

			// discard '\n' chars attached to input
			date[strlen(date) - 1] = '\0';

			add_checkup(name, date);
			printf("\nCheckup added\n\n");
		}
		else if (c == 'l')
		{
			char* result = last_checkup(name);
			if (result == NULL)
				printf("\nNo checkups documented.\n\n");
			else
				printf("\nLast checkup: %s\n\n", result);
		}
	}
	else if (c == 'b')
	{
		char breed[30];

		printf("\nPlease enter the breed:\n");
		fgets(breed, sizeof(breed), stdin);

		// discard '\n' chars attached to input
		breed[strlen(breed) - 1] = '\0';

		struct container* result = list_of_breed(breed);

		printf("\nList of dogs with breed type %s:\n\n", breed);

		display(result);
		remove_all(result);
		result = NULL;
	}
	else // c = 'n'
	{
		struct container* result = list_by_name();

		printf("\nList of dogs sorted by name:\n\n");

		display(result);
		remove_all(result);
		result = NULL;
	}
}

// This function recursively removes all dogs from the linked list of containers
// Notice that all of the checkups for all of the dogs must be removed as well
void remove_all(struct container* dogs)
{
	struct checkup* temp;
	if (dogs != NULL)
	{
		remove_all(dogs->next);
		while (dogs->dog->checkups != NULL)
		{
			temp = dogs->dog->checkups;
			dogs->dog->checkups = dogs->dog->checkups->next;
			free(temp);
		}
		free(dogs->dog);
		free(dogs);
	}
}

// This function prints the list of dogs in an organized format
// It may be useful to trace this code before you get started
void display(struct container* dogs)
{
	struct container* container_traverser = dogs;

	if (container_traverser == NULL)
	{
		printf("\nThere are no dogs on this list!\n\n");
		return;
	}

	while (container_traverser != NULL) // traverse list of dogs
	{
		printf("Name: %s\n", container_traverser->dog->name);
		printf("Breed: %s\n", container_traverser->dog->breed);
		printf("Checkups on file: ");

		struct checkup* ptr = container_traverser->dog->checkups;
		if (ptr == NULL)
		{
			printf("No checkups documented.");
		}
		else
		{
			while (ptr != NULL) // traverse list of checkups
			{
				printf("\n%s", ptr->date);
				ptr = ptr->next;
			}
		}

		printf("\n\n"); // formatting
		container_traverser = container_traverser->next;
	}
}

// hw07 Q1 : add (5 points)
// This function should add dog to the head of the list of containers.
// The function search_dog() is called before calling this function,
// therefore you can assume that the dog is not already on the list.
void add_dog(char* name, char* breed)
{
	if (list == NULL) {
		list = (struct container*)malloc(sizeof(struct container)); // defines a node holding the respective details 
		struct dog *newDogNAME = (struct dog*)malloc(sizeof(struct dog)); // pointer that ensures contact to the structure

		strcpy(newDogNAME->breed, breed);
		strcpy(newDogNAME->name, name);

		newDogNAME->checkups = NULL; //ensures that the global pointer is at the first entry
		list->dog = newDogNAME; // funtion that moves forward the declaration
		list->next = NULL;
	}
	else {
		struct dog *newDogNAME = (struct dog*)malloc(sizeof(struct dog));
		strcpy(newDogNAME->breed, breed);
		strcpy(newDogNAME->name, name);
		newDogNAME->checkups = NULL;
		struct container *temp_variable = list;
		while (temp_variable->next != NULL) {
			temp_variable = temp_variable->next;
		}
		struct container *newDogValue = (struct container*)malloc(sizeof(struct container)); //avoids counting and padding
		newDogValue->dog = newDogNAME;
		newDogValue->next = NULL; // starts from the begining of the list 
		temp_variable->next = newDogValue; // moves on to the next value
	}
}

// hw07 Q2 : search (5 points)
// In this function, you are passed the name of a dog to find its breed.
// If the dog exists on the list, return a pointer to the requested dog. If not, return NULL.
// (You must return a pointer to a node in your list. Do not create a pointer that just includes the breed)
// (Remember that it is enough to search for a dog by only their name since no 2 dogs will have the same name)
struct dog* search_dog(char* name)
{
	struct container *temp_variable = list; // type casting that avoids counting and padding 
	while (temp_variable != NULL) {
		if (strcmp(name, temp_variable->dog->name) == 0) { // compares the respective conditions of the list if matched
			return temp_variable->dog;
		}
		temp_variable = temp_variable->next; //filters through the rest of the list
	}
	return NULL;
}

// hw07 Q3: add_checkup (10)
// In this function, you are passed the name of a dog and a date of a checkup.
// You should add the date to the tail of the linked list of the dogs "checkups".
// You can assume that all checkups will be added in chronological order.
// The function search_dog() is called before calling this function,
// therefore you can assume that the dog is not already on the list.
void add_checkup(char* name, char* date)
{
	struct dog *currentDog = search_dog(name);
	if (currentDog != NULL) {
		struct checkup *newCheckupDATE = (struct checkup*)malloc(sizeof(struct checkup));
		strcpy(newCheckupDATE->date, date);
		newCheckupDATE->next = NULL;
		struct checkup *temp_variable = currentDog->checkups; //filters through the list to add the checkup date for the dog
		if (temp_variable == NULL) {
			currentDog->checkups = newCheckupDATE; // stores the recent checkup date
		}
		else {
			while (temp_variable->next != NULL) {
				temp_variable = temp_variable->next;
			}
			temp_variable->next = newCheckupDATE; // inserts the checkup date for the respective dog in the list with a new checkup date
		}
	}
}

// hw07 Q4: last_checkup (15)
// In this function, you are passed the name of a dog to find the date of its last checkup.
// Remember that checkups are stored in chronological order,
// therefore the last checkup will be at the tail of the linked list of checkups.
// If the dog has not yet had a checkup added to its list of checkups, return NULL.
// The function search_dog() is called before calling this function,
// therefore you can assume that the dog is not already on the list.
char* last_checkup(char* name)
{
	struct dog *currentDog = search_dog(name);
	if (currentDog != NULL) {
		struct checkup *temp_variable = currentDog->checkups; //stores the current checkup date
		while (temp_variable->next != NULL) { //runs the loop when the conditions are met for the most current date
			temp_variable = temp_variable->next;
		}
		return temp_variable->date;
	}
	else
		return NULL;
}

// hw07 Q5: remove_one (15)
// In this function, you are passed the name of a dog to remove the corresponding dog from the list.
// The search function is called before this function so you can assume that the dog is on the list.
// You will need to find the dog and remove it using proper memory management to ensure no memory leaks.
void remove_one(char* name)
{
	struct container *temp_variable = list;
	if (strcmp(temp_variable->dog->name, name) == 0) { //compares the letter entered and the values in the list
		list = list->next; // filters through the list 
		return;
	}
	else {
		struct container *previous = NULL;
		while (strcmp(temp_variable->dog->name, name) != 0) { //compares the dog name with the use of the while loop
			previous = temp_variable;
			temp_variable = temp_variable->next;
		}
		previous->next = temp_variable->next;
		free(temp_variable); // deletes the temp_variable used to store the value to remove the dog
	}
}

// hw08 Q1: list_of_breed (25)
// This function is used to construct a linked list of containers from the global list of containers.
// The returned list should only contain dogs which are of the breed type parameter (container->dog->breed).
// The list that you return will be cleaned up for you by the remove_all() function (see helper() function),
// however you will need to make sure that you leave no dangling references (those cause memory leaks too).
// Notice that the returned list will need to contain all dog and checkup information to be displayed.
struct container* list_of_breed(char* breed)
{
	int counter = 0;
	struct container *breed_list = (struct container *)malloc(sizeof(struct container));
	struct container *temp_variable = list;
	struct container *current;
	while (temp_variable != NULL) {
		if (strcmp(temp_variable->dog->breed, breed) == 0) {
			current = (struct container *)malloc(sizeof(struct container));
			struct dog *currentDog = (struct dog *)malloc(sizeof(struct dog));
			current->dog = currentDog;
			strcpy(current->dog->breed, temp_variable->dog->breed); //compares the breed 
			strcpy(current->dog->name, temp_variable->dog->name); // compares the name within the list 
			current->dog->checkups = NULL;
			struct checkup *checkup_list = NULL;
			struct checkup *checklist_current= NULL;
			int ccounter = 0;
			while (temp_variable->dog->checkups != NULL) { 
				struct checkup *newCheckupDATE = (struct checkup*)malloc(sizeof(struct checkup)); // finds the new checkup date 
				strcpy(newCheckupDATE->date, temp_variable->dog->checkups->date);
				newCheckupDATE->next = NULL;
				if (ccounter == 0) {
					checkup_list = newCheckupDATE;
				}
				else {
					checklist_current= checkup_list;
					while (checklist_current->next != NULL) {
						checklist_current= checklist_current->next;
					}
					checklist_current->next = newCheckupDATE;
				}
				temp_variable->dog->checkups = temp_variable->dog->checkups->next;
			}
			current->dog->checkups = checkup_list;
			if (counter == 0) {
				current->next = NULL;
				counter = 1;
			}
			else
				current->next = breed_list;
			breed_list = current;
		}
		temp_variable = temp_variable->next;
	}
	temp_variable = NULL;
	current = NULL;
	free(temp_variable);
	free(current); //deletes the variable 
	display(breed_list);
	return breed_list;
}

// hw08 Q2: list_by_name (25)
// This function is used to construct a linked list of containers from the global list of containers.
// The returned list should be sorted alphabetically by each container's dog's name (container->dog->name).
// The list that you return will be cleaned up for you by the remove_all() function (see helper() function),
// however you will need to make sure that you leave no dangling references (those cause memory leaks too).
// Notice that the returned list will need to contain all dog and checkup information to be displayed.
// You can again assume that for this assignment, no 2 dogs on the list will have the same name.
// You may want to use the function that you have written above as a blueprint for this function.
struct container* list_by_name()
{
	struct container *list_name = (struct container *)malloc(sizeof(struct container));
	struct container *temp_variable = list;
	struct container *temp = list_name;
	list_name = NULL;
	while (temp_variable != NULL) {
		temp = list_name;
		struct container *current = (struct container *)malloc(sizeof(struct container));
		struct dog *currentDog = (struct dog *)malloc(sizeof(struct dog));
		current->dog = currentDog;
		strcpy(current->dog->breed, temp_variable->dog->breed);
		strcpy(current->dog->name, temp_variable->dog->name);
		current->dog->checkups = NULL;
		struct checkup *checkup_list = NULL;
		struct checkup *checklist_current= NULL;
		int ccounter = 0;
		while (temp_variable->dog->checkups != NULL) {
			struct checkup *newCheckupDATE = (struct checkup*)malloc(sizeof(struct checkup));
			strcpy(newCheckupDATE->date, temp_variable->dog->checkups->date); //compares the previous checkup date and copies it 
			newCheckupDATE->next = NULL;
			if (ccounter == 0) {
				checkup_list = newCheckupDATE;
			}
			else {
				checklist_current= checkup_list;
				while (checklist_current->next != NULL) {
					checklist_current= checklist_current->next;
				}
				checklist_current->next = newCheckupDATE;
			}
			temp_variable->dog->checkups = temp_variable->dog->checkups->next;
		}
		current->dog->checkups = checkup_list;
		if (temp == NULL) {
			current->next = NULL;
			list_name = current;
			temp_variable = temp_variable->next;
			continue;
		}
		if (strcmp(temp_variable->dog->name, temp->dog->name)<0) {
			current->next = temp;
			list_name = current;
			temp_variable = temp_variable->next;
			continue;
		}
		struct container *previous = NULL;
		bool inserted = false;
		while (temp->next != NULL) {
			previous = temp;
			temp = temp->next;
			if (strcmp(temp_variable->dog->name, temp->dog->name)<0) {
				current->next = temp;
				previous->next = current;
				inserted = true;
				break;
			}
		}
		if (!inserted) {
			current->next = NULL; //returns the current list 
			temp->next = current; // continures the next 
		}
		temp_variable = temp_variable->next;
	}
	return list_name;
}
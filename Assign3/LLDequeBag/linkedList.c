#include "linkedList.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>


/* Double Link*/
struct DLink {
	TYPE value;
	struct DLink * next;
	struct DLink * prev;
};

/* Double Linked List with Head and Tail Sentinels  */

struct linkedList{
	int size;
	struct DLink *firstLink;
	struct DLink *lastLink;
};

/*
	initList
	param lst the linkedList
	pre: lst is not null
	post: lst size is 0
*/

void _initList (struct linkedList *lst) {
	lst->size = 0;
	lst->firstLink = NULL;
	lst->lastLink = NULL;
}

/*
 createList
 param: none
 pre: none
 post: firstLink and lastLink reference sentinels
 */

struct linkedList *createLinkedList()
{
	struct linkedList *newList = malloc(sizeof(struct linkedList));
	_initList(newList);
	return(newList);
}

/*
	_addLinkBeforeBefore
	param: lst the linkedList
	param: l the  link to add before
	param: v the value to add
	pre: lst is not null
	pre: l is not null
	post: lst is not empty
*/

/* Adds Before the provided link, l */

void _addLinkBefore(struct linkedList *lst, struct DLink *l, TYPE v)
{
	assert(lst != NULL);
	assert(l != NULL);

	struct DLink *NewLink = malloc(sizeof(struct DLink));

	//Set values for new link
	NewLink->value = v;

	if (lst->firstLink == l)
	{
		//DLink is the first value in the link list.
		NewLink->prev = NULL;
		NewLink->next = l;

		//Adjust the former first link prev to NewLink.
		l->prev = NewLink;

		//Update the LinkList to include the new link.
		lst->firstLink = NewLink;
		lst->size++;
	}
	else
	{
		//GO FISH - have to find the link that you will be inserting.
		struct DLink *Current = lst->firstLink;

		// Walk the link list
		while ((Current->next != lst->lastLink) && (Current != l))
		{
			Current = Current->next;
		}

		if (Current == lst->lastLink)
		{
			// Unable to find the given link in the List to be inserted in front of it so adding to back.
			addBackList(lst, v);
		}
		else
		{
			// Insert DLink at Point in List.
			NewLink->prev = Current->prev;
			NewLink->next = Current->next;

			// Adjust the links prev & next in the list.
			Current->prev->next = NewLink;
			Current->next->prev = NewLink;

			// Update the List Size Count
			lst->size++;
		}
	}

}

/*
	addFrontList
	param: lst the linkedList
	param: e the element to be added
	pre: lst is not null
	post: lst is not empty, increased size by 1
*/

void addFrontList(struct linkedList *lst, TYPE e)
{
	assert(lst != NULL);

	struct DLink *NewLink = malloc(sizeof(struct DLink));

	// Populate new Link
	NewLink->value = e;
	NewLink->next = lst->firstLink;
	NewLink->prev = NULL;

	// Add to the existing list and increment size
	lst->firstLink->prev = NewLink;
	lst->firstLink = NewLink;
	lst->size++;
}

/*
	addBackList
	param: lst the linkedList
	param: e the element to be added
	pre: lst is not null
	post: lst is not empty, increased size by 1
*/

void addBackList(struct linkedList *lst, TYPE e) {
	assert(lst != NULL);
	struct DLink *NewLink = malloc(sizeof(struct DLink));

	// Populate new Link
	NewLink->value = e;
	NewLink->next = NULL;
	NewLink->prev = NULL;

	// Add to the existing list and increment size
	if (lst->size==0)
	{
		// first Link in the List
		lst->firstLink = lst->lastLink = NewLink;
		lst->size++;
	}
	else
	{
		// Size greater than zero, list established.
		struct DLink *Current = lst->lastLink;
		Current->next = NewLink;
		NewLink->prev = Current;
		lst->lastLink = NewLink;
		lst->size++;
	}
}

/*
	frontList
	param: lst the linkedList
	pre: lst is not null
	pre: lst is not empty
	post: none
*/

TYPE frontList (struct linkedList *lst) {
	assert(lst != NULL);
	assert(lst->size > 0);
	/*temporary return value...you may need to change this */
	return lst->firstLink->value;
}

/*
	backList
	param: lst the linkedList
	pre: lst is not null
	pre: lst is not empty
	post: lst is not empty
*/

TYPE backList(struct linkedList *lst)
{
	assert(lst != NULL);
	assert(lst->size > 0);
	/*temporary return value...you may need to change this */
	return lst->lastLink->value;
}

/*
	_removeLink
	param: lst the linkedList
	param: l the linke to be removed
	pre: lst is not null
	pre: l is not null
	post: lst size is reduced by 1
*/

void _removeLink(struct linkedList *lst, struct DLink *l)
{
	assert(lst != NULL);
	assert(l != NULL);

	if (containsList(lst, l->value) == 1)
	{
		struct DLink *dlinkTemp = lst->firstLink;

		while (dlinkTemp != lst->lastLink)
		{
			if (dlinkTemp == l)
			{
				// Set the previous link's next element to the following element after dlinkTemp.
				dlinkTemp->prev->next = dlinkTemp->next;

				// Set the next link's previous element to the dlinkTemp previous.
				dlinkTemp->next->prev = dlinkTemp->prev;

				//Reduce the size of the Link List Count
				lst->size--;

				// Free the memory for the dlinkTemp
				free(dlinkTemp);

				return;
			}
			else
			{
				dlinkTemp = dlinkTemp->next;
			}
		}
	}
	return;
}

/*
	removeFrontList
	param: lst the linkedList
	pre:lst is not null
	pre: lst is not empty
	post: size is reduced by 1
*/

void removeFrontList(struct linkedList *lst) {
	assert(lst != NULL);

	//Redirect the firstLink pointer
	lst->firstLink = lst->firstLink->next;
	lst->firstLink->prev = NULL;

	// Adjust the size of the Link List
	lst->size--;
}

/*
	removeBackList
	param: lst the linkedList
	pre: lst is not null
	pre:lst is not empty
	post: size reduced by 1
*/

void removeBackList(struct linkedList *lst)
{	
	assert(lst != NULL);

	//Redirect the firstLink pointer
	lst->lastLink = lst->lastLink->prev;
	lst->firstLink->next = NULL;

	// Adjust the size of the Link List
	lst->size--;	
}

/*
	isEmptyList
	param: lst the linkedList
	pre: lst is not null
	post: none
*/

int isEmptyList(struct linkedList *lst) {
	assert(lst!=NULL);
	return (lst->size == 0) ? 1 : 0;
}

/* Function to print list
 Pre: lst is not null
 */
void _printList(struct linkedList* lst)
{
	assert(lst != NULL);

	struct DLink *Current = lst->firstLink;

	printf("Here are the values inside of the Linked List: [");
	while (Current->next != NULL)
	{
		printf("%i, ", Current->value);
		Current = Current->next;
	}
	printf("]\n");
}

/* 
	Add an item to the bag
	param: 	lst		pointer to the bag
	param: 	v		value to be added
	pre:	lst is not null
	post:	a link storing val is added to the bag
 */
void addList(struct linkedList *lst, TYPE v)
{
	assert(lst != NULL);
	addBackList(lst, v);
}

/*	Returns boolean (encoded as an int) demonstrating whether or not
	the specified value is in the collection
	true = 1
	false = 0

	param:	lst		pointer to the bag
	param:	e		the value to look for in the bag
	pre:	lst is not null
	pre:	lst is not empty
	post:	no changes to the bag
*/
int containsList (struct linkedList *lst, TYPE e) {
	assert(lst != NULL);

	if (lst->size != 0)
	{
		struct DLink Current1 = *lst->firstLink;
		struct DLink Current2 = *lst->lastLink;

		while ((Current1.next != lst->lastLink) && (Current2.prev != lst->firstLink))
		{
			if ((Current1.value == e) || (Current2.value == e))
			{
				return 1;
			}
			else if (Current1.next == Current2.next)
			{
				// Both are the same link so check one and then return.
				return (Current1.value == e) ? 1 : 0;
			}
			else
			{
				Current1 = *Current1.next;
				Current2 = *Current2.prev;
			}
		}
	}

	/*Replaced default if while loop completes and finds nothing return 0 */
	return 0;
}

/*	Removes the first occurrence of the specified value from the collection
	if it occurs

	param:	lst		pointer to the bag
	param:	e		the value to be removed from the bag
	pre:	lst is not null
	pre:	lst is not empty
	post:	e has been removed
	post:	size of the bag is reduced by 1
*/
void removeList (struct linkedList *lst, TYPE e) {
	assert(lst != NULL);
	assert(lst->size > 0);
	int listSize = lst->size;

	struct DLink *TempLink = malloc(sizeof(struct DLink));

	TempLink->value = e;

	_removeLink(lst, TempLink);

	assert(containsList(lst, e) == 0);
	assert(listSize == (lst->size - 1));
}
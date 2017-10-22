#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "hashMap.h"

/*the first hashing function you can use*/
int stringHash1(char * str)
{
	int i;
	int r = 0;
	for (i = 0; str[i] != '\0'; i++)
		r += str[i];
	return r;
}

/*the second hashing function you can use*/
int stringHash2(char * str)
{
	int i;
	int r = 0;
	for (i = 0; str[i] != '\0'; i++)
		r += (i+1) * str[i]; /*the difference between stringHash1 and stringHash2 is on this line*/
	return r;
}

/* initialize the supplied hashMap struct*/
void _initMap (struct hashMap * ht, int tableSize)
{
	int index;
	if(ht == NULL)
		return;
	ht->table = (hashLink**)malloc(sizeof(hashLink*) * tableSize);
	ht->tableSize = tableSize;
	ht->count = 0;
	for(index = 0; index < tableSize; index++)
		ht->table[index] = NULL;
}

/* allocate memory and initialize a hash map*/
hashMap *createMap(int tableSize) {
	assert(tableSize > 0);
	hashMap *ht;
	ht = malloc(sizeof(hashMap));
	assert(ht != 0);
	_initMap(ht, tableSize);
	return ht;
}

/*
 Free all memory used by the buckets.
 Note: Before freeing up a hashLink, free the memory occupied by key and value
 */
void _freeMap (struct hashMap * ht)
{  
	/*write this*/
	for (int i = 0; i < ht->tableSize; i++)
	{
		if (ht->table[i] != NULL)
		{
			hashLink *Garbage = ht->table[i];

			/* Loop through the Link List to the n of it and start freeing up memory */
			if (Garbage)
			{
				while (Garbage->next != NULL)
				{
					//TODO: Fix the Free Memory issue here.
					struct hashLink *tempLink = Garbage->next;

					if (tempLink)
					{
						// Shink the Link List connect the next link to the Garbage.
						Garbage->next = tempLink->next;

						// Free the memory of the Link pulled out.
						free(tempLink);
					}
				}
			}
			
			/* Free up the Baseline Link at the HashTable bucket*/
			free(Garbage);
		}
	}

	return 0;
}

/* Deallocate buckets and the hash map.*/
void deleteMap(hashMap *ht) {
	assert(ht!= 0);
	/* Free all memory used by the buckets */
	_freeMap(ht);
	/* free the hashMap struct */
	free(ht);
}

/* 
Resizes the hash table to be the size newTableSize 
*/
void _setTableSize(struct hashMap * ht, int newTableSize)
{
	assert(newTableSize > 0 && newTableSize > ht->tableSize);

	/*write this*/
	hashMap *newHashTable = createMap(newTableSize);

	for (int i = 0; i < ht->tableSize; i++)
	{
		if (ht->table[i] != NULL)
		{
			struct hashLink *tempLink = (hashLink *)ht->table[i];

			while (tempLink)
			{
				insertMap(newHashTable, tempLink->key, tempLink->value);
				tempLink = (tempLink->next != NULL) ? tempLink->next : NULL;
			}

			/* Block got stuck in an infinite loop */
			//do
			//{
			//	insertMap(newHashTable, tempLink->key, tempLink->value);
			//} while (tempLink->next !=NULL);
		}
	}

	/* Swap Tables and free up old memory */

	hashMap *Garbage = ht;
	ht = newHashTable;
	_freeMap(Garbage);
	free(Garbage);
}

/*
 insert the following values into a hashLink, you must create this hashLink but
 only after you confirm that this key does not already exist in the table. For example, you
 cannot have two hashLinks for the word "taco".
 
 if a hashLink already exists in the table for the key provided you should
 replace that hashLink--this requires freeing up the old memory pointed by hashLink->value
 and then pointing hashLink->value to value v.
 
 also, you must monitor the load factor and resize when the load factor is greater than
 or equal LOAD_FACTOR_THRESHOLD (defined in hashMap.h).
 */
void insertMap (struct hashMap * ht, KeyType k, ValueType v)
{  
	/*write this*/
	assert(ht != NULL);
	assert(k != NULL);
	int hashIndex;

	/* Find the HashIndex on the table where the value ought to go. */
	switch (HASHING_FUNCTION)
	{
		case 2:
			hashIndex = stringHash2(k) % ht->tableSize;
			break;
		case 1:
			hashIndex = stringHash1(k) % ht->tableSize;
			break;
		default:
			hashIndex = stringHash1(k) % ht->tableSize;
			break;
	}
	if (hashIndex < 0) hashIndex += ht->tableSize;

	if (containsKey(ht,k))
	{
		/* Go and Replace the value, do not create a new Link*/
		struct hashLink *tempLink = (hashLink *) ht->table[hashIndex];
		/* Move down the Bucket link list to find the Key */
		while (strcmp(tempLink->key ,k) != 0) tempLink = tempLink->next;
		tempLink->value = v;
	}
	else
	{
		/* Have to build a new link and then add it to the end of the bucket link list */
		struct hashLink *newLink = (struct hashLink *) malloc(sizeof(hashLink));
		assert(newLink);
		newLink->key = k;
		newLink->value = (v == NULL) ? 1 : v;
		newLink->next = (ht->table[hashIndex] == NULL) ? NULL : (hashLink *) ht->table[hashIndex];
		/* Drop new link into the bucket on the hash table */
		ht->table[hashIndex] = newLink;
		ht->count++;
	}

	/* Resize table if required */
	if (tableLoad(ht) >= LOAD_FACTOR_THRESHOLD) _setTableSize(ht, ht->tableSize*2);
}

/*
 this returns the value (which is void*) stored in a hashLink specified by the key k.
 
 if the user supplies the key "taco" you should find taco in the hashTable, then
 return the value member of the hashLink that represents taco.
 
 if the supplied key is not in the hashtable return NULL.
 */
ValueType* atMap (struct hashMap * ht, KeyType k)
{ 
	/*write this*/

	if (containsKey(ht,k))
	{
		int hashIndex;

		/* Find the HashIndex on the table where the value ought to go. */
		switch (HASHING_FUNCTION)
		{
			case 2:
				hashIndex = stringHash2(k) % ht->tableSize;
				break;
			case 1:
				hashIndex = stringHash1(k) % ht->tableSize;
				break;
			default:
				hashIndex = stringHash1(k) % ht->tableSize;
				break;
		}
		if (hashIndex < 0)hashIndex += ht->tableSize;

		/* Go find the value */
		struct hashLink *tempLink = ht->table[hashIndex];

		while (tempLink)
		{
			if (strcmp(tempLink->key, k)==0) 
			{
				return tempLink->value;
			}
			tempLink = tempLink->next;
		}
	}
	
	return NULL;
}

/*
 a simple yes/no if the key is in the hashtable. 
 0 is no, all other values are yes.
 */
int containsKey (struct hashMap * ht, KeyType k)
{  
	/*write this*/
	/* From Worksheet 38 of Group 2 discussion - refactored*/
	assert(ht != NULL);
	int hashIndex;

	switch (HASHING_FUNCTION)
	{
		case 2:
			hashIndex = stringHash2(k) % ht->tableSize;
			break;
		case 1:
			hashIndex = stringHash1(k) % ht->tableSize;
			break;
		default:
			hashIndex = stringHash1(k) % ht->tableSize;
			break;
	}
	if (hashIndex < 0)hashIndex += ht->tableSize;

	/* Go Find the Key Value*/
	struct hashLink *current = (hashLink *)ht->table[hashIndex];
	while (current)
	{
		if (strcmp(current->key, k) == 0) 
		{
			return 1;
		}
		current = current->next;
	}

	return 0;
}

/*
 find the hashlink for the supplied key and remove it, also freeing the memory
 for that hashlink. it is not an error to be unable to find the hashlink, if it
 cannot be found do nothing (or print a message) but do not use an assert which
 will end your program.
 */
void removeKey (struct hashMap * ht, KeyType k)
{  
	/*write this*/
	if (k != NULL && containsKey(ht,k))
	{
		int hashIndex;

		switch (HASHING_FUNCTION)
		{
			case 2:
				hashIndex = stringHash2(k) % ht->tableSize;
				break;
			case 1:
				hashIndex = stringHash1(k) % ht->tableSize;
				break;
			default:
				hashIndex = stringHash1(k) % ht->tableSize;
				break;
		}
		if (hashIndex < 0)hashIndex += ht->tableSize;

		struct hashLink *tempLink = (hashLink *)ht->table[hashIndex];
		// Check root of Bucket to see if the value is sitting there.
		if (strcmp(tempLink->key,k)==0)
		{
			ht->table[hashIndex] = (tempLink->next != NULL) ? tempLink->next : NULL;
			ht->count--;
			return;
		}

		// Go fish down the Link List for the value.
		while (tempLink->next->next != NULL)
		{
			if (strcmp(tempLink->next->key,k) == 0)
			{
				/* Found it at the next link, pull it out of the line. */

				struct hashLink *replace = (tempLink->next->next != NULL) ? tempLink->next->next : NULL;
				tempLink->next = replace;
				// Decrement the Table Counter.
				ht->count--;

				/* Clean up the memory */
				// free(replace);
				return;
			}

			/* Move the link to check the next one */
			tempLink = tempLink->next;
		}

		// After moving through the list the final link has to be it.
		if (strcmp(tempLink->next->key,k)==0)
		{
			// Just free the link to take it away.
			tempLink->next = NULL;
			ht->count--;
			return;
		}
	}
}

/*
 returns the number of hashLinks in the table
 */
int size (struct hashMap *ht)
{  
	/*write this*/
	int linkCount = 0;

	for (int i = 0; i < ht->tableSize; i++)
	{
		hashLink *tempLink = ht->table[i];
		while (tempLink != NULL)
		{
			linkCount++;
			tempLink = tempLink->next;
		}
	}

	return linkCount;
}

/*
 returns the number of buckets in the table
 */
int capacity(struct hashMap *ht)
{  
	/*write this*/
	return ht->tableSize;
}

/*
 returns the number of empty buckets in the table, these are buckets which have
 no hashlinks hanging off of them.
 */
int emptyBuckets(struct hashMap *ht)
{  
	/*write this*/
	int numBuckets = 0;
	
	for (int i = 0; i < ht->tableSize; i++)
	{
		if (ht->table[i] == NULL)numBuckets++;
	}

	return numBuckets;
}

/*
 returns the ratio of: (number of hashlinks) / (number of buckets)
 
 this value can range anywhere from zero (an empty table) to more then 1, which
 would mean that there are more hashlinks then buckets (but remember hashlinks
 are like linked list nodes so they can hang from each other)
 */
float tableLoad(struct hashMap *ht)
{  
	/*write this*/
	return (float)(size(ht) / ht->tableSize);
}
void printMap (struct hashMap * ht)
{
	int i;
	struct hashLink *temp;	
	for(i = 0;i < capacity(ht); i++){
		temp = ht->table[i];
		if(temp != 0) {		
			printf("\nBucket Index %d -> ", i);		
		}
		while(temp != 0){			
			printf("Key:%s|", temp->key);
			printValue(temp->value);
			printf(" -> ");
			temp=temp->next;			
		}		
	}
}



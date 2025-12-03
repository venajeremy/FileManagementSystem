#include <stdlib.h>

#include "inodeTable.h"

inodeTable table;

// Hard cap on inode table entries: Could be dynamically sized array later
const int MAXSIZE = 50;
int size = 0;


// Constructors & Destructors

void initTable(){
	table.entryArray = (inodeEntry *)malloc(sizeof(inodeEntry)*MAXSIZE);
	table.entryDeletedStack = NULL;	
}

void destTable(){
	deletedEntry* last;
	while(table.entryDeletedStack != NULL){
		last = table.entryDeletedStack;
		table.entryDeletedStack = table.entryDeletedStack->next;
		free(last);
	}
	free(table.entryArray);
}

// Helpers

deletedEntry* popDeleted(){
	if(table.entryDeletedStack == NULL){
		return NULL;
	}
	deletedEntry* top = table.entryDeletedStack;
	table.entryDeletedStack = table.entryDeletedStack->next;
	return top;
}

// Public Methods

int addFile(void* dataPtr, int dataSize, fileType dataType){

	// Find position in entryArray to write new file
	int index;
	deletedEntry* nextDeleted = popDeleted();
	// If we have a deleted entry overwrite this first
	if(nextDeleted != NULL){
		index = nextDeleted->index;
		free(nextDeleted);
	}
	else
	{
		if(size==MAXSIZE){
			// Inode Table is Full
			return -1;
		}
		index = size;
		size++;
	}

	// Add new inode table entry
	inodeEntry* newEntry = &table.entryArray[index];
	newEntry->valid = 1;
	newEntry->type = dataType;
	newEntry->dataPointer = dataPtr;
	newEntry->fileSize = dataSize;

	return index;

}

int deleteFile(int index){
	
	// Check index within bounds
	if(index >= MAXSIZE || index < 0){
		return 0;
	}

	inodeEntry* toDelete = &table.entryArray[index];

	// Check if already deleted
	if(toDelete->valid != 1){
		return 0;
	}

	// Make this entry invalid
	toDelete->valid = 0;

	// Add this entry to the invalid entry stack in the table
	// This will be freed when popped or table destroyed
	deletedEntry* newDeleted = (deletedEntry *)malloc(sizeof(deletedEntry));
	newDeleted->index = index;
	newDeleted->next = table.entryDeletedStack->next;
	table.entryDeletedStack = newDeleted;
}

void* getData(int index){
	// Check index within bounds
	if(index >= MAXSIZE || index < 0){
		return NULL;
	}

	inodeEntry* retrievedFile = &table.entryArray[index];

	// Check if already deleted
	if(retrievedFile->valid != 1){
		return NULL;
	}

	return retrievedFile->dataPointer;

}

int getSize(int index){
	// Check index within bounds
	if(index >= MAXSIZE || index < 0){
		return -1;
	}

	inodeEntry* retrievedFile = &table.entryArray[index];

	// Check if already deleted
	if(retrievedFile->valid != 1){
		return -1;
	}

	return retrievedFile->fileSize;

}

fileType getType(int index){
	// Check index within bounds
	if(index >= MAXSIZE || index < 0){
		return -1;
	}

	inodeEntry* retrievedFile = &table.entryArray[index];

	// Check if already deleted
	if(retrievedFile->valid != 1){
		return -1;
	}

	return retrievedFile->type;

}



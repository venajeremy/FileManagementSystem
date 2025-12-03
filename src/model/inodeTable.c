#include <stdlib.h>

#include "inode.h"

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
		table.entryDeletedStack = table.entryDeletedStack.next;
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
	table.entryDeletedStack = table.entryDeletedStack.next;
	return top;
}

// Public Methods

int addFile(void* dataPtr, size_t dataSize, fileType dataType){

	// Find position in entryArray to write new file
	int index;
	deletedEntry* nextDeleted = popDeleted();
	// If we have a deleted entry overwrite this first
	if(nextDeleted != NULL){
		index = deletedEntry.index;
		free(deletedEntry);
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
	newEntry->valid = true;
	newEntry->type = dataType;
	newEntry->dataPointer = dataPtr;
	newEntry->fileSize = dataSize;

	return index;

}

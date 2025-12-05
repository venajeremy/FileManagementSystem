#include "folderModel.h"

#include <stdlib.h>
#include <stdio.h>

// Constructor & Destructor

void initFolder(folder** newFolder){
	(*newFolder) = (folder*) malloc(sizeof(folder));
	(*newFolder)->fileLinkedList = NULL;
}

// Methods

void createFile(folder* sourceFolder, char* name, int inodeID){

	fileList* newEntry = (fileList*) malloc(sizeof(fileList));

	char* read = name;
	int i = 0;
	while(*read != '\0' && i < fileNameSize){
		newEntry->file.fileName[i] = name[i];
		i++;
	}
	
	newEntry->file.inodeIndex = inodeID;

	newEntry->nextFile = sourceFolder->fileLinkedList;
	sourceFolder->fileLinkedList = newEntry;
}

fileList* extractFile(folder* currentFolder, char* name){
	fileList* listItem = currentFolder->fileLinkedList;
	fileList** previousItem = &(currentFolder->fileLinkedList);
	fileEntry file;

	char* fileName;
	char* searchName;

	while(listItem != NULL){	

		file = listItem->file;
			
		fileName = file.fileName;
		searchName = name;

		while(*fileName == *searchName || (*searchName == '\0' && *fileName == '/')){
			if(*searchName == '\0'){
				// At end of fileName and at the end of searchName, Remove item from linked list
				(*previousItem) = listItem->nextFile;
				return listItem;
			} 
			fileName++;
			searchName++;
		}

		previousItem = &listItem;
		listItem = listItem->nextFile;

	}
	return NULL;
}

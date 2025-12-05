#include "folderModel.h"

#include <stdlib.h>
#include <stdio.h>

// Constructor & Destructor (MOVE TO CONTROLLER)
folder* initFolder(){
	folder* newFolder = (folder*) malloc(sizeof(folder));
	newFolder->fileLinkedList = NULL;
	return newFolder;
}

// Methods

char createFile(folder* sourceFolder, char* name, int inodeID){

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

fileList* removeFile(folder* currentFolder, char* name){
	fileList* listItem = currentFolder->fileLinkedList;
	fileList** previousItem = &(currentFolder->fileLinkedList);
	fileEntry file;

	char* fileName;
	char* searchName;

	while(listItem != NULL){	

		file = listItem->file;
			
		fileName = file.fileName;
		searchName = name;

		while(*fileName == *searchName || (*fileName == '\0' && *searchName == '/')){
			if(*fileName == '\0'){
				// At end of fileName and at the end of searchName, Remove item from linked list
				(*previousItem)->nextFile = listItem->nextFile;
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

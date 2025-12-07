#include "controller.h"

#include <stdlib.h>
#include <stdio.h>

// Folder Controls:

// Constructor and Destructor

void initFileSystem(folder** fold){
	initTable();
	initFolder(fold);
}

void destFileSystem(folder** fold){
	deleteFolder(*fold);
	destTable();
}

// Read Inode Helpers

int fileExists(int inodeID){
	return inodeID >= 0;
}

folder readFolderFile(int folderID){
	folder* fold = (folder*) getData(folderID);
	return *fold;
}

char* readTextFile(int textfileID){
	return (char*) getData(textfileID);
}

// Deletition

char deleteFolderItem(fileList* listItem){
	// Handles freeing a folder item including its children if it is a folder type
	
	if(listItem==NULL){
		return 0;
	}

	// Check if type is directory
	fileEntry file = listItem->file;
	if(getType(file.inodeIndex)==DIRECTORY){
		// If directory load the folder object attached
		folder* fold = (folder*) getData(file.inodeIndex);
		deleteFolder(fold);
	}
	// Remove the file attached to the folder item from the inode table
	deleteInodeEntry(file.inodeIndex);
	// Free the folder item
	free(listItem);

	return 1;
}

char deleteFolder(folder* delFolder){
	fileList* innerListItem = delFolder->fileLinkedList;
	fileList* next;

	if(delFolder==NULL){
		return 0;
	}

	while(innerListItem != NULL){
		// Recursively call delete folder item on all contents of the folder
		next = innerListItem->nextFile;
		deleteFolderItem(innerListItem);
		innerListItem = next;
	}

	return 1;
}

char deleteFile(folder* currentFolder, char* path, char* name){
	folder* parentFolder = getFolder(currentFolder, path);
	if(parentFolder==NULL){
		return 0;
	}
	
	return deleteFolderItem(extractFile(parentFolder, name));

}

// Accessing

folder* getFolder(folder* currentFolder, char* path){
	if(*path=='\0' || *path=='/'){
		return currentFolder;
	}
	int idOfPath = accessFile(currentFolder, path);
	if(idOfPath < 0){
		printf("Error: Provided path does not lead to a valid file.\n");
		return NULL;
	}

	if(getType(idOfPath)!=DIRECTORY){
		printf("Error: Path leads to a data file, not a directory.\n");
		return NULL;
	}
	folder* pathedFolder = (folder *) getData(idOfPath);

	return pathedFolder;
}

int accessFile(folder* currentFolder, char* path){
    // Recursive function
    // Path string has form foo/bar/qaz\0
    // where a/ is a folder and b\0 (null terminator) is a file

    // check each file in linked list against next folder in path
    // if reach / character and at end of file name and file is a folder recursively call on found folder. Otherwise continue to next file. If we reach end of file linked list return -1.

    fileList* currentFile = currentFolder->fileLinkedList;
    fileEntry currentEntry;
    char* fileChar;
    char* pathChar;

    while(currentFile != NULL){
        currentEntry = currentFile->file;
        
		fileChar = currentEntry.fileName;
		pathChar = path;

		// Match characters in path name to file name
		while(*fileChar == *pathChar || *fileChar=='\0'){
			if(*fileChar == '\0'){
				// Reached end of current file name
				if(*pathChar == '/'){
					// Reached end of current path & path item is folder
					// If current file is a folder recursively search inside it
					if(getType(currentEntry.inodeIndex) == DIRECTORY){
						// Go to next character in path: start of next entry
						pathChar++;
						return accessFile((folder*)getData(currentEntry.inodeIndex), pathChar);
					}
				} else if(*pathChar == '\0'){
					// Reached end of current path & path item is a file
					// Return inode index of file
					return currentEntry.inodeIndex;
				}

				// Reached end of current file but not end of current path, break to next file in folder
				break;

			}
			// Not yet at end of filename, iterate to next character
			fileChar++;
			pathChar++;
		}

		// Current file name didn't match with path, try the next file in folder
		currentFile = currentFile->nextFile;
        
    }

    // Could not find file return -1
    return -1;

}

// File System View

void printFileSystemRecursive(folder* currentFolder, int spaces){
	fileList* list = currentFolder->fileLinkedList;

	while(list != NULL){
		for(int i = 0 ; i < spaces ; i++){
			printf("   ");
		}
		printf("%s\n", list->file.fileName);
		if(getType(list->file.inodeIndex)==DIRECTORY){

			printFileSystemRecursive((folder*)getData(list->file.inodeIndex), spaces+1);

		}
		
		list = list->nextFile;
	}
}

void printFileSystem(folder* currentFolder){
	printFileSystemRecursive(currentFolder, 0);	
}

// Creating Files

char addDataFile(folder* currentFolder, char* path, char* name, void* data, int size){
	folder* pathedFolder = getFolder(currentFolder, path);	
	if(pathedFolder==NULL || (accessFile(pathedFolder, name)>=0)){
		return 0;
	}

	int idOfDataFile = addFile(data, size, DATA);

	createFile(pathedFolder, name, idOfDataFile);

	return 1;
}

char addFolderFile(folder* currentFolder, char* path, char* name){
	folder* pathedFolder = getFolder(currentFolder, path);	
	if(pathedFolder==NULL || (accessFile(pathedFolder, name)>=0)){
		return 0;
	}

	folder* newFolder = (folder *) malloc(sizeof(folder));

	int idOfFolder = addFile(newFolder, sizeof(folder), DIRECTORY);

	createFile(pathedFolder, name, idOfFolder);

	return 1;
}

// Update Data File

char updateDataFile(folder* currentFolder, char* path, void* data, int size){

	int inodeID = accessFile(currentFolder, path);

	if(fileExists(inodeID)){
		updateFile(inodeID, data, size, DATA);
		return 1;
	}
	return 0;

}


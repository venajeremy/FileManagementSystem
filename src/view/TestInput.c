#include "inodeModel.h"
#include "folderModel.h"
#include "controller.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
	// Constructors
	initTable();

	folder* root = (folder*) malloc(sizeof(folder));

	if(addFolderFile(root, "", "test")){
		printf("Successfully created folder on root\n");
	} else {
		printf("Could not create folder on root\n");
	}

	char* str = "Hello file system!\n";
	char* heapData = (char*)malloc(sizeof(char)*strlen(str)+1);
	strcpy(heapData, str);

	if(addDataFile(root, "test", "textfile", heapData, sizeof(heapData))){
		printf("Successfully created text file\n");
	} else {
		printf("Could not create text file\n");
	}

	printf("Reading from text file: %s \n", readTextFile(accessFile(root, "test/textfile")));

	// Destructors
	destTable();
}

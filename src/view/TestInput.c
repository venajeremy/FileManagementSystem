#include "inodeModel.h"
#include "folderModel.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
	// Constructors
	initTable();

	// Test Inode Table addFile and deleteFile
	char* str = "Hello file system!\n";
	char* heapData = (char*)malloc(sizeof(char)*strlen(str)+1);
	strcpy(heapData, str);

    char* str1 = "I am a different string of a different size!!!!!\n";
	char* heapData1 = (char*)malloc(sizeof(char)*strlen(str1)+1);
	strcpy(heapData1, str1);

    

	int testStringIndex = addFile(heapData, sizeof(heapData), DATA);

	printf("Saved string #%d, Reaing saved data: \n %s\n", testStringIndex, (char*) getData(testStringIndex));

	deleteFile(testStringIndex);

	testStringIndex = addFile(heapData1, sizeof(heapData1), DATA);
	
	printf("Saved string #%d, Reaing saved data: \n %s\n", testStringIndex, (char*) getData(testStringIndex));
  

	// Test creating folder and accessing it
	folder* root = initFolder();
	folder* innerFolder = initFolder();
	int folder = addFile(&innerFolder, sizeof(innerFolder), DIRECTORY);

	createFile(root, "TestA", folder);

	printf("Added new file!\n");

	if(accessFile(root, "TestA") > 0){
		printf("Successfully found: TestA\n");
	} else {
		printf("Could not find: TestA\n");
	}
	
	if(accessFile(root, "TestB") > 0){
		printf("Successfully found: TestB\n");
	} else {
		printf("Could not find: TestB\n");
	}

	

	// Destructors
	destTable();
}

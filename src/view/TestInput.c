#include "inodeTable.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
	// Constructors
	initTable();


	char* str = "Hello fild system!\n";
	char* heapData = (char*)malloc(sizeof(char)*strlen(str)+1);
	strcpy(heapData, str);

    	char* str1 = "I am a different string of a different size!!!!!\n";
	char* heapData1 = (char*)malloc(sizeof(char)*strlen(str1)+1);
	strcpy(heapData1, str1);

    

	int testStringIndex = addFile(heapData, sizeof(heapData), DATA);

	printf("Saved first string, Reaing saved data: \n %s\n", (char*) getData(testStringIndex));

	testStringIndex = addFile(heapData1, sizeof(heapData1), DATA);
	printf("Saved second string, Reaing saved data: \n %s\n", (char*) getData(testStringIndex));
  

	// Destructors
	destTable();
}

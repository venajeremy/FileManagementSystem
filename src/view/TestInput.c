#include "inodeTable.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
	// Constructors
	initTable();


	char* str = "Hello fild system!\n";
	char* heapData = (char*)malloc(sizeof(str)+1);
	strcpy(heapData, str);

	printf("Created Addr: %d\n",(void*)heapData);

	int testStringIndex = addFile(&heapData, sizeof(heapData), DATA);

	printf("The inode index of new file is: %d\n", testStringIndex);

  

	// Destructors
	destTable();
}

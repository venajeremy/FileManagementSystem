#include "inodeTable.h"

#include <stdio.h>

int main(){
	// Constructors
	initTable();


	char testString[20] = "Hello file system!\n";

	int testStringIndex = addFile(&testString, sizeof(testString), DATA);

	printf("The inode index of new file is: %d\n", testStringIndex);

  

	// Destructors
	destTable();
}

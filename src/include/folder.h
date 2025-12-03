#ifndef FOLDER_H

#define FOLDER_H

typedef struct {
	char* fileName;
	int innodeIndex;
} fileEntry;

typedef struct fileList {
	fileEntry* file;
	fileList* nextFile;
} fileList;

typedef struct {
	fileList* fileLinkedList;
} folder;

#endif

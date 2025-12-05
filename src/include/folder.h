#ifndef FOLDER_H

#define FOLDER_H

#define fileNameSize 255

typedef struct {
	char fileName[fileNameSize];
	int inodeIndex;
} fileEntry;

typedef struct fileList {
	fileEntry file;
	struct fileList* nextFile;
} fileList;

typedef struct {
	fileList* fileLinkedList;
} folder;

#endif

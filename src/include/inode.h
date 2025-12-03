#ifndef INODE_H

#define INODE_H

typedef enum {
	DIRECTORY,
	DATA
} fileType;

typedef struct {
	char valid;
	fileType type;
	void* dataPointer;
	int fileSize;
} inodeEntry;

typedef struct deletedEntry {
	int index;
	struct deletedEntry* next;
} deletedEntry;

typedef struct {
	inodeEntry* entryArray;
	deletedEntry* entryDeletedStack;
} inodeTable;

#endif

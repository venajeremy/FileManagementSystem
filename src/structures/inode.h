#ifndef INODE_H

#define INODE_H

typedef enum {
	DIRECTORY,
	DATA
} fileType;

typedef struct {
	bool valid;
	fileType type;
	void* dataPointer;
	size_t fileSize;
} inodeEntry;

typedef struct deletedEntry {
	int iD;
	deletedEntry* nextDeletedEntry;
} deletedEntry;

typedef struct {
	inodeEntry* entryArray;
	deletedEntry* entryDeletedStack;
} inodeTable;

#endif

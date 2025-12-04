#ifndef INODETABLE_H

#define INODETABLE_H

#include "inode.h"

void initTable();

void destTable();

int addFile(void* dataPtr, int dataSize, fileType dataType);

int deleteFile(int index);

void* getData(int index);

int getSize(int index);

fileType getType(int index);

int updateFile(int index, void* dataPtr, int dataSize, fileType dataType);

#endif

#ifndef INODETABLE_H

#define INODETABLE_H

void initTable();

void destTable();

int addFile(void* dataPtr, size_t dataSize, fileType dataType);

#endif

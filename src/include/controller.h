#ifndef CONTROLLER_H

#define CONTROLLER_H

#include "inodeModel.h"
#include "folderModel.h"
#include "folder.h"
#include "inode.h"

void printFileSystem(folder* currentFolder);

char removeFile(folder* currentFolder, char* path, char* name);

folder readFolderFile(int folderID);

char* readTextFile(int textfileID);

int accessFile(folder* currentFolder, char* path);

char addDataFile(folder* currentFolder, char* path, char* name, void* data, int size);

char addFolderFile(folder* currentFolder, char* path, char* name);

#endif

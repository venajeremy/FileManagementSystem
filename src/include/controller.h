#ifndef CONTROLLER_H

#define CONTROLLER_H

#include "inodeModel.h"
#include "folderModel.h"
#include "folder.h"
#include "inode.h"

char addDataFile(folder* currentFolder, char* path, char* name, void* data, int size);

char addFolderFile(folder* currentFolder, char* path, char* name);

folder* getFolder(folder* currentFolder, char* path);

int accessFile(folder* currentFolder, char* path);

folder readFolderFile(int folderID);

char* readTextFile(int textfileID);

char deleteFile(folder* currentFolder, char* path, char* name);

char deleteFolder(folder* delFolder);

void printFileSystem(folder* currentFolder);

#endif

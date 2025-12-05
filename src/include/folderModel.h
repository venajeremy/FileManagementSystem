#ifndef FOLDERMODEL_H

#define FOLDERMODEL_H

#include "folder.h"
#include "inode.h"

void initFolder(folder** newFolder);

void createFile(folder* sourceFolder, char* name, int inodeID);

fileList* extractFile(folder* currentFolder, char* name);

#endif

#ifndef FOLDERMODEL_H

#define FOLDERMODEL_H

#include "folder.h"
#include "inode.h"

folder* initFolder();

void destFolder(folder* fold);

int accessFile(folder* currentFolder, char* name);

char createFile(folder* sourceFolder, char* name, int inodeID);

#endif

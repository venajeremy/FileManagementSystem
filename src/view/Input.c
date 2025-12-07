#include "controller.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
	filesys_folder_t root;
	initFileSystem(&root);

	char command[100];
	char path[256];
	char name[256];
	char content[512];
	char* heapData;

	char* controls = "Commands: help, create, open, close, search, list, delete, update, exit\n\n";

	printf("File Management System\n");
	printf(controls);

	while(1){
		printf("> ");
		scanf("%s", command);

		if(strcmp(command, "exit") == 0){
			break;
		}
		if(strcmp(command, "help") == 0){
			printf(controls);
		}
		else if(strcmp(command, "list") == 0){
			printFileSystem(root);
			printf("\n");
		}
		else if(strcmp(command, "create") == 0){
			printf("Choose type: file or folder\n");
			scanf("%s", command);
			if(strcmp(command, "file") == 0){
				printf("Enter path to create file at:\n");
				scanf("%s", path);
				printf("Enter file name:\n");
				scanf("%s", name);
				printf("Enter file text content:\n");
				scanf(" %[^\n]", content);
				
				heapData = (char*)malloc(sizeof(char)*strlen(content)+1);
				strcpy(heapData, content);

				if(addDataFile(root, path, name, heapData, strlen(heapData)+1)){
					printf("File created successfully\n");
				} else {
					printf("Could not create file\n");
					free(heapData);
				}
			}
			else if(strcmp(command, "folder") == 0){
				printf("Enter path to create folder at:\n");
				scanf("%s", path);
				printf("Enter file name:\n");
				scanf("%s", name);
				if(addFolderFile(root, path, name)){
					printf("Folder created successfully\n");
				} else {
					printf("Could not create folder\n");
				}
			}
		}
		else if(strcmp(command, "open") == 0){
			printf("Enter path of file:\n");
			scanf("%s", path);
			int fileID = accessFile(root, path);
			if(fileID >= 0){
				printf("%s\n", readTextFile(fileID));
			} else {
				printf("File not found\n");
			}
		}
		else if(strcmp(command, "close") == 0){
			printf("File closed\n");
		}
		else if(strcmp(command, "search") == 0){
			scanf("%s", path);
			int fileID = accessFile(root, path);
			if(fileID >= 0){
				printf("File found\n");
			} else {
				printf("File not found\n");
			}
		}
		else if(strcmp(command, "delete") == 0){
			printf("Enter path of file:\n");
			scanf("%s", path);
			printf("Enter file name:\n");
			scanf("%s", name);	
			if(deleteFile(root, path, name)){
				printf("File deleted successfully\n");
			} else {
				printf("Could not delete file\n");
			}
		}
		else if(strcmp(command, "update") == 0){
			printf("Enter path of file:\n");
			scanf("%s", path);
			printf("Enter new string content:\n");
			scanf("%s", content);
			
			heapData = (char*)malloc(sizeof(char)*strlen(content)+1);
			strcpy(heapData, content);

			if(updateDataFile(root, path, heapData, strlen(heapData)+1)){
				printf("File updated successfully\n");
			} else {
				printf("Could not update file\n");
				free(heapData);
			}
		}
	}

	destFileSystem(&root);
	return 0;
}

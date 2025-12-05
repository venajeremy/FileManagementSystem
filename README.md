# FileManagementSystem

## Structures
### Folder Structure

#### 1. File Entry:
	a) Purpose: Used inside folder to reference entries in the primary file table (inode Table)
	b) Structure:
		- File Name (string)
		- Inode Index (int) 
		- Next File List Item (forms single linked list)

#### 2. Folder:
	a) Purpose: Folder that contains linked list of File Entries
	b) Structure:
		- File List Item (head of linked list defined above)

### Inode Table Structure
#### 1.	Inode Table Entry:
	a) Purpose: Stores the details for a specific file on the system
	b) Important Detail: Inode Table uses index of entries as ID. Each entry in the table does not know its ID.
	c) Structure: 
		- Valid (Boolean: default false)
		- File Type (Enum: directory/data)
		- Data Pointer (Void Ptr: will be casted depending on the type)
		- File Size (size_t)

#### 2. Deleted Entry:
	a) Purpose: Listed List of entries that have been deleted. Prioritizing writing over these instead of writing to the end of the array i node table array.
	b) Structure:
		- ID (Int)
		- Next Deleted Entry (Deleted Entry Pointer)

#### 3. Inode Table:
	a) Purpose: Contains array of Inode Table Entries
	b) Structure:
		- Array of InodeTable Entries
		- Linked list of Deleted Entry

## Models

### 1. Inode Table Model:
	a) Purpose: Manages maintaining Inode table.
	b) Actions:
		- Add File: Creates a new Inode Table Entry of type file. Called by folder model create file. Overwrite deleted entries before writing to end of array.
			> Input: Data Pointer (void*), Data Size (size_t), Data Type (Folder or Data)
			> Output: ID of Inode Entry (index in inode table)
    	- Delete File: Deletes any file (could be data file or folder). Sets Inode Table Entry to be invalid. Add deleted index to deleted entry stack. Free memory of file.
			> Input: ID of file
			> Output: None
		- Get Data: Retries data location from file
			> Input: ID of file
			> Output: Memory address of file
		- Get Size: Retries size of file
			> Input: ID of file
			> Output: Size of file
		- Get File Type: Returns the file type of the file
			> Input: ID of file
			> Output: Type Enum of file
        - Update File: Updates existing inode entry
            > Input: ID of file
            > Output: True or False if file was updated successfully

### 2. Folder Model:
	a) Purpose: Access file, Create file, Delete file. Abstracted control interface used by controller.
	b) Actions:
		- Access file: Finds the inode id of a file within a folder. This file could be a data file or a folder.
			> Input: Source folder (folder memory address), file to access (string)
			> Output: Inode index of file, -1 if does not exist
		- Create file: Adds file to entry to folder
			> Input: Source folder (folder memory address), file name, file inode id
			> Output: Successfully created file (bool)
		- Remove file: pulls a file with specified name from linked list and returns it
			> Input: Source folder (folder memory address), file name
			> Output: FileListItem/NULL

## Controllers

### 1.	Controller
	a) Purpose: Facilitate communication between folder model and inode table model. Manage how the view will interface with the physical data. Create file, create text file, create folder, access file, access folder, delete file, delete folder
	b) Actions:
		- Get Path: Takes in path parameter, traverses files to find chosen file using folder model access file call, ensuring file is a folder type. Gets the inode id. Returns inode id.
			> Input: Path to file
			> Output: File inode id
		- Add data file: Takes in path parameter uses get path on path. Takes in data and saves it in inode table, provides new inode id to folder. Takes inode id and new file name and adds to folder with create file.
			> Input: Path to file (string), Name of file (string), Data memory address (void *), Data size (size_t)
			> Output: Success (bool)
		- Add folder file: Takes in path parameter uses get path on path. Creates new folder object provides to inode table and gets new inode index. Adds new folder object to folder with create file.
 			> Input: Path to new folder (string), Name of new folder (string)
			> Output: Success (bool)
		- Read folder file: Takes in inode id, returns folder object, returns NULL if id is not folder or not in inode table
			> Input: Inode id
			> Output: Folder object or NULL
		- Read text file: Takes in inode id, retrieves data, returns string
			> Input: Inode id
			> Output: File Contents (string)
		- Remove file: Takes in path and remove the file with folder model delete file
			> Input: Path to file (string), Name of file (string)
			> Output: Success (bool)
        - Delete data file:
        - Delete folder file:



#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct Directory //each directory has a linked list file and linked list folder and name of directory
{
	char name[20];	//name of directory
	struct LinkedListDir* folder;	//folder children of node
	struct LinkedListFile* file;	//file children of node
	struct Directory* next;
};

struct Directory* Directory_construct(char f[]) 		//directory constructor
{
	struct Directory* n=(struct Directory*)malloc(sizeof(struct Directory));
	strcpy(n->name, f);
	n->folder = NULL;
	n->file = NULL;
	n->next = NULL;
	return n;
};

struct LinkedListDir 	//each linked list contains directories
{
	struct Directory* first_dir;
};

struct LinkedListDir* LinkedListDir_construct() 	//LinkedListDir constructor
{
	struct LinkedListDir* n=(struct LinkedListDir*)malloc(sizeof(struct LinkedListDir));
	n->first_dir = NULL;
	return n;
};

struct FileNode
{
	char file_name[20];	//filename
	struct FileNode* next;	//next filenode
};

struct FileNode* FileNode_construct(char f[])
{
	struct FileNode* n = (struct FileNode*)malloc(sizeof(struct FileNode));
	strcpy(n->file_name, f);
	n->next = NULL;
	return n;
}

struct LinkedListFile	//list of files in directory
{
	struct FileNode* first_file;
};

struct LinkedListFile* LinkedListFile_construct() 	//LinkedListFile constructor
{
	struct LinkedListFile* n=(struct LinkedListFile*)malloc(sizeof(struct LinkedListFile));
	n->first_file = NULL;
	return n;
};

void display_file_list(struct LinkedListFile* f_list)
{
	if(f_list == NULL)
	{
		printf("No files in the Directory\n");
		return;
	}

	if(f_list->first_file != NULL)
	{
		struct FileNode* temp = f_list->first_file;
		printf("Root\n-----\n");
		while(temp != NULL)
		{
			printf("%s\n", temp->file_name);
			temp=temp->next;
		}
	}
}

void display_dir_list(struct LinkedListDir* f_dir)	//display directory names
{
	if(f_dir == NULL)
	{
		printf("No Directories\n");
		return;
	}

	if(f_dir->first_dir != NULL)
	{
		struct Directory* temp = f_dir->first_dir;
		while(temp != NULL)
		{
			printf("%s\n", temp->name);
			temp=temp->next;
		}
	}
}

void insertFile(struct LinkedListFile* llist_file, char f_name[])	//insert a file in linked list file
{
	if(llist_file->first_file == NULL)	//llist empty
		llist_file->first_file = FileNode_construct(f_name);
	else	//llist not empty
	{
		struct FileNode *temp = llist_file->first_file;
		while(temp->next!=NULL && strcmp(temp->file_name, f_name)!=0)
			temp=temp->next;
		if(strcmp(temp->file_name, f_name)==0) 	//already exists
		{
			printf("Same File Exists already\n");
			return;
		}
		temp->next = FileNode_construct(f_name);
	}
	printf("File Created Successfully\n");
}


void single_level(int n) 	//single level directory organization
{
	struct Directory* root = Directory_construct("root");	//root directory

	int ch;
	char file_name[20];
	do
	{
		printf("\n1. Create File\n");
		printf("2. View Contents\n");
		printf("3. Exit\n");
		scanf("%d", &ch);
		
		if(ch==1)	//create file
		{
			printf("Enter file name : ");
			scanf("%s", file_name);

			if(root->file == NULL)	//if file list empty create
				root->file = LinkedListFile_construct();

			insertFile(root->file, file_name);
		}
		else if(ch==2)	//view contents
			display_file_list(root->file);
		else if(ch == 3)
			break;

	}while(ch != 3);
}

void createDirectory(struct LinkedListDir* llist_dir, char d_name[])	//create directory under current directory
{
	if(llist_dir->first_dir == NULL)	//llist empty
		llist_dir->first_dir = Directory_construct(d_name);
	else	//llist not empty
	{
		struct Directory *temp = llist_dir->first_dir;
		while(temp->next!=NULL && strcmp(temp->name, d_name)!=0)
			temp=temp->next;
		if(strcmp(temp->name, d_name) == 0) 	//already exists
		{
			printf("Same Directory Exists already\n");
			return;
		}
		temp->next = Directory_construct(d_name);
	}
	printf("Directory Created Successfully\n");
}

void tree_level(int n)	//tree level directory organization
{
	struct Directory* root = Directory_construct("root");	//root directory
	struct Directory* cur_dir = root;

	int i, ch;
	char user_names[5][20], file_name[20], dir_name[20];

	for(i=0;i<n;i++)	//input user names
	{
		printf("Enter User %d Name : ", i+1);
		scanf("%s", user_names[i]);

		if(root->folder == NULL)	//if folder linked list is not created, create
				root->folder = LinkedListDir_construct();
		createDirectory(root->folder, user_names[i]);	//create directories for users
	}

	do
	{
		printf("\n1. Create Directory\n");
		printf("2. Change Directory\n");
		printf("3. Create File\n");
		printf("4. View Contents\n");
		printf("5. Exit\n");
		scanf("%d", &ch);

		if(ch==1)	//create directory
		{
			if(strcmp(cur_dir->name,"root") == 0)	//cur dir is root no privilege
			{
				printf("You don't have permission to create a directory in root directory\n");
				continue;
			}

			printf("Enter Directory name : ");
			scanf("%s", dir_name);

			if(cur_dir->folder == NULL)	//if folder linked list is not created, create
				cur_dir->folder = LinkedListDir_construct();
			createDirectory(cur_dir->folder, dir_name);
		}
		else if(ch==2)	//change directory
		{
			printf("Enter Directory name or Enter root to move to root directory\n");
			scanf("%s", dir_name);

			if(strcmp(dir_name, "root") == 0)
			{
				cur_dir = root;	
				continue;
			}
			else if(cur_dir->folder == NULL)
			{
				printf("No Directories present in this Directory\n");
				continue;
			}

			struct Directory* temp = cur_dir->folder->first_dir;
			while(temp != NULL)
			{
				if(strcmp(temp->name, dir_name) == 0)
				{
					cur_dir = temp;
					printf("Directory Changed\n");
					break;
				}
				temp = temp->next;
			}
			if(temp==NULL)
				printf("No such Directory present\n");
		}
		else if(ch==3)//create files
		{
			if(strcmp(cur_dir->name,"root") == 0)	//cur dir is root no privilege
			{
				printf("You don't have permission to create a File in root directory\n");
				continue;
			}

			printf("Enter file name : ");
			scanf("%s", file_name);

			if(cur_dir->file == NULL)	//if file list empty create
				cur_dir->file = LinkedListFile_construct();

			insertFile(cur_dir->file, file_name);
		}
		else if (ch==4)	//display contents
		{
			display_dir_list(cur_dir->folder);
			display_file_list(cur_dir->file);
		}
	}while(ch != 5);
}

void main()
{
	int n, ch;

	printf("Enter number of users : ");
	scanf("%d", &n);

	printf("\n1. Single Level Directory");
	printf("\n2. Hierarchical Directory\n");
	scanf("%d", &ch);

	switch(ch)
	{
		case 1:
		{
			single_level(n);
			break;
		}
		case 2:
		{
			tree_level(n);
			break;
		}
	}
}
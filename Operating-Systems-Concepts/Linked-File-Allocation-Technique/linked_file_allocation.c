#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>

struct BlockNode	//block node
{
	char file_name[15];	//name of file stored in the block
	char dir_name[15];  //name of directory in which file is stored
	struct BlockNode* next;	//pointer to next block
	int status;	//allocated or not
};

struct BlockNode* BlockNodeConstruct(int status, char file_name[])	//block node constructor
{
	struct BlockNode* n=(struct BlockNode*)malloc(sizeof(struct BlockNode));
	strcpy(n->file_name, file_name);
	strcpy(n->dir_name, "");
	n->next = NULL;
	n->status = status;
	return n;
}

struct BlockQueue	//block queue
{
	struct BlockNode* front;	//first block in queue
	struct BlockNode* rear;	   // last block in queue
	int num_blocks;	//total number of blocks
};

struct BlockQueue* BlockQueueConstruct(int n)	//block queue constructor
{
	struct BlockQueue* q=(struct BlockQueue*)malloc(sizeof(struct BlockQueue));
	q->num_blocks = n;
	q->front = NULL;
	q->rear = NULL;
	return q;
}

void enqueueBlockQ(struct BlockQueue* q, struct BlockNode* n)	//enqueueBlockQ
{
	if(q->rear==NULL && q->front==NULL)	//empty queue
	{
		q->front = n;
		q->rear = n;
	 	q->front->next = NULL;
	 	q->rear->next = NULL;
	}
	else	//non-empty queue
	{
		q->rear->next = n;
		q->rear = n;
	}
}

void dequeueBlockQ(struct BlockQueue* q)
{
	struct BlockNode* temp;
	if (q->front == NULL)
		return;
 	temp = q->front;
	q->front = q->front->next;
 	if (q->front == NULL)	//if only one node in the queue
  		q->rear = NULL;
  	free(temp);
}

int isEmptyBlockQ(struct BlockQueue* q)	//return T if queue is empty
{
	return q->front==NULL;
}

struct FileNode 	//each FileNode in directory queue
{
	char file_name[15];	//name of file
	char dir_name[20];  //name of directory whose file is stored in this block
	int file_size;	//size of the file
	int blocks_need;	//number of blocks needed for file	
	struct FileNode* next;	//pointer to next File
};

struct FileNode* FileNodeConstruct(char filename[], char dir_name[], int file_size, int block_s)	//FileNode constructor
{
	struct FileNode* n=(struct FileNode*)malloc(sizeof(struct FileNode));
	strcpy(n->file_name, filename);
	strcpy(n->dir_name, dir_name);
	n->file_size = file_size;
	if(n->file_size % block_s != 0)
		n->blocks_need = ceil(n->file_size / block_s)+1;
	else
		n->blocks_need = ceil(n->file_size / block_s);
	n->next = NULL;
	return n;
}

struct FileQueue 	//File Queue(contains all files in a directory)
{
	struct FileNode* front;	//pointer to first filenode
	struct FileNode* rear;	//pointer to last filenode
	int num_files;	//total number of files in the filequeue(i.e,tot number of files in this directory)
};

struct FileQueue* FileQueueConstruct()	//FileQueue Contructor
{
	struct FileQueue* q=(struct FileQueue*)malloc(sizeof(struct FileQueue));
	q->front = NULL;
	q->rear = NULL;
	q->num_files = 0;
	return q;
}

void enqueueFileQ(struct FileQueue* q, struct FileNode* n)	//enqueueFileQ
{
	if(q->rear==NULL && q->front==NULL)	//empty queue
	{
		q->front = n;
		q->rear = n;
	 	q->front->next = NULL;
	 	q->rear->next = NULL;
	}
	else	//non-empty queue
	{
		q->rear->next = n;
		q->rear = n;
	}
	q->num_files++;
}

void dequeueFileQ(struct FileQueue* q)
{
	struct FileNode* temp;
	if (q->front == NULL)
		return;
 	temp = q->front;
	q->front = q->front->next;
 	if (q->front == NULL)	//if only one node in the queue
  		q->rear = NULL;
  	free(temp);
  	q->num_files--;
}

int isEmptyFileQ(struct FileQueue* q)	//return T if queue is empty
{
	return q->front==NULL;
}

struct DirectoryNode 	//contains file queue(i.e, each directory has some files)
{
	char dir_name[20];	//name of directory
	struct FileQueue* file_q;	//pointer to front of FileQueue
	struct DirectoryNode* next;
};

struct DirectoryNode* DirectoryNodeConstruct(char dir_name[20])	//DirectoryNode Constructor
{
	struct DirectoryNode* q=(struct DirectoryNode*)malloc(sizeof(struct DirectoryNode));
	strcpy(q->dir_name, dir_name);
	q->file_q = NULL;
	q->next = NULL;
	return q;
}

struct DirectoryQueue 	//root's directory queue
{
	struct DirectoryNode* front;
	struct DirectoryNode* rear;
};

struct DirectoryQueue* DirectoryQueueConstruct()	//DirectoryQueue Constructor
{
	struct DirectoryQueue* q=(struct DirectoryQueue*)malloc(sizeof(struct DirectoryQueue));	
	q->front = NULL;
	q->rear = NULL;
	return q;
}

void enqueueDirectoryQ(struct DirectoryQueue* q, struct DirectoryNode* n)	//enqueueFileQ
{
	if(q->rear==NULL && q->front==NULL)	//empty queue
	{
		q->front = n;
		q->rear = n;
	 	q->front->next = NULL;
	 	q->rear->next = NULL;
	}
	else	//non-empty queue
	{
		q->rear->next = n;
		q->rear = n;
	}
}

void dequeueDirectoryQ(struct DirectoryQueue* q)
{
	struct DirectoryNode* temp;
	if (q->front == NULL)
		return;
 	temp = q->front;
	q->front = q->front->next;
 	if (q->front == NULL)	//if only one node in the queue
  		q->rear = NULL;
  	free(temp);
}

int isEmptyDirectoryQ(struct DirectoryQueue* q)	//return T if queue is empty
{
	return q->front==NULL;
}

void linked_allocation(struct BlockQueue* block_q, struct FileNode* file, int block_size)	//index allocation of file
{
	int blocks_allocated = 0; //counter - number of blocks allocated for file
	struct BlockNode* temp = block_q->front;

	while(temp != NULL && blocks_allocated != file->blocks_need)	//loop till blocks needed are allocated
	{
		if(temp->status == 0)	//if block is not allocated
		{
			strcpy(temp->file_name, file->file_name);
			temp->status = 1;
			strcpy(temp->file_name, file->file_name);
			strcpy(temp->dir_name, file->dir_name);
			blocks_allocated++;
		}
		temp = temp->next;
	}
}

int main()
{
	int n_blocks, block_size, n_files, i, ch;
	struct BlockQueue* block_q;

	printf("Enter total number of Blocks : ");
	scanf("%d", &n_blocks);
	
	//initially enqueue all blocks to queue without any file allocation
	block_q = BlockQueueConstruct(n_blocks);
	for(i=0;i<n_blocks;i++)		//initially setting blocks 2,5,9,10 is not free
	{
		if(i==2 || i==5 || i==9 || i==10)
			enqueueBlockQ(block_q, BlockNodeConstruct(1, "OTHERS"));
		else
			enqueueBlockQ(block_q, BlockNodeConstruct(0, "Free"));
	}

	printf("Enter size of each Block : ");
	scanf("%d", &block_size);

	struct DirectoryQueue* root_dirQ = DirectoryQueueConstruct();	//root's directory queue
	struct FileQueue* root_fileQ = FileQueueConstruct();	//root directory's file queue

	do
	{
		printf("\n\n1. Create File\n");
		printf("2. Delete File\n");
		printf("3. View File Allocation\n");
		printf("4. Exit\n\nChoice : ");
		scanf("%d", &ch);

		switch(ch)
		{
			case 1:
			{
				int file_size;
				char file_name[20];
				char dir_name[20];

				//input file details
				printf("Enter File Name : ");
				scanf("%s", file_name);
				printf("Enter size of file \'%s\': ", file_name);
				scanf("%d", &file_size);

				printf("Enter Name of Directory To Create or Type 'root' to Create File in Root Directory : ");
				scanf("%s", dir_name);

				//create file node
				struct FileNode* file = FileNodeConstruct(file_name, dir_name, file_size, block_size);

				if(!strcmp(dir_name, "root"))	//add file in root's file Q
					enqueueFileQ(root_fileQ, file);
				else	//add file to sub directory
				{
					struct DirectoryNode* temp = root_dirQ->front;
					while(temp != NULL && !strcmp(temp->dir_name, dir_name))	//loop till dir is found or no such dir
						temp = temp->next;
					if(temp == NULL)	//no dir found
					{
						struct FileQueue* file_q = FileQueueConstruct();	//create file queue
						enqueueFileQ(file_q, file);	//enqueue file in created file queue

						struct DirectoryNode* new_dir = DirectoryNodeConstruct(dir_name);	//create dir node with dir name
						new_dir->file_q = file_q;

						enqueueDirectoryQ(root_dirQ, new_dir);	//enqueue dir in root's dir queue
					}
					else	//dir found so enqueue file in its file queue
						enqueueFileQ(temp->file_q, file);
				}
				linked_allocation(block_q, file, block_size);
				break;
			}
			case 2:
			{
				char file_name[20];
				char dir_name[20];

				//input file details
				printf("Enter File Name : ");
				scanf("%s", file_name);

				printf("Enter Name of Directory of the file or type 'root' : ");
				scanf("%s", dir_name);

				if(!strcmp(dir_name, "root"))	//found file in root's file Q
				{
					struct FileNode* temp_fn = root_fileQ->front;
					struct FileNode* prev = root_fileQ->front;
					while(temp_fn != NULL)
					{
					 	if(strcmp(file_name, temp_fn->file_name))
					 		break;
						prev = temp_fn;
						temp_fn = temp_fn->next;
					}
					if(temp_fn==NULL)	//not found
					{
						printf("No Such File Found in the directory\n");
						break;
					}
					prev->next = temp_fn->next;
					free(temp_fn);
				}
				else	//found file in sub directory
				{
					struct DirectoryNode* temp_dn = root_dirQ->front;
					
					while(strcmp(temp_dn->dir_name, dir_name))
						temp_dn = temp_dn->next;

					struct FileNode* temp_1 = temp_dn->file_q->front;
					struct FileNode* prev = temp_dn->file_q->front;
					while(temp_1 != NULL && strcmp(file_name, temp_1->file_name))
					{
						prev = temp_1;
						temp_1 = temp_1->next;
					}
					if(temp_1==NULL)	//not found
					{
						printf("No Such File Found in the directory\n");
						break;
					}
					prev->next = temp_1->next;
					free(temp_1);
				}

				struct BlockNode* temp = block_q->front;
				while(temp!=NULL)//loop till found all blocks or end
				{
				 	if(strcmp(temp->file_name, file_name) && strcmp(temp->dir_name, dir_name))
						temp = temp->next;
					else	//found
					{
						strcpy(temp->file_name, "Free");	//set as free block
						strcpy(temp->dir_name, "");	//since free no directory
						temp->status = 0;	//status is free
					}
				}
				break;
			}
			case 3:
			{
				//blocks contents
				printf("\nBlocks :\n--------\n");
				struct BlockNode* temp_b = block_q->front;
				i = 0;	//counter
				while(temp_b != NULL)
				{
					printf("Block : %d - File Name : %s - Directory : %s\n", i, temp_b->file_name, temp_b->dir_name);
					temp_b = temp_b->next;
					i++;
				}

				// directory contents
				printf("\n\nFiles :\n--------");
				struct FileNode* temp_r = root_fileQ->front;
				while(temp_r != NULL && strcmp(temp_r->file_name, ""))
				{
					printf("\nFile Name : %s", temp_r->file_name);
					printf("\nDirectory Name : %s", temp_r->dir_name);
					printf("\nFile Size : %d", temp_r->file_size);
					printf("\nBlocks Needed : %d\n", temp_r->blocks_need);
					temp_r = temp_r->next;
				}

				struct DirectoryNode* temp_d = root_dirQ->front;
				while(temp_d != NULL)
				{
					struct FileNode* temp_dir_f = temp_d->file_q->front;
					while(temp_dir_f != NULL && strcmp(temp_dir_f->file_name, ""))
					{
						printf("\nFile Name : %s", temp_dir_f->file_name);
						printf("\nDirectory Name : %s", temp_dir_f->dir_name);
						printf("\nFile Size : %d", temp_dir_f->file_size);
						printf("\nBlocks Needed : %d\n", temp_dir_f->blocks_need);
						temp_dir_f = temp_dir_f->next;
					}
					temp_d = temp_d->next;
				}
				break;
			}
			case 4:
			{
				exit(0);
			}
			default:
			{
				printf("Invalid Input\n");
			}
		}
	}while(ch!=4);
}
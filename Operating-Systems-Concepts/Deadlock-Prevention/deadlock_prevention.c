#include<stdio.h>
#include<stdlib.h>

void input_data(int n, int m, int *available, int* cpy_available, int **allocation)
{
	int i, j;

	printf("\n Resources Instances\n");
	printf("---------------------------\n");
	//tot instances for resources
	for(i=0;i<m;i++)
	{
		printf("Number of instances for resource %d : ", i+1);
		scanf("%d",&available[i]);
		cpy_available[i] = available[i];
	}

	//allocation
	printf("\n---------------------------\n");
	printf("Allocation of Resources\n");
	printf("---------------------------\n\n");
	for(i=0;i<n;i++)
	{
		printf("-------------------\n");
		printf("Process %d :\n", i+1);
		printf("-------------------\n");
		for(j=0;j<m;j++)
		{
			printf("Number of instances of resource %d to allocate : ", j+1);
			scanf("%d",&allocation[i][j]);
		}
	}
}

void hold_wait(int n, int m, int *available, int* cpy_available, int **allocation)	//hold and wait
{
	int skipped, cnt=0, completed =0, i, j;
	int* finish = (int*)malloc(sizeof(int)*n);	//to denote completed processes
	int* done = (int*)malloc(sizeof(int)*n);	//to denote completed processes
	for(i=0;i<n;i++)
		done[i]=-1;

	while(n != completed)	//skipped should not be equal to the all remaining process - means unsafe
	{
		skipped = 0;
		for(i=0;i<n;i++)
		{
			if(done[i] != -1) //already completed
			{
				skipped++;
				continue;
			}

			for(j=0;j<m;j++)
				if(allocation[i][j] <= available[j])
					cnt++;

			if(cnt==m)	//process i can be allocated
			{
				for(j=0;j<m;j++)
					available[j] -= allocation[i][j];

				finish[completed++] = i;
				done[i]=1;
				skipped=0;
			}
			else
				skipped++;
			cnt=0;
		}
		//wait till all resources are released
		printf("\nAll allocated resources freed...\n");
		for(i=0;i<m;i++)
			available[i] = cpy_available[i];
	}

	printf("\n\nOrder of Resource Allocation : ");
		for(i=0;i<n;i++)
			printf("P%d ", finish[i]);
}

void circular_wait(int n, int m)	//circular wait
{
	int i, pid;
	int* available;	//available vector - number of available instances of each resources
	int* cpy_available;
	
	available = (int*)malloc(sizeof(int)*m);
	cpy_available = (int*)malloc(sizeof(int)*m);

	printf("\n Resources Instances\n");
	printf("---------------------------\n");
	//tot instances for resources
	for(i=0;i<m;i++)
	{
		printf("Number of instances for resource %d : ", i+1);
		scanf("%d",&available[i]);
		cpy_available[i] = available[i];
	}

	do
	{
		int rid=-1, t_rid;
		printf("\nEnter the process Id \n");
		printf("Enter -9 to exit \n");
		scanf("%d", &pid);
		if(pid==-9)
			break;
		printf("\nProcess P%d\n", pid);
		printf("------------\n");
		do
		{
			printf("\tEnter the resource Id to allocate \n");
			printf("\tEnter -9 to exit\n");
			scanf("%d", &t_rid);
			if(t_rid == -1)	//exit choice
				break;
			else if(t_rid <= rid)	//requested lower priority resource or unavailable resource
			{
				printf("\tCan't allocate lower priority resource for this process\n");
				break;
			}
			else	//resource allocated
			{
				rid = t_rid;
				printf("\tResource Allocated\n");
			}
		}while(t_rid != -9);
	}while(pid != -9);
}

void main()
{
	int n;	//number of processes
	int m;	//number of resorce types

	int i, j, pr, ch;

	printf("Enter the number of processes : ");
	scanf("%d",&n);
	printf("Enter the number of resources types : ");
	scanf("%d",&m);

	printf("\n1. Hold & Wait\n");
	printf("2. Circular Wait\n");
	scanf("%d", &ch);

	switch(ch)
	{
		case 1:
		{
			int* available;	//available vector - number of available instances of each resources
			int** allocation;	//Allocation[i,j]-process Pi is currently allocated K instances of Rj
			int* cpy_available;

			available = (int*)malloc(sizeof(int)*m);
			cpy_available = (int*)malloc(sizeof(int)*m);
			allocation = (int**)malloc(sizeof(int*)*n);
			for(i=0;i<n;i++)
				allocation[i] = (int*)malloc(sizeof(int)*m);
			input_data(n, m, available, cpy_available, allocation);
			hold_wait(n, m, available, cpy_available, allocation);
			break;
		}
		case 2:
		{
			circular_wait(n, m);
			break;
		}
	}
}
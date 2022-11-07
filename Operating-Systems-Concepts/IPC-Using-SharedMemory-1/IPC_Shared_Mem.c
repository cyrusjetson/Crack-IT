#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/shm.h>
#include<sys/wait.h>

int sum(int* arr, int s, int e)
{
	int sum=0,i;
	for(i=s;i<=e;i++)
		sum+=arr[i];
	return sum;
}

int main()
{
	int p1, p2, p3, p4,n=8,i, inp[8], key, shmid;
	key = ftok("ex3_1.c", 1);
	printf("Enter 8 elements\n");
	for(i=0;i<8;i++)
		scanf("%d",&inp[i]);
	shmid = shmget(key, 12*sizeof(int),0666|IPC_CREAT);	//create shared memory
	int* shared_mem =(int*)shmat(shmid, 0, 0);

	for(i=0;i<8;i++)
		shared_mem[i] = inp[i];
	shmdt(0);
	((p1 = fork()) && (p2 = fork()));
	if(p1==0)	//child 1
	{
		int* shared_mem =(int*)shmat(shmid, 0, 0);
		shared_mem[8] = sum(shared_mem, 0,1);
		shmdt(0);
	}
	else if(p2==0) //child 2
	{
		int* shared_mem =(int*)shmat(shmid, 0, 0);
		shared_mem[9] = sum(shared_mem, 2,3);
		shmdt(0);
	}
	else if(p1>0) // parent
	{
		((p3 = fork()) && (p4 = fork()));
		if(p3==0)	//child 3
		{
			int* shared_mem =(int*)shmat(shmid, 0, 0);
			shared_mem[10] = sum(shared_mem, 4,5);
			shmdt(0);
		}
		else if(p4==0) //child 4
		{
			int* shared_mem =(int*)shmat(shmid, 0, 0);
			shared_mem[11] = sum(shared_mem, 6,7);
			shmdt(0);
		}
		if(p1 > 0 && p2 > 0 && p3 > 0 && p4 > 0) //parent process
		{
			shared_mem =(int*)shmat(shmid, 0, 0);
			printf("Sum from child 1:%d\n", shared_mem[8]);
			printf("Sum from child 2:%d\n", shared_mem[9]);
			printf("Sum from child 3:%d\n", shared_mem[10]);
			printf("Sum from child 4:%d\n", shared_mem[11]);
			shmdt(0);
			shmctl(shmid, IPC_RMID, NULL); //clear memory
		}
		else
			wait(NULL);
	}

}
#include<stdio.h>
#include<stdlib.h>

int fcfs(int n_requests, int queue[], int pos)
{
	int tot_head_mov = 0, i;
	for(i=0;i<n_requests;i++)
	{
		tot_head_mov += abs(queue[i] - pos);
		pos = queue[i];
		printf("%d ", pos);
	}
	return tot_head_mov;
}

int nearest(int cur_pos, int n_requests, int temp_q[])	//find nearest request
{
	int i, pos=0;
	for(i=1;i<n_requests;i++)
	{
		if(abs(cur_pos-temp_q[i]) < abs(cur_pos-temp_q[pos]))
			pos = i;
	}
	temp_q[pos] = 99999;
	return pos;
}

int sstf(int n_requests, int queue[], int pos)
{
	int i, temp_q[10], tot_head_mov=0, near_pos;

	for(i=0;i<n_requests;i++)	//copy request to temp array
		temp_q[i] = queue[i];

	for(i=0;i<n_requests;i++)
	{
		near_pos = nearest(pos, n_requests, temp_q);
		tot_head_mov += abs(pos - queue[near_pos]);
		pos = queue[near_pos];
		printf("%d ", pos);
	}
	return tot_head_mov;
}

void selectionSort(int n_requests, int temp_q[])	//sort input array
{
    int i, j, min_idx;
    for (i = 0; i < n_requests - 1; i++)
    {
        min_idx = i;
        for (j = i + 1; j < n_requests; j++)
            if (temp_q[j] < temp_q[min_idx])
                min_idx = j;
        //swap
        if(i != min_idx)
        {
	        temp_q[min_idx] += temp_q[i];
	        temp_q[i] = temp_q[min_idx] - temp_q[i];
	        temp_q[min_idx] -= temp_q[i];
	    }
    }
}

int scan(int n_requests, int queue[], int pos)
{
	int i, tot_head_mov = 0, j, temp_q[15];
	
	for(i=0;i<n_requests;i++)	//copy requests array
		temp_q[i] = queue[i];
	selectionSort(n_requests, temp_q);	//sort the requests array

	for(i=0;i<n_requests;i++)	//find the position of header at start
		if(pos <= temp_q[i])
			break;

	for(j=i-1;j>-1;j--)	//towards left from ith pos
	{
		tot_head_mov += abs(pos - temp_q[j]);
		pos = temp_q[j];
		printf("%d ", pos);
	}
	
	printf("0 ");
	pos = 0;

	for(j=i;j<n_requests;j++)	//towards right from ith pos
	{
		tot_head_mov += abs(pos - temp_q[j]);
		pos = temp_q[j];
		printf("%d ", pos);
	}
	return tot_head_mov;
}

int cscan(int n_requests, int queue[], int pos)
{
	int i, tot_head_mov = 0, j, temp_q[15];
	
	for(i=0;i<n_requests;i++)	//copy requests array
		temp_q[i] = queue[i];
	selectionSort(n_requests, temp_q);	//sort the requests array

	for(i=0;i<n_requests;i++)	//find the position of header at start
		if(pos <= temp_q[i])
			break;
	
	for(j=i-1;j>-1;j--)	//towards left from ith pos
	{
		tot_head_mov += abs(pos - temp_q[j]);
		pos = temp_q[j];
		printf("%d ", pos);
	}

	printf("0 199 ");
	pos=199;
	
	for(j=n_requests-1;j>i;j--)	//from right end to ith pos
	{
		tot_head_mov += abs(pos - temp_q[j]);
		pos = temp_q[j];
		printf("%d ", pos);
	}
	return tot_head_mov;
}

int look(int n_requests, int queue[], int pos)
{
	int i, tot_head_mov = 0, j, temp_q[15];
	
	for(i=0;i<n_requests;i++)	//copy requests array
		temp_q[i] = queue[i];
	selectionSort(n_requests, temp_q);	//sort the requests array

	for(i=0;i<n_requests;i++)	//find the position of header at start
		if(pos <= temp_q[i])
			break;

	for(j=i-1;j>-1;j--)	//towards left from ith pos
	{
		tot_head_mov += abs(pos - temp_q[j]);
		pos = temp_q[j];
		printf("%d ", pos);
	}
	
	for(j=i;j<n_requests;j++)	//towards right from ith pos
	{
		tot_head_mov += abs(pos - temp_q[j]);
		pos = temp_q[j];
		printf("%d ", pos);
	}
	return tot_head_mov;
}

int clook(int n_requests, int queue[], int pos)
{
	int i, tot_head_mov = 0, j, temp_q[15];
	
	for(i=0;i<n_requests;i++)	//copy requests array
		temp_q[i] = queue[i];
	selectionSort(n_requests, temp_q);	//sort the requests array

	for(i=0;i<n_requests;i++)	//find the position of header at start
		if(pos <= temp_q[i])
			break;
	
	for(j=i-1;j>-1;j--)	//towards left from ith pos
	{
		tot_head_mov += abs(pos - temp_q[j]);
		pos = temp_q[j];
		printf("%d ", pos);
	}

	for(j=n_requests-1;j>i;j--)	//from right end to ith pos
	{
		tot_head_mov += abs(pos - temp_q[j]);
		pos = temp_q[j];
		printf("%d ", pos);
	}
	return tot_head_mov;
}

void best(int n_requests, int queue[], int pos)
{
	int head_mov[6], best = 0, i;

	printf("\nFCFS\n-----\nHead Movement : %d ", pos);
	head_mov[0] = fcfs(n_requests, queue, pos);
	printf("\nTotal Head Movement : %d\n", head_mov[0]);

	printf("\nSSTF\n-----\nHead Movement : %d ", pos);
	head_mov[1] = sstf(n_requests, queue, pos);
	printf("\nTotal Head Movement : %d\n", head_mov[1]);

	printf("\nSCAN\n-----\nHead Movement : %d ", pos);
	head_mov[2] = scan(n_requests, queue, pos);
	printf("\nTotal Head Movement : %d\n", head_mov[2]);

	printf("\nCSCAN\n-----\nHead Movement : %d ", pos);
	head_mov[3] = cscan(n_requests, queue, pos);
	printf("\nTotal Head Movement : %d\n", head_mov[3]);

	printf("\nLOOK\n-----\nHead Movement : %d ", pos);
	head_mov[4] = look(n_requests, queue, pos);
	printf("\nTotal Head Movement : %d\n", head_mov[4]);

	printf("\nCLOOK\n-----\nHead Movement : %d ", pos);
	head_mov[5] = clook(n_requests, queue, pos);
	printf("\nTotal Head Movement : %d\n", head_mov[5]);

	for(i=1;i<6;i++)
		if(head_mov[i] < head_mov[best])
			best = i;

	if(best == 0)
		printf("\nFCFS is the best Disk Scheduling Algorithm with total head movement of %d cylinders\n", head_mov[best]);
	else if(best == 1)
		printf("\nSSTF is the best Disk Scheduling Algorithm with total head movement of %d cylinders\n", head_mov[best]);
	else if(best == 2)
		printf("\nSCAN is the best Disk Scheduling Algorithm with total head movement of %d cylinders\n", head_mov[best]);
	else if(best == 3)
		printf("\nCSCAN is the best Disk Scheduling Algorithm with total head movement of %d cylinders\n", head_mov[best]);
	else if(best == 4)
		printf("\nLOOK is the best Disk Scheduling Algorithm with total head movement of %d cylinders\n", head_mov[best]);
	else if(best == 5)
		printf("\nCLOOK is the best Disk Scheduling Algorithm with total head movementn of %d cylinders\n", head_mov[best]);
	else if(best == 6)
		printf("\nFCFS is the best Disk Scheduling Algorithm with total head movement of %d cylinders\n", head_mov[best]);
}

int main()
{
	int ch, pos, n_requests, queue[15], i, tot_head_mov;
	do
	{
		printf("Choose an Option :\n-------------------\n");
		printf("\t1. FCFS\n");
		printf("\t2. SSTF\n");
		printf("\t3. SCAN\n");
		printf("\t4. CSCAN\n");
		printf("\t5. LOOK\n");
		printf("\t6. CLOOK\n");
		printf("\t7. Best\n");
		printf("\t8. Exit\n");
		printf("\nOption : ");
		scanf("%d", &ch);
		
		if(ch==8)
			break;
		
		printf("Enter the initial position of the disk head : ");
		scanf("%d", &pos);
		printf("Enter the number of requests : ");
		scanf("%d", &n_requests);
		printf("Enter the disk queue requests\n");
		for(i=0;i<n_requests;i++)
			scanf("%d", &queue[i]);
		
		
		switch(ch)
		{
			case 1:
			{
				printf("\nFCFS\n-----\nHead Movement : %d ", pos);
				tot_head_mov = fcfs(n_requests, queue, pos);
				printf("\nTotal Head Movement : %d\n", tot_head_mov);
				break;
			}
			case 2:
			{
				printf("\nSSTF\n-----\nHead Movement : %d ", pos);
				tot_head_mov = sstf(n_requests, queue, pos);
				printf("\nTotal Head Movement : %d\n", tot_head_mov);
				break;
			}
			case 3:
			{
				printf("\nSCAN\n-----\nHead Movement : %d ", pos);
				tot_head_mov = scan(n_requests, queue, pos);
				printf("\nTotal Head Movement : %d\n", tot_head_mov);
				break;
			}
			case 4:
			{
				printf("\nCSCAN\n-----\nHead Movement : %d ", pos);
				tot_head_mov = cscan(n_requests, queue, pos);
				printf("\nTotal Head Movement : %d\n", tot_head_mov);
				break;
			}
			case 5:
			{
				printf("\nLOOK\n-----\nHead Movement : %d ", pos);
				tot_head_mov = look(n_requests, queue, pos);
				printf("\nTotal Head Movement : %d\n", tot_head_mov);
				break;
			}
			case 6:
			{
				printf("\nCLOOK\n-----\nHead Movement : %d ", pos);
				tot_head_mov = clook(n_requests, queue, pos);
				printf("\nTotal Head Movement : %d\n", tot_head_mov);
				break;
			}
			case 7:
			{
				best(n_requests, queue, pos);
				break;
			}
			case 8:
			{
				exit(0);
			}
		}
		break;//remove
	}while(ch!=8);
}
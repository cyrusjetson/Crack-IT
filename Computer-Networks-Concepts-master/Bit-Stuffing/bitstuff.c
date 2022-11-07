#include<stdio.h>
#include<string.h>
#include<ctype.h>

int stuff_bit(int inp[], int stuff[], int n)
{
	int i, j=0, count=0, flag=0;

	for(i=0;i<20;i++)	//stuff with -1 entirely
		stuff[i]=-1;

	for(i=0;i<n;i++)
	{
		if(inp[i] == 0)	//0
		{
			flag = 1;
			count = 0;
		}
		else	//1s
			count++;

		stuff[j++] = inp[i];

		if(flag==1 && count==5)	//011111
		{
			stuff[j++]=0;
			flag = 0;
			count = 0;
		}
	}

	printf("Bit Stuff : ");
	for(i=0;i<20;i++)
	{
		if(stuff[i] == -1)
			break;
		printf("%d ",stuff[i]);
	}
	return j;
}

void destuff_bit(int stuff[], int destuff[], int n)
{
	int i, j=0, count=0, flag=0;

	for(i=0;i<20;i++)	//stuff with -1 entirely
		destuff[i]=-1;

	for(i=0;i<n;i++)
	{
		if(stuff[i] == 0)	//0
		{
			flag = 1;
			count = 0;
		}
		else	//1s
			count++;

		if(flag ==1 && count==5)
		{
			flag=0;
			count=0;
			destuff[j++]=stuff[i];
			i++;
		}
		else
			destuff[j++]=stuff[i];
	}

	printf("Bit De-Stuff : ");
	for(i=0;i<20;i++)
	{
		if(destuff[i] == -1)
			break;
		printf("%d ",destuff[i]);
	}
}

int main()
{
	int i, n, stuff_len;
	int inp[20], stuff[20], destuff[20];

	printf("Enter length of the data : ");
	scanf("%d", &n);
	printf("Data : ");
	for(i=0;i<n;i++)
		scanf("%d", &inp[i]);

	stuff_len = stuff_bit(inp, stuff, n);
	printf("\n");
	destuff_bit(stuff, destuff, stuff_len);
}
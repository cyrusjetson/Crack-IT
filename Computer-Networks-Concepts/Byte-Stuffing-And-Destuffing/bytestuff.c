#include<stdio.h>
#include<string.h>

int stuff_byte(char inp[], char stuff[])
{
	int i, l, j=1;
	l= strlen(inp);

	stuff[0]='f';
	for(i=1;i<20;i++)
		stuff[i]='-';

	for(i=0;i<l;i++)
	{
		if(inp[i] == 'e' || inp[i] == 'f')
			stuff[j++] = 'e';

		stuff[j++] = inp[i];
	}
	stuff[j]='f';
	printf("Stuffed Data : ");
	for(i=0;i<=j;i++)
	{
		if(stuff[i]=='-')
			break;
		printf("%c", stuff[i]);
	}
	return j;
}

void destuff_byte(char stuff[], char destuff[])
{
	int i, l, j=0;

	for(i=0;i<20;i++)
		destuff[i] = '-';

	l = strlen(stuff);
	for(i=1;i<l;i++)
	{
		if(stuff[i]=='e')
			i++;
		destuff[j++] = stuff[i];
	}

	printf("\nDestuff Data : ");
	for(i=0;i<j;i++)
	{
		if(destuff[i] == 'f' && destuff[i+1] == '-')
			break;
		printf("%c", destuff[i]);
	}
}

int main()
{
	char inp[20], stuff[20], destuff[20];

	printf("Data : ");
	scanf("%s", inp);

	int stuff_len = stuff_byte(inp, stuff);
	destuff_byte(stuff, destuff);
}

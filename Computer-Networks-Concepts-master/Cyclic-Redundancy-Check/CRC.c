#include<stdio.h>

void CRC(int data[], int key[], int n_data, int n_key, int rem[])
{
	int i, j;

	for(i=0;i<n_key;i++)	//copy first n_key bits
		rem[i] = data[i];

	for(i=n_key;i<n_data+n_key;i++)
	{
		if(rem[0] == 1)	//1 at bit 0
		{
			for(j=0;j<n_key;j++)	//XOR with key
				rem[j] = ((rem[j] == key[j])? 0 : 1);
			for(j=0;j<n_key-1;j++)	//shift
				rem[j] = rem[j+1];
			rem[j] = data[i];	//set last bit to bit from data
		}
		else	//0 at bit 0
		{
			for(j=0;j<n_key-1;j++)	//shift
				rem[j] = rem[j+1];
			rem[j] = data[i];	//set last bit to bit from data
		}
	}
}

int main()
{
	int i, n_data, n_key, data[16], key[4], rem[4], sum=0;

	printf("Key Length : ");
	scanf("%d", &n_key);
	printf("Key : ");
	for(i=0;i<n_key;i++)
		scanf("%d", &key[i]);

	printf("Data Length : ");
	scanf("%d", &n_data);
	printf("Data : ");
	for(i=0;i<n_data;i++)
		scanf("%d", &data[i]);
	for(i=n_data;i<n_data+n_key-1;i++)
		data[i] = 0;

	printf("\n\nData : ");
	for(i=0;i<n_data+n_key-1;i++)
		printf("%d ", data[i]);

	printf("\nKey : ");
	for(i=0;i<n_key;i++)
		printf("%d ", key[i]);

	CRC(data, key, n_data, n_key, rem);
	printf("\nRemainder : ");
	for(i=0;i<n_key-1;i++)
		printf("%d ", rem[i]);

	for(i=n_data;i<n_key+n_data-1;i++)
		data[i] = rem[i-n_data];

	printf("\nData From Transmitter : ");
	for(i=0;i<n_key+n_data-1;i++)
		printf("%d ", data[i]);

	CRC(data, key, n_data, n_key, rem);
	printf("\nRemainder : ");
	for(i=0;i<n_key-1;i++)
	{
		sum+=rem[i];
		printf("%d ", rem[i]);
	}

	if(sum == 0)
		printf("\nNo Data Loss\n");
	else
		printf("\nData Loss\n");
}
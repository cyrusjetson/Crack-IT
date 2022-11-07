#include<stdio.h>

int min_dist(int dist[], int visited[], int n)
{
	int min=999, i, min_ind;

	for(i=0;i<n;i++)
		if(visited[i]==0 && min>=dist[i])
		{
			min = dist[i];
			min_ind = i;
		}
	return min_ind;
}

void link_state(int weight_matrix[10][10], int n, int src)
{
	int visited[10], dist[10], i, min_ind, j;

	for(i=0;i<n;i++)
	{
		visited[i]=0;
		dist[i]=999;
	}
	dist[src] = 0;

	for(i=0;i<n;i++)
	{
		min_ind = min_dist(dist, visited, n);
		visited[min_ind]=1;
		for(j=0;j<n;j++)
		{
			if(visited[j]==0 && (dist[min_ind] + weight_matrix[min_ind][j] < dist[j]))
				dist[j] = dist[min_ind] + weight_matrix[min_ind][j];
		}
	}
	for(i=0;i<n;i++)
		printf("%d\n", dist[i]);
}

int main()
{
	int i, j, weight_matrix[10][10], n, m, u, v, weight, src;

	printf("Number of Routers : ");
	scanf("%d",&n);

	for(i=0;i<n;i++)
		for(j=0;j<n;j++)
			if(i==j)
				weight_matrix[i][j]=0;
			else
				weight_matrix[i][j]=999;

	printf("Number of Edges : ");
	scanf("%d",&m);

	for(i=0;i<m;i++)
	{
		printf("\nEdge : %d\n",i+1);
		printf("Enter U:");
		scanf("%d",&u);
		printf("Enter V:");
		scanf("%d",&v);
		printf("Enter weight :");
		scanf("%d",&weight);
		weight_matrix[u-1][v-1]=weight;
		weight_matrix[v-1][u-1]=weight;
	}

	printf("\nSource Router : ");
	scanf("%d",&src);
	link_state(weight_matrix, n, src-1);
}
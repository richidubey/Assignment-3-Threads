#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>		//For malloc

int A[100][100],B[100][100],C[100][100];
int m,n,k;

int main()
{
/*
	for(int i=0;i<10;i++)
		for(int j=0;j<10;j++)
			A[i][j]=i+j;
			
		for(int i=0;i<10;i++)
			for(int j=0;j<10;j++)
				B[i][j]=i+j;*/
	printf("M: ");
	scanf("%d", &m);
	
	printf("K: ");
	scanf("%d", &k);
	
	printf("N: ");
	scanf("%d", &n); 

	
	printf("\nEnter %d*%d Matrix  :",m,k);
	
	for(int i=0;i<m;i++)
		for(int j=0;j<k;j++)
			scanf("%d",&A[i][j]);
	
	printf("\nEnter %d*%d Matrix  :",k,n);
		
	for(int i=0;i<k;i++)
		for(int j=0;j<n;j++)
			scanf("%d",&B[i][j]);

	pthread_t subid;
	pthread_attr_t sub_attr;
	
	void* runsub(void *);
	
	pthread_attr_init(&sub_attr);	
	
	pthread_create(&subid,&sub_attr,runsub,NULL);

	pthread_join(subid,NULL);
	
	printf("Returned Matrix: \n\n");
	for(int i=0;i<m;i++)	
	{
		for(int j=0;j<n;j++)
		{
			printf("%d ",C[i][j]);
		}
		printf("\n");
	}


	return 0;
}

typedef struct
{
	int x;
	int y;
}pair; 

void* runsub(void *ptr)
{
	// Sub Thread that creates thread for every entry of the new matrix
//	m=5;
//	n=6;
//	k=4;
	pthread_t entry[m][n];
	
	void* fillentry (void *);
	
	pair pass[m][n];
	
	for(int i=0;i<m;i++)
	{
		for(int j=0;j<n;j++)
		{
			pass[i][j].x=i;
			pass[i][j].y=j;
			
			// Not having individual pass might affect the output because of concurrent execution.
			pthread_create(&entry[i][j],NULL,fillentry,&pass[i][j]);
		}
	}
	
	printf("A is from thread 1 :\n ");
	
	
	for(int i=0;i<m;i++)
		for(int j=0;j<k;j++)
			printf("%d ",A[i][j]);
	
	
	int *ret;
	for(int i=0;i<m;i++)
	{
		for(int j=0;j<n;j++)
		{
			
			pthread_join(entry[i][j],&ret);
			
			C[i][j]=*ret;
		}
	}
	
	
}

void* fillentry(void *ptr)
{
printf("A is from thread 2 \n: ");
	
	
	for(int i=0;i<m;i++)
		for(int j=0;j<k;j++)
			printf("%d ",A[i][j]);
	
	// Row i, Col j
	
	int* sum=(int*)malloc(sizeof(int));
	
	*sum=0;
	
	printf(" K is = %d",k);
	for(int i=0;i<k;i++)
	{
	
		*sum+=A[((pair*)ptr)->x][i]*B[i][((pair*)ptr)->y];
		
		printf("Added  %d + %d  for %d,%d",A[((pair*)ptr)->x][k],B[k][((pair*)ptr)->y],((pair*)ptr)->x,((pair*)ptr)->y);
	}
	
		printf("Working on %d,%d, Sum = %d\n",((pair*)ptr)->x,((pair*)ptr)->y,*sum);
	
	return sum;
}


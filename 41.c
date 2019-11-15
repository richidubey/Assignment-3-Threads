#include<stdio.h>
#include<pthread.h>

int A[100][100],B[100][100];
int m,n,k;

int main()
{
	
	
	
/*	printf("M: ");*/
/*	scanf("%d", &m);*/
/*	*/
/*	printf("K: ");*/
/*	scanf("%d", &k);*/
/*	*/
/*	printf("N: ");*/
/*	scanf("%d", &n); */

/*	*/
/*	printf("\nEnter %d*%d Matrix  :",m,k);*/
/*	*/
/*	for(int i=0;i<m;i++)*/
/*		for(int j=0;j<k;j++)*/
/*			scanf("%d",&A[i][j]);*/
/*	*/
/*	printf("\nEnter %d*%d Matrix  :",k,n);*/
/*		*/
/*	for(int i=0;i<k;i++)*/
/*		for(int j=0;j<n;j++)*/
/*			scanf("%d",&B[i][j]);*/

	pthread_t subid;
	pthread_attr_t sub_attr;
	
	void* runsub(void *);
	
	pthread_attr_init(&sub_attr);	
	
	pthread_create(&subid,&sub_attr,runsub,NULL);

	pthread_join(subid,NULL);


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
	m=5;
	n=6;
	pthread_t entry[m][n];
	
	void* fillentry (void *);
	
	pair pass;
	
	for(int i=0;i<m;i++)
	{
		for(int j=0;j<n;j++)
		{
			pass.x=i;
			pass.y=j;
			pthread_create(&entry[i][j],NULL,fillentry,&pass);
		}
	}
	
	for(int i=0;i<m;i++)
	{
		for(int j=0;j<n;j++)
		{
			pthread_join(entry[i][j],NULL);
		}
	}
	
	
}

void* fillentry(void *ptr)
{
	printf("Working on %d,%d\n",((pair*)ptr)->x,((pair*)ptr)->y);
}


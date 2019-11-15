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
	
	void* runsub(void * argument);
	
	pthread_attr_init(&sub_attr);
	
	
	pthread_create(&subid,&sub_attr,runsub,hello);

	pthread_join(subid,NULL);


	return 0;
}

void* runsub(void *ptr)
{
		
}


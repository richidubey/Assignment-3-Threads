#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>

typedef struct
{
	int a;
	int b;
	
	int loc;
}data;

int power(int a,int b)
{
	int ret=1;
	
	while(b!=0)
	{
		ret*=a;
		b--;
	}
	return ret;
}
int countdigits(int a)
{
	int ret=0;
	
	while(a!=0)
	{
		a=a/10;
		ret++;
	}
	
	return ret;
}

int getdigit(int a,int loc)
{
	int i=0;
	int ret;
	
	while(i!=loc && a>0)
	{
		ret=a%10;
		a=a/10;
		i++;
	}
	
	
	if(i!=loc)
	return -1;
	
	return ret;
}

void* mult(void *ptr)
{
	data *d;
	
	d=(data*) ptr;
	
	int *ret=malloc(sizeof(int));
	
	for(int i=1;i<=d->loc;i++)
	{
		if(getdigit(d->b,i)!=-1 && getdigit(d->a,d->loc-(i-1))!=-1)
		{
			(*ret)+=getdigit(d->b,i)*getdigit(d->a,d->loc-(i-1)); 	
		//	printf("Thread with loc = %d is mult.%d and %d\n" ,d->loc,getdigit(d->b,i),getdigit(d->a,d->loc-(i-1))); 	
		}
	}
	
	return ret;

}


int main()
{
	
	int a;
	
	int b;
	
	printf("A : ");
	scanf("%d",&a);
	
	printf("B: ");
	scanf("%d",&b);
	
	int digits=0;
	
	digits+=countdigits(a);
	
	digits+=countdigits(b);
	
	data d[digits-1];


	printf("%d\n",digits);
	
	pthread_t tid[digits-1];
	
	for(int i=1;i<=digits-1;i++)		//We always need 1 less digit than the sum of both digits in final ans
	{
		d[i-1].a=a;
		d[i-1].b=b;
		d[i-1].loc=i;
		
		pthread_create(&tid[i-1],NULL,mult,&d[i-1]);
		
	}
	
	
	void *ret[digits-1];
	
	int ans=0;
	
	for(int i=0;i<digits-1;i++)
	{
		pthread_join(tid[i],&ret[i]);
		printf("Thread %d came with return value %d\n",i+1,*((int*)ret[i]));
		//printf("Added %d to ans ",*((int*)ret[i])*power(10,i));		
		ans+=*((int*)ret[i])*power(10,i);
	}
	
	printf("Final Ans = %d\n",ans);


	return 0;
}

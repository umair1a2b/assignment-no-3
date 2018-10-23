#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

int a[1000];
int chunk_size=100;
void *add(void *arg)
{
    int start=(int)arg;
    int end=start+chunk_size;
    int sum=0;
    for(int i=start;i<end;i++)
    {
        sum+=a[i];
    }
    return ((void*)sum);
}
int main()
{
    int status[10];
    pthread_t p_thread[10];
    for(int i=0;i<1000;i++)
    {
        a[i]=i+1;
    }
    for(int i=0;i<10;i++)
    {
        pthread_create(&p_thread[i],NULL,add,(void*)(i*chunk_size));
    }
    for(int i=0;i<10;i++)
    {
        pthread_join(p_thread[i],(void**)&status[i]);
    }
    int sum1=0;
    for(int i=0;i<10;i++)
    {
        printf("Child thread %d : %d \n",i+1,status[i]);
        sum1+=status[i];
    }
    printf("parent thread : %d \n",sum1);
}




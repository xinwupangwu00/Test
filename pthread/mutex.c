#include <stdio.h>
#include <pthread.h>
//#include <error.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

static char buf[5] = {10,20,30,40,50};
pthread_mutex_t mutex;

void *handler1(void *arg)
{

    char *str = (char *)arg;
    printf("这是线程1<id>%lu在跑...\t",pthread_self());
    printf("传入的数据为：%s\n",str);
    
    for(int i=0;i<5;i++)
    {
        sleep(1);
        pthread_mutex_lock(&mutex);
        printf("+++打印全局变量（共享数据）buf[%d] = %d \n",i,*(buf+i));
        *(buf+i) += 5;
        pthread_mutex_unlock(&mutex);
    }
    
    return (void *)0;
}

void *handler2(void *arg)
{
    char *str = (char *)arg;

    printf("这是线程2<id>%lu在跑...\t",pthread_self());
    printf("传入的数据为：%s\n",str);
    for(int i=0;i<5;i++)
    {
        sleep(1);
        pthread_mutex_lock(&mutex);
        printf("---打印全局变量（共享数据）buf[%d] = %d \n",i,*(buf+i));
        *(buf+i) += 5;
        pthread_mutex_unlock(&mutex);
    }

    return (void *) 0;
}
int main()
{
    pthread_t tid1,tid2;
    int ret = 0;
    char *str1 = "wgg dhx xin";
    printf("这是主线程%lu在跑...\n",pthread_self());

    pthread_mutex_init(&mutex,NULL);    //初始化互斥锁

    ret = pthread_create(&tid1,NULL,handler1,(void *)"phx dhx xin");
    if(ret)
    {
        fprintf(stderr,"线程创建失败:%s\n",strerror(ret));
        exit(-1);
    }
    ret = pthread_create(&tid2,NULL,handler2,(void *)str1);
    if(ret)
    {
        fprintf(stderr,"线程创建失败:%s\n",strerror(ret));
        exit(-1);
    }


    pthread_join(tid1,NULL);
    pthread_join(tid2,NULL);

    pthread_mutex_destroy(&mutex);
    
    return 0;
}
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
pthread_mutex_t mutex;
pthread_cond_t cond;
static int flag = 0;
static int buf[] = {100,200,300,400,500};


void *handler1(void *arg)
{
    printf("+++++线程ID：%ld\n",pthread_self());
    for(int i = 0;i<8;i++)
    {
        sleep(1);
        pthread_mutex_lock(&mutex);
        printf("+++上锁\n");
        while(!flag) //条件不成立，就wait，并解开锁
        {
            printf("++++条件不成立，先解开互斥锁\n");
            pthread_cond_wait(&cond,&mutex);         
            //flag = 1;

        }               
        while(flag)
        {
            printf("++++条件成立,操作数据...\n");
        /* code for processing global data */
                flag = 0;
        }
        pthread_mutex_unlock(&mutex);
        printf("++++操作完数据，解开互斥锁\n");
        


    }

    return (void *)0;
}

void *handler2(void *arg)
{
    for(int i = 0;i<8;i++)
    {
        sleep(1);
        pthread_mutex_lock(&mutex);
        printf("---上锁\n");
        /* process */
        flag = 1;
        printf("条件达成,解锁并唤醒wait函数\n");
        pthread_mutex_unlock(&mutex);
        pthread_cond_signal(&cond);


    }

    return (void *)0;
}

int main()
{

    pthread_t tid1,tid2;
    //初始化互斥锁和信号量
    pthread_mutex_init(&mutex,NULL);  
    pthread_cond_init(&cond,NULL); 


    int ret = 0;
    int numBuf[] = {2000,0,7,27};
    ret = pthread_create(&tid1,NULL,handler1,numBuf);
    if(ret)
    {
        perror("pthread_craete failed!\n");
        exit(-1);
    }
    ret = pthread_create(&tid2,NULL,handler2,numBuf);
    if(ret)
    {
        perror("pthread_craete failed!\n");
        exit(-1);
    }



    pthread_join(tid1,NULL);
    pthread_join(tid2,NULL);
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond);

    return 0;
}
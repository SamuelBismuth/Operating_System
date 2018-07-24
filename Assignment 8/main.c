#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

typedef struct args{
    sem_t mutex;
    sem_t* mArr;
    size_t mArr_size;
    int id;
    int * aA_arr;
    int  aArr_Size;
}Args;

void *(*start_routine) (void *);

void * f(void * args){
    Args* arg=(Args*)args;
    int id=arg->id;
    sem_wait(&(arg->mArr[id]));
    printf("hi %d\n",id);
    fflush(stdout);
    if(id!=0)
        arg->aA_arr[id]+=arg->aA_arr[id-1];
    if(id!=4)
        sem_post(&(arg->mArr[id+1]));
    pthread_cancel(pthread_self());
    return 0;
}

int main() {
    start_routine=f;
    pthread_t tArr[5];
    sem_t sArr[5];
    sem_t mutex;
    sem_init(&mutex,0,1);
    int arr []={1,2,3,4,5};
    for (int j = 0; j < 5; ++j) {
        if (j==0)
            sem_init(&sArr[j],0,1);
        else
            sem_init(&sArr[j],0,0);
    }
    for (int i = 0; i < 5; ++i) {
        Args arg;
        arg.id=i;
        arg.aA_arr=arr;
        arg.aArr_Size=5;
        arg.mArr=sArr;
        arg.mArr_size=5;
        arg.mutex=mutex;
        pthread_create(&tArr[i],NULL,f,&arg);
        pthread_join(tArr[i],NULL);
    }
    printf("%d\n",arr[4]);
    fflush(stdout);
    return 0;
}

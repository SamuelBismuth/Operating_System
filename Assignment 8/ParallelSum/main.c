#include <stdio.h>
#include <stdlib.h>

#include <pthread.h>
#include <semaphore.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/mman.h>

typedef struct Args
{
    int step;
    sem_t mutex;
    int* array;
    int array_size;
    pthread_barrier_t* barrier;
    int thread_id;
} args;

void sum(args* argument);
void* create_shared_memory(size_t size);

// https://stackoverflow.com/questions/5656530/how-to-use-shared-memory-with-linux-in-c
void* create_shared_memory(size_t size)
{
    // Our memory buffer will be readable and writable:
    int protection = PROT_READ | PROT_WRITE;

    // The buffer will be shared (meaning other processes can access it), but
    // anonymous (meaning third-party processes cannot obtain an address for it),
    // so only this process and its children will be able to use it:
    int visibility = MAP_ANONYMOUS | MAP_SHARED;

    // The remaining parameters to `mmap()` are not important for this use case,
    // but the manpage for `mmap` explains their purpose.
    return mmap(NULL, size, protection, visibility, 0, 0);
}

void sum(args* argument)
{
    int* temp = (int*) malloc(sizeof(int*) * argument->array_size);
    for (int i = 0; i < argument->array_size; i++)
    {
        temp[i] = (int) malloc(sizeof(int));
        temp[i] = argument->array[i];
    }
    while (argument->step <= argument->array_size)
    {
        puts("hello");
        pthread_barrier_wait(&(argument->barrier));
        puts("hello");
        sem_wait(&argument->mutex);
        if (argument->thread_id >= argument->step)
        {
            //shared A.
            argument->array[argument->thread_id] = temp[argument->thread_id] + temp[argument->thread_id - argument->step];
        }
        sem_post(&argument->mutex);
        pthread_barrier_wait(&argument->barrier);
        for (int i = 0; i < argument->array_size; i++)
        {
            printf("%d, ", argument->array[i]);
            fflush(stdout);
        }
        puts(" ");
        if (argument->thread_id == argument->array_size - 1)
        {
            argument->step *= 2;
        }
        for (int i = 0; i < argument->array_size; i++)
        {
            temp[i] = argument->array[i];
        }
        pthread_barrier_wait(&argument->barrier);
    }
}

int main()
{
    int array [6] = {2, 2, 5, 1, 7, 8};
    int array_size = 6;
    pthread_barrier_t* barrier = (pthread_barrier_t *) create_shared_memory(sizeof(pthread_barrier_t *));
    pthread_barrier_init(barrier, NULL, array_size);
    for (int i = 0; i < array_size; ++i)
    {
        if (fork())
        {
            puts("hello");
            printf("%d \n", pthread_barrier_wait(barrier));
            puts("over");
            printf("destroy %d \n", pthread_barrier_destroy(barrier));
            fflush(stdout);
            puts("test passed");
//            args arg;
//            arg.step = 1;
//            arg.array = (int*) malloc(sizeof(int*) * array_size);
//            for (int i = 0; i < array_size; i++)
//            {
//                arg.array[i] = (int) malloc(sizeof(int));
//                arg.array[i] = array[i];
//            }
//            arg.array_size = array_size;
//            arg.thread_id = i;
//            sem_init(&arg.mutex, 0, 1);
//           // arg.barrier = shmem;
//            sum(&arg);
        }
    }
    return 0;
}

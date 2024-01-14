#include <stdlib.h>
#include <pthread.h>


#define alloc(X,T,R) (R) malloc(X * sizeof (T*));

typedef struct thread_custom {
   void* (*action)(void * param);
    pthread_t thread;
    
} Thread;

Thread* thread_create(void* (*action)(void *)){
    Thread* thread = alloc(1, Thread, Thread*);

    thread->action = action;

    return thread;
}

void thread_start(Thread* thread, void* arg) {
    pthread_create(&(thread->thread), NULL, thread->action, (void*)(arg));
}



void thread_wait(Thread* thread){
   pthread_join(thread->thread, NULL);
}

void thread_free(Thread* thread){
   free(thread);
}
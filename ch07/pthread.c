#include <sys/types.h>
#include <sys/stat.h>
#include <sys/times.h> //times
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/uio.h> //iov
#include <sys/mman.h> //mmap
#include <string.h>
#include <pthread.h> //pthread

pthread_t thread2;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
int shared = 0;

void add_shared() {
    pthread_mutex_lock(&mutex);
    shared ++;
    printf("[%d] shared = %d\n", gettid(), shared);
    pthread_mutex_unlock(&mutex);
}

void *start_thread (void *message) {
    int unused;
    int ret;
    const pthread_t me = pthread_self();

    ret = pthread_setcancelstate(PTHREAD_CANCEL_DEFERRED, &unused);
    
    printf("[%d] thread : %s\n", gettid(), (char*)message);
    sleep(1);
    add_shared();
    if (strcmp((char*)message, "thread1") == 0) {
        int ret = pthread_cancel(thread2);
        if (ret) {
            perror("pthread_cancel");
        }
    }
    sleep(9);
    return message;
}

void *end_thread (void *a) {
    add_shared();
    printf("exit\n");
    pthread_exit(NULL);
}

int main() {
    pthread_t thread1, thread3;
    void * result;

    pthread_create(&thread1, NULL, start_thread, "thread1");
    pthread_create(&thread2, NULL, start_thread, "thread2");
    pthread_create(&thread3, NULL, end_thread, NULL);

    if (pthread_equal(thread1, thread2)) {
        printf("TID equal\n");
    } else {
        printf("TID not equal\n");
    }

    pthread_detach(thread3);
    pthread_join(thread1, &result);
    printf("thread1: %s\n", (char*)result);
    pthread_join(thread2, &result);
    if (result == PTHREAD_CANCELED) {
        printf("thread2 canceled\n");
    } else {
        printf("thread2: %s\n", (char*)result);
    }

    return 0;
}
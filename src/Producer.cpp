#include "../include/Producer.h"

extern Summary summary;

/**
 * While there is input, it reads it from cin, if the value read is S, then it calls the sleep function from tands.
 * If the value is a trans and it requires the code to do work then, it starts a semaphore and adds the value to
 * the queue for the threads to read it. This process is protected by semaphores to check for whether the queue is
 * full or not.
 */
void Producer::pushToQueue()
{
    string val;
    while (getline(cin, val)) {
        if(val[0]=='S'){
            string tmp = val.substr(1,val.length()-1);
            printRow(0,"Sleep", val,-1);
            Sleep(atoi(tmp.c_str()));
            summary.addSleep();
        }
        else {
            sem_wait(&CanAddStack);
            sem_wait(&StackMutex);
            tasks.push(val);
            summary.addWork();
            printRow(0, "Work", val, tasks.size());
            sem_post(&StackMutex);
            sem_post(&AvailStack);
        }
    }
    printRow(0,"End","",-1);
    endOfFileReached = true;
}

/**
 * Creates the consumer threads based on the number of threads, after it creates the threads, it proceeds to push to
 * queue. After all the tasks in the consumer threads are done, it closes them and it prints a summary of the program
 * @param *arg
 */
void * Producer::createConsumerThreads(void *arg)
{
    int nthreads = *static_cast<int *>(arg);
    pthread_t consumerThreads [nthreads];
    int *threadID;
    for (int i = 0; i < nthreads; i++){
        threadID = static_cast<int *>(malloc(sizeof(int)));
        *threadID = i;
        if( pthread_create( &consumerThreads[i], NULL, &Consumer::threadloop, static_cast<void *>(threadID))) {
            perror( "Thread create" );
            return NULL;
        }
    }

    pushToQueue();

    for (int i = 0; i < nthreads; i++){
        pthread_join(consumerThreads[i],NULL);
    }
    free(threadID);
    summary.printSummary();
    return 0;
}
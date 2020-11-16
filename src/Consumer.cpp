#include "../include/Consumer.h"

extern Summary summary;

/**
 * Protected by different semaphores, it checks to see whether there is anything in the queue to pop
 * once the file is done being read, then it checks whether the queue is also empty from tasks, when
 * the queue is empty of tasks it frees all the semaphores to allow the threads to come to a conclusion
 * @param threadID
 */
string Consumer::popFromQueue(int threadID){
    sem_wait(&AvailStack);
    sem_wait(&StackMutex);
    string taskToDo = "";
    if(!endOfFileReachedTasksNotAvail) {
        taskToDo = tasks.front();
        tasks.pop();
        printRow(threadID, "Receive", taskToDo, tasks.size());
        summary.addReceive();
        if (endOfFileReached && tasks.size() == 0) {
            endOfFileReachedTasksNotAvail = true;
            sem_post(&StackMutex);
            sem_post(&CanAddStack);
            sem_post(&AvailStack);
        }
    }
    else {
        sem_post(&StackMutex);
        sem_post(&CanAddStack);
        sem_post(&AvailStack);
    }
    sem_post(&StackMutex);
    sem_post(&CanAddStack);
    return taskToDo;
}

/**
 * calls the trans function from the tands.h file and passes it the value val as the input
 * @param val
 */
void Consumer::callTrans(string val){
    if (val[0]=='T'){
        string tmp = val.substr(1,val.length()-1);
        Trans(atoi(tmp.c_str()));
    }
}

/**
 * The main loop that is being run by all the consumer threads. The end condition is when the end of the file is reached
 * and all the tasks in the queue have come to a completion. In this method, first the thread asks for work, then it pops
 * from the queue. After the task has come to a completion, it prints that the task is completed and updates the summary
 * tables.
 * @param argc
 * @param *argv[]
 */
void * Consumer::threadloop( void *args ) {
    int threadID = *static_cast<int *>(args)+1;
    while(true) {
        printRow(threadID, "Ask", "", -1);
        summary.addAsk();
        if(endOfFileReachedTasksNotAvail){
            break;
        }
        else {
            string taskToCall = popFromQueue(threadID);
            if(taskToCall!="") {
                callTrans(taskToCall);
                printRow(threadID, "Complete", taskToCall, -1);
                summary.updateThreadCounts(threadID);
                summary.addComplete();
            }
            else{
                break;
            }
        }
    }
    return 0;
}
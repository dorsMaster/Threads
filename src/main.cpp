#include "../include/includes.h"

sem_t StackMutex;
sem_t CanAddStack;
sem_t AvailStack;
sem_t Print;
sem_t SummarySem;
queue<string> tasks;

bool endOfFileReached;
bool endOfFileReachedTasksNotAvail;

string filename;
ofstream myfile(filename);

Summary summary;

std::chrono::time_point<std::chrono::steady_clock> startTime = std::chrono::steady_clock::now();
/**
 * Uses a template to assign width to table for when it prints
 * https://stackoverflow.com/questions/14765155/how-can-i-easily-format-my-data-table-in-c
 * @param t
 * @param width
 */

template<typename T> void printElement(T t, const int& width) {
    myfile << left << setw(width) << setfill(separator) << t;
}
/**
 * Uses a template to assign width to table for when it prints the queue size
 * @param t
 * @param width
 */

template<typename T> void printqSizeElement(T t, const int& width) {
    myfile << left  << "Q= " << setw(width) << setfill(separator) << t;
}
/**
 * Uses a template to assign width to table for when it prints the time. It also sets the precision to three, meaning it will have 3 decimal places.
 * @param t
 * @param width
 */

template<typename T> void printTimeElement(T t, const int& width) {
    myfile << fixed <<setprecision(3) << left << setw(width) << setfill(separator)  << t;
}
/**
 * Print a row in the file with the thread Id, the type of action, job and size of the queue
 * @param threadID
 * @param message
 * @param job
 * @param qSize
 */

void printRow(int threadID, string message, string job, int qSize){
    sem_wait(&Print);
    std::chrono::time_point<std::chrono::steady_clock> timePoint = std::chrono::steady_clock::now();
    auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(timePoint - startTime);
    double ms = (double)milliseconds.count()/1000;
    printTimeElement(ms,timeWidth);
    printElement("ID= ", idWidth);
    printElement(threadID, numWidth);
    (qSize==-1)?printElement("",qsizeWidth+3):printqSizeElement(qSize,qsizeWidth);
    printElement(message, commandWidth);
    printElement(((job[0]=='T' || job[0]=='S')?(job.substr(1,job.length()-1)):" "), numWidth);
    myfile << "\n";
    summary.setEndTime(ms);
    sem_post(&Print);
}
/**
 * Initiates the semaphores, and the producer thread. Waits on the producer thread to come to completion
 * @param argc
 * @param *argv[]
 */

int main(int argc, char *argv[]) {
    endOfFileReached = false;
    endOfFileReachedTasksNotAvail = false;
    int nthreads = strtol(argv[1], NULL, 10);
    int sizeOfQ = nthreads * 2;

    if( sem_init(&Print, 0, 1 ) ) {
        perror( "AvailStack Sempahore init" );
        exit( -1 );
    }
    if( sem_init(&StackMutex, 0, 1 ) ) {
        perror( "StackMutex Sempahore init" );
        exit( -1 );
    }
    if( sem_init(&CanAddStack, 0, sizeOfQ ) ) {
        perror( "CanAddStack Sempahore init" );
        exit( -1 );
    }
    if( sem_init(&AvailStack, 0, 0 ) ) {
        perror( "AvailStack Sempahore init" );
        exit( -1 );
    }
    if( sem_init(&SummarySem, 0, 1 ) ) {
        perror( "AvailStack Sempahore init" );
        exit( -1 );
    }

    summary = Summary();
    summary.initThreadsSumArray(nthreads);
    if (argc==3){
        filename = (string)"prodcon." + argv[2] + (string)".log";
    }
    else{
        filename = "prodcon.log";
    }
    summary.setFileName(filename);
    myfile.open(filename);

    pthread_t ptid;
    int *numthreads =  (int *)malloc(sizeof(int));
    *numthreads = nthreads;
    if(pthread_create(&ptid, NULL, &Producer::createConsumerThreads, (void *)numthreads)) {
        perror("Thread create");
        return (-1);
    }

    pthread_join(ptid,NULL);
    return 0;
}

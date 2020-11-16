//
// Created by dors on 10/24/20.
//
#include "../include/Summary.h"

extern std::ofstream myfile;

/**
 * Initializes summary with all values as zeros
 */
Summary::Summary() {
    Summary::work = 0;
    Summary::sleep = 0;
    Summary::complete = 0;
    Summary::ask = 0;
    Summary::receive = 0;
    Summary::nthreads = 0;
    Summary::filename = "";
}

/**
 * Initializes an array with all zeros with the size of nthreads starting from index 1
 * @param nthreads
 */
void Summary::initThreadsSumArray(int nthreads){
    Summary::nthreads = nthreads;
    Summary::threads = new int [nthreads+1];
    for (int i; i<nthreads+2; i++){
        Summary::threads[i]=0;
    }
}

/**
 * This function is used at the beginning of the program to set the file that summary needs to write to
 * @param fileName
 */
void Summary::setFileName(std::string fileName){
    Summary::filename = fileName;
}

/**
 * Sets the time for the last job that was run
 * @param endTime
 */
void Summary::setEndTime(float endTime){
    Summary::endTime = endTime;
}

/**
 * To keep track of work
 */
void Summary::addWork(){
    sem_wait(&SummarySem);
    Summary::work +=1;
    sem_post(&SummarySem);
}

/**
 * To keep track of ask
 */
void Summary::addAsk(){
    sem_wait(&SummarySem);
    Summary::ask +=1;
    sem_post(&SummarySem);
}

/**
 * To keep track of receive
 */
void Summary::addReceive(){
    sem_wait(&SummarySem);
    Summary::receive +=1;
    sem_post(&SummarySem);
}

/**
 * To keep track of complete
 */
void Summary::addComplete(){
    sem_wait(&SummarySem);
    Summary::complete +=1;
    sem_post(&SummarySem);
}

/**
 * To keep track of sleep
 */
void Summary::addSleep(){
    sem_wait(&SummarySem);
    Summary::sleep +=1;
    sem_post(&SummarySem);
}

/**
 * To keep track of the count of work for each thread
 */
void Summary::updateThreadCounts(int threadID){
    sem_wait(&SummarySem);
    Summary::threads[threadID]=Summary::threads[threadID]+1;
    sem_post(&SummarySem);
}

/**
 * To print the summary at the end of the program, it also closes the file
 */
void Summary::printSummary() {
    if (myfile.is_open()) {
        myfile << "Summary" << "\n";
        myfile << "    Work      " << Summary::work << "\n";
        myfile << "    Ask       " << Summary::ask << "\n";
        myfile << "    Receive   " << Summary::receive << "\n";
        myfile << "    Complete  " << Summary::complete << "\n";
        myfile << "    Sleep     " << Summary::sleep << "\n";
        for (int i = 0; i < Summary::nthreads; i++) {
            myfile << "Thread   ";
            myfile << left << setw(5) << setfill(separator) << i + 1 << "       " << Summary::threads[i + 1] << "\n";
        }
        myfile << "Transactions per second:    " << ((Summary::endTime==0)?-1:((float) (Summary::complete / Summary::endTime))) << "\n";
        myfile.flush();
        myfile.close();
    }
}



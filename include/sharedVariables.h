//
// Created by dors on 10/29/20.
//

#ifndef C379A2_SHAREDVARIABLES_H
#define C379A2_SHAREDVARIABLES_H

#include <semaphore.h>
#include <queue>
#include <iostream>
using namespace std;

extern sem_t StackMutex;
extern sem_t CanAddStack;
extern sem_t AvailStack;
extern sem_t SummarySem;
extern queue<string> tasks;

const char separator    = ' ';
const int idWidth     = 5;
const int timeWidth     = 8;
const int numWidth     = 3;
const int commandWidth = 12;
const int qsizeWidth = 5;

extern bool endOfFileReached;
extern bool endOfFileReachedTasksNotAvail;

void printRow(int threadID, string message, string job, int qSize);


#endif //C379A2_SHAREDVARIABLES_H

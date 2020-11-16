//
// Created by dors on 10/24/20.
//

#ifndef C379A2_SUMMARY_H
#define C379A2_SUMMARY_H
#include <iostream>
#include <fstream>
#include <iomanip>
#include "sharedVariables.h"

class Summary {
    int work;
    int ask;
    int receive;
    int complete;
    int sleep;
    int *threads;
    int nthreads;
    std::string filename;
    float endTime;
public:
    Summary();
    void addWork();
    void addSleep();
    void addAsk();
    void addReceive();
    void addComplete();
    void printSummary();
    void initThreadsSumArray(int nthreads);
    void updateThreadCounts(int threadID);
    void setFileName(std::string fileName);
    void setEndTime(float endTime);
};


#endif //C379A2_SUMMARY_H

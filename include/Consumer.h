//
// Created by dors on 10/22/20.
//

#ifndef C379A2_CONSUMER_H
#define C379A2_CONSUMER_H
#include "Summary.h"
#include <iostream>
#include "sharedVariables.h"
#include "tands.h"

/**
 * The consumer class is to pop from Queue, it is reliant on Summary in order to update the tasks.
 */

class Consumer {

    static std::string popFromQueue(int threadID);

    static void callTrans(std::string val);

public:
    static void *threadloop(void *arg);
};


#endif //C379A2_CONSUMER_H

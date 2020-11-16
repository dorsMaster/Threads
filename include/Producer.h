//
// Created by dors on 10/22/20.
//

#ifndef C379A2_PRODUCER_H
#define C379A2_PRODUCER_H
#include "../include/Consumer.h"
/**
 * Creates consumer thread, pushes values to the queue and waits on the consumer threads to finish
 */
class Producer {
    static void pushToQueue();

public:
    static void * createConsumerThreads(void *arg);
};


#endif //C379A2_PRODUCER_H

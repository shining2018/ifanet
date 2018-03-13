/*
 * DropTailQueue.h
 *
 *  Created on: 2018Äê1ÔÂ22ÈÕ
 *      Author: NETLAB
 */

#ifndef INET_COMMON_QUEUE_DROPTAILQUEUE_H_
#define INET_COMMON_QUEUE_DROPTAILQUEUE_H_

#include "inet/common/INETDefs.h"

#include "inet/common/queue/PassiveQueueBase.h"

namespace inet {

/**
 * Drop-front queue. See NED for more info.
 */
class INET_API DropTailQueue : public PassiveQueueBase
{
  protected:
    // configuration
    int frameCapacity;

    // state
    cQueue queue;
    cGate *outGate;

    // statistics
    static simsignal_t queueLengthSignal;

  public:
    virtual void initialize() override;

    /**
     * Redefined from PassiveQueueBase.
     */
    virtual cMessage *enqueue(cMessage *msg) override;

    /**
     * Redefined from PassiveQueueBase.
     */
    virtual cMessage *dequeue() override;

    /**
     * Redefined from PassiveQueueBase.
     */
    virtual void sendOut(cMessage *msg) override;

    /**
     * Redefined from IPassiveQueue.
     */
    virtual bool isEmpty() override;

  public:
    int getLength();
};

} // namespace inet



#endif /* INET_COMMON_QUEUE_DROPTAILQUEUE_H_ */

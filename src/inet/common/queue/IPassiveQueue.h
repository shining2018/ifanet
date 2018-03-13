/*
 * IPassiveQueue.h
 *
 *  Created on: 2018Äê1ÔÂ22ÈÕ
 *      Author: NETLAB
 */

#ifndef INET_COMMON_QUEUE_IPASSIVEQUEUE_H_
#define INET_COMMON_QUEUE_IPASSIVEQUEUE_H_

#include "inet/common/INETDefs.h"

namespace inet {

class IPassiveQueueListener;

/**
 * Abstract interface for passive queues.
 */
class INET_API IPassiveQueue
{
  public:
    virtual ~IPassiveQueue() {}

    /**
     * The queue should send a packet whenever this method is invoked.
     * If the queue is currently empty, it should send a packet when
     * when one becomes available.
     */
    virtual void requestPacket() = 0;

    /**
     * Returns number of pending requests.
     */
    virtual int getNumPendingRequests() = 0;

    /**
     * Return true when queue is empty, otherwise return false.
     */
    virtual bool isEmpty() = 0;

    /**
     * Clear all queued packets and stored requests.
     */
    virtual void clear() = 0;

    /**
     * Returns a packet directly from the queue, bypassing the primary,
     * send-on-request mechanism. Returns nullptr if the queue is empty.
     */
    virtual cMessage *pop() = 0;

    /**
     * Adds a new listener to the listener list.
     * It does nothing, if the listener list already contains the listener
     * (by pointer equality).
     */
    virtual void addListener(IPassiveQueueListener *listener) = 0;

    /**
     * Removes a listener from the listener list.
     * It does nothing if the listener was not found on the listener list.
     */
    virtual void removeListener(IPassiveQueueListener *listener) = 0;
};

/**
 * Interface for notifying listeners about passive queue events.
 */
class INET_API IPassiveQueueListener
{
  public:

    virtual ~IPassiveQueueListener() {};

    /**
     * A packet arrived and it was added to the queue (the queue length
     * increased by one). Therefore a subsequent requestPacket() call
     * can deliver a packet immediately.
     */
    virtual void packetEnqueued(IPassiveQueue *queue) = 0;
};

} // namespace inet



#endif /* INET_COMMON_QUEUE_IPASSIVEQUEUE_H_ */

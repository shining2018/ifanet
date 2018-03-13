/*
 * DropTailQueue.cc
 *
 *  Created on: 2018Äê1ÔÂ22ÈÕ
 *      Author: NETLAB
 */

#include "inet/common/queue/DropTailQueue.h"

namespace inet {

Define_Module(DropTailQueue);

simsignal_t DropTailQueue::queueLengthSignal = registerSignal("queueLength");

void DropTailQueue::initialize()
{
    PassiveQueueBase::initialize();

    queue.setName(par("queueName"));

    //statistics
    emit(queueLengthSignal, queue.getLength());

    outGate = gate("out");

    // configuration
    frameCapacity = par("frameCapacity");
}

cMessage *DropTailQueue::enqueue(cMessage *msg)
{
    if (frameCapacity && queue.getLength() >= frameCapacity) {
        EV << "Queue full, dropping packet.\n";
        return msg;
    }
    else {
        queue.insert(msg);
        emit(queueLengthSignal, queue.getLength());
        return nullptr;
    }
}

cMessage *DropTailQueue::dequeue()
{
    if (queue.isEmpty())
        return nullptr;

    cMessage *msg = (cMessage *)queue.pop();

    // statistics
    emit(queueLengthSignal, queue.getLength());

    return msg;
}

void DropTailQueue::sendOut(cMessage *msg)
{
    send(msg, outGate);
}

bool DropTailQueue::isEmpty()
{
    return queue.isEmpty();
}

int DropTailQueue::getLength()
{
    return queue.getLength();
}

} // namespace inet



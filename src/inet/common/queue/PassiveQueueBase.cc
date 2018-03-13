/*
 * PassiveQueueBase.cc
 *
 *  Created on: 2018Äê1ÔÂ22ÈÕ
 *      Author: NETLAB
 */

#include <algorithm>

#include "inet/common/queue/PassiveQueueBase.h"

namespace inet {

simsignal_t PassiveQueueBase::rcvdPkSignal = registerSignal("rcvdPk");
simsignal_t PassiveQueueBase::enqueuePkSignal = registerSignal("enqueuePk");
simsignal_t PassiveQueueBase::dequeuePkSignal = registerSignal("dequeuePk");
simsignal_t PassiveQueueBase::dropPkByQueueSignal = registerSignal("dropPkByQueue");
simsignal_t PassiveQueueBase::queueingTimeSignal = registerSignal("queueingTime");

void PassiveQueueBase::initialize()
{
    // state
    packetRequested = 0;
    WATCH(packetRequested);

    // statistics
    numQueueReceived = 0;
    numQueueDropped = 0;
    WATCH(numQueueReceived);
    WATCH(numQueueDropped);
}

void PassiveQueueBase::handleMessage(cMessage *msg)
{
    numQueueReceived++;

    emit(rcvdPkSignal, msg);

    if (packetRequested > 0) {
        packetRequested--;
        emit(enqueuePkSignal, msg);
        emit(dequeuePkSignal, msg);
        emit(queueingTimeSignal, SIMTIME_ZERO);
        sendOut(msg);
    }
    else {
        msg->setArrivalTime(simTime());
        cMessage *droppedMsg = enqueue(msg);
        if (msg != droppedMsg)
            emit(enqueuePkSignal, msg);

        if (droppedMsg) {
            numQueueDropped++;
            emit(dropPkByQueueSignal, droppedMsg);
            delete droppedMsg;
        }
        else
            notifyListeners();
    }
}

void PassiveQueueBase::refreshDisplay() const
{
    char buf[100];
    sprintf(buf, "q rcvd: %d\nq dropped: %d", numQueueReceived, numQueueDropped);
    getDisplayString().setTagArg("t", 0, buf);
}

void PassiveQueueBase::requestPacket()
{
    Enter_Method("requestPacket()");

    cMessage *msg = dequeue();
    if (msg == nullptr) {
        packetRequested++;
    }
    else {
        emit(dequeuePkSignal, msg);
        emit(queueingTimeSignal, simTime() - msg->getArrivalTime());
        sendOut(msg);
    }
}

void PassiveQueueBase::clear()
{
    cMessage *msg;

    while (nullptr != (msg = dequeue()))
        delete msg;

    packetRequested = 0;
}

cMessage *PassiveQueueBase::pop()
{
    return dequeue();
}

void PassiveQueueBase::finish()
{
}

void PassiveQueueBase::addListener(IPassiveQueueListener *listener)
{
    auto it = find(listeners.begin(), listeners.end(), listener);
    if (it == listeners.end())
        listeners.push_back(listener);
}

void PassiveQueueBase::removeListener(IPassiveQueueListener *listener)
{
    auto it = find(listeners.begin(), listeners.end(), listener);
    if (it != listeners.end())
        listeners.erase(it);
}

void PassiveQueueBase::notifyListeners()
{
    for (auto & elem : listeners)
        (elem)->packetEnqueued(this);
}

} // namespace inet



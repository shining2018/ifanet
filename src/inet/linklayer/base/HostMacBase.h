/*
 * HostMacBase.h
 *
 *  Created on: 2018Äê3ÔÂ12ÈÕ
 *      Author: NETLAB
 */

#ifndef INET_LINKLAYER_BASE_HOSTMACBASE_H_
#define INET_LINKLAYER_BASE_HOSTMACBASE_H_

#include "inet/common/INETDefs.h"
#include "inet/common/queue/DropTailQueue.h"
#include "inet/mobility/base/MovingMobilityBase.h"
#include "inet/common/geometry/common/Coord.h"

namespace inet
{
class INET_API HostMacBase:public cSimpleModule
{
protected:
    simtime_t m_SlotLength;
    int m_SlotNum;
    double m_CommunicationRange;

    DropTailQueue *m_PkQueue;
    DropTailQueue *m_ReTransQueue;

    cModule *m_Bs;
    cModule *m_Parent;

    MovingMobilityBase *m_Mobility;

protected:
    virtual void initialize(int stage) override;
    void findBs();
    void findParentModule();
    Coord getCurrentPosition();
    Coord getApPosition();
    double getDistance();
    int getPropagationSlots();

    //virtual void receiveSignal(cComponent *source, simsignal_t signalID, cObject *obj, cObject *details) override;

public:
    HostMacBase();
};
}



#endif /* INET_LINKLAYER_BASE_HOSTMACBASE_H_ */

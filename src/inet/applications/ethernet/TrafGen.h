/*
 * TrafGen.h
 *
 *  Created on: 2018Äê1ÔÂ22ÈÕ
 *      Author: NETLAB
 */

#ifndef INET_APPLICATIONS_ETHERNET_TRAFGEN_H_
#define INET_APPLICATIONS_ETHERNET_TRAFGEN_H_

#include "inet/common/INETDefs.h"

namespace inet
{
class INET_API TrafGen: public cSimpleModule
{
protected:

    long m_SeqNum = 0;

    //send parameters
    cPar *m_SendInterval = nullptr;
    cPar *m_NumPacketsPerBurst = nullptr;
    cPar *m_PacketLength = nullptr;

    //selfmessage
    cMessage *m_TimerMsg = nullptr;

    simtime_t m_StartTime;
    simtime_t m_StopTime;

    //statistics
    long m_PacketsSent = 0;
    simsignal_t m_SentPkSignal;

protected:
    virtual void initialize(int stage) override;
    virtual int numInitStages() const override { return NUM_INIT_STAGES; }
    virtual void handleMessage(cMessage *msg) override;
    virtual void finish() override;

    virtual void scheduleNextPacket(simtime_t previous);
    virtual void sendBurstPackets();

public:
    TrafGen();
    virtual ~TrafGen();
};

}



#endif /* INET_APPLICATIONS_ETHERNET_TRAFGEN_H_ */

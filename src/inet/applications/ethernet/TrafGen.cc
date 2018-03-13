/*
 * TrafGen.cc
 *
 *  Created on: 2018Äê1ÔÂ22ÈÕ
 *      Author: NETLAB
 */
#include <stdio.h>
#include <string.h>
#include <math.h>

#include "inet/applications/ethernet/TrafGen.h"

namespace inet
{
Define_Module(TrafGen);

TrafGen::TrafGen()
{
    m_SendInterval=nullptr;
    m_NumPacketsPerBurst=nullptr;
    m_PacketLength=nullptr;
    m_TimerMsg=nullptr;
}

TrafGen::~TrafGen()
{
    cancelAndDelete(m_TimerMsg);
}

void TrafGen::initialize(int stage)
{
    cSimpleModule::initialize(stage);

    if(stage == INITSTAGE_LOCAL)
    {
        m_SendInterval = &par("sendInterval");
        m_NumPacketsPerBurst = &par("numPacketsPerBurst");
        m_PacketLength = &par("packetLength");

        m_SeqNum = 0;
        WATCH(m_SeqNum);

        //statistics
        m_SentPkSignal=registerSignal("sentPk");
        m_PacketsSent = 0;
        WATCH(m_PacketsSent);

        m_StartTime = par("startTime");
        m_StopTime = par("stopTime");
        if (m_StopTime >= SIMTIME_ZERO && m_StopTime < m_StartTime)
        {
            throw cRuntimeError("Invalid startTime/stopTime parameters");
        }
    }
    else
    {
        if(stage == INITSTAGE_APPLICATION_LAYER)
        {
            m_TimerMsg = new cMessage("generateNextPacket");
            scheduleNextPacket(-1);
        }
    }
}

void TrafGen::handleMessage(cMessage *msg)
{
    if(msg->isSelfMessage())
    {
        sendBurstPackets();
        scheduleNextPacket(simTime());
    }
    else
    {
        throw cRuntimeError("TrafGen receives error msg! ");
    }
}

void TrafGen::finish()
{
    cancelAndDelete(m_TimerMsg);
    m_TimerMsg = nullptr;
}

void TrafGen::scheduleNextPacket(simtime_t previous)
{
    simtime_t next;
    if(previous == -1)
    {
        next = simTime() <= m_StartTime ? m_StartTime : simTime();
        EV_INFO<<"next scheduling time: "<<next<<endl;
    }
    else
    {
        next = previous + m_SendInterval->doubleValue();
        EV_INFO<<"next scheduling time: "<<next<<endl;
    }

    if(m_StopTime < SIMTIME_ZERO || next < m_StopTime)
    {
        scheduleAt(next,m_TimerMsg);

    }
}


void TrafGen::sendBurstPackets()
{
    int n= m_NumPacketsPerBurst->longValue();
    for(int i =0; i < n; i++)
    {
        m_SeqNum++;

        char msgname[40];
        sprintf(msgname, "pk-%d-%ld",getId(),m_SeqNum);

        cPacket *pk = new cPacket(msgname);

        long len = m_PacketLength->longValue();
        pk->setByteLength(len);

        EV_INFO << "Send packet: "<< msgname <<", length=" <<len<<" Bytes"<<endl;
        emit(m_SentPkSignal,pk);
        send(pk,"appOut");
        m_PacketsSent++;
    }
}
}




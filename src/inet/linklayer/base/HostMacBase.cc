/*
 * HostMacBase.cc
 *
 *  Created on: 2018Äê3ÔÂ12ÈÕ
 *      Author: NETLAB
 */

#include "inet/linklayer/base/HostMacBase.h"
namespace inet
{
Define_Module(HostMacBase);

HostMacBase::HostMacBase()
{
    m_SlotLength = 0;
    m_SlotNum = 0;
    m_CommunicationRange = 0;
    m_PkQueue = nullptr;
    m_ReTransQueue = nullptr;
    m_Mobility = nullptr;
}

void HostMacBase::initialize(int stage)
{
    cSimpleModule::initialize(stage);

    if(stage == INITSTAGE_LOCAL)
    {
        m_SlotLength = par("slotLength");
        m_SlotNum = par("slotNum");
        m_CommunicationRange = par("communicationRange");
    }
    else
    {
        if(stage == INITSTAGE_LINK_LAYER)
        {
            m_PkQueue = dynamic_cast<DropTailQueue *>(gate("upperLayerInPkQueue")->getPreviousGate()->getOwnerModule());
            m_ReTransQueue = dynamic_cast<DropTailQueue *>(gate("upperLayerInReTransQueue")->getPreviousGate()->getOwnerModule());

            m_Mobility = dynamic_cast<MovingMobilityBase *>(this->getParentModule()->getModuleByPath("mobility"));

            findBs();
            findParentModule();

        }
    }
}

void HostMacBase::findBs()
{
    m_Bs=getModuleByPath("bs");
    if(!m_Bs)
    {
        throw cRuntimeError("HostMacBase--BS not found!");
    }
    else
    {
        EV_DEBUG<<this->getFullName()<<" found BS: "<<m_Bs->getFullName()<<endl;
    }
}

void HostMacBase::findParentModule()
{
    m_Parent=getParentModule();
    if(!m_Parent)
    {
        throw cRuntimeError("HostMacBase--Parent module not found");
    }
    else
    {
        EV_DEBUG<<this->getFullName()<<"'s parent is: "<<m_Parent->getFullName()<<endl;
    }
}

Coord HostMacBase::getCurrentPosition()
{
    cModule *mdMobilityOfHost = m_Parent->getSubmodule("mobility");
    IMobility *mdMovingMobilityOfHost = dynamic_cast<IMobility *>(mdMobilityOfHost);
    //EV<<"Host position: "<<mdMovingMobilityOfHost->getCurrentPosition()<<endl;
    return mdMovingMobilityOfHost->getCurrentPosition();
}

Coord HostMacBase::getBsPosition()
{
    cModule *mdMobilityOfBs = m_Bs->getSubmodule("mobility");
    IMobility *mdMovingMobilityOfBs = dynamic_cast<IMobility *>(mdMobilityOfBs);
    //EV<<"Ap position: "<<mdMovingMobilityOfAp->getCurrentPosition()<<endl;
    return mdMovingMobilityOfBs->getCurrentPosition();
}

double HostMacBase::getDistance()
{
    Coord cdHost=getCurrentPosition();
    Coord cdBs=getBsPosition();
    Coord cdDistance=cdHost-cdBs;

    return sqrt(cdDistance.x*cdDistance.x+cdDistance.y*cdDistance.y+cdDistance.z*cdDistance.z);

}
int HostMacBase::getPropagationSlots()
{
    double distance=getDistance();
    simtime_t stPropagationTime=distance/SPEED_OF_LIGHT;
    return ceil(stPropagationTime/m_SlotLength);

}

}




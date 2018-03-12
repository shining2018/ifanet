/*
 * ThreeWayRandomMobility.cc
 *
 *  Created on: 2017Äê12ÔÂ12ÈÕ
 *      Author: NETLAB
 */

#include "inet/mobility/single/ThreeWayRandomMobility.h"
#include "inet/common/INETMath.h"

namespace inet {

Define_Module(ThreeWayRandomMobility);

static const double stateMatrix[3][3]=
{
        {0.8,  0.1,  0.1},
        {0.3,  0.7,  0},
        {0.3,  0,    0.7}
};
ThreeWayRandomMobility::ThreeWayRandomMobility()
{
    r = -1;
    radius=-1;
    startAngle = 0;
    speed = 0;
    omega = 0;
    angle = 0;
    duration=0;
    margin=0;
    angleMean=0;
    isOutOfBorder=false;

}

void ThreeWayRandomMobility::initialize(int stage)
{
    MovingMobilityBase::initialize(stage);

    EV_TRACE << "initializing ThreeWayRandomMobility stage " << stage << endl;
    if (stage == INITSTAGE_LOCAL) {
        r = par("r");
        radius=par("radius");
        margin=par("margin");
        duration=par("duration");
        nextTransition=simTime()+duration;

        ASSERT(r > 0);
        startAngle = par("startAngle").doubleValue() / 180.0 * M_PI;
        EV_DEBUG<<"startAngle:"<<startAngle;
        angle=startAngle;
        speed = par("speed");
        omega = speed / r;
        stationary = (omega == 0);


    }
}

void ThreeWayRandomMobility::setInitialPosition()
{
    lastPosition.x=uniform(constraintAreaMin.x,constraintAreaMax.x);
    lastPosition.y=uniform(constraintAreaMin.y,constraintAreaMax.y);
    lastPosition.z=uniform(constraintAreaMin.z,constraintAreaMax.z);

    while(isBorderHugging())
    {
        lastPosition.x=uniform(constraintAreaMin.x,constraintAreaMax.x);
        lastPosition.y=uniform(constraintAreaMin.y,constraintAreaMax.y);
        lastPosition.z=uniform(constraintAreaMin.z,constraintAreaMax.z);
    }
}

void ThreeWayRandomMobility::move()
{
    if(isBorderHugging())
    {
        EV_DEBUG<<"Border hugging..."<<endl;

        if(isOutOfBorder==false)
        {
            if(randomValue>0.5)
            {
                cx=lastPosition.x-radius*cos(angle);
                cy=lastPosition.y+radius*sin(angle);
            }
            else
            {
                cx=lastPosition.x+radius*cos(angle);
                cy=lastPosition.y-radius*sin(angle);
            }
            EV_DEBUG<<"cx="<<cx<<", cy="<<cy<<endl;
        }

        isOutOfBorder=true;

        if(randomValue>0.5)
        {
            state=2;

            lastPosition.x = cx + radius * cos(angle);
            lastPosition.y = cy - radius * sin(angle);
            lastPosition.z = 0;

            angle = angle - omega * (simTime()-lastUpdate).dbl();
        }
        else
        {
            state=1;
            lastPosition.x = cx - radius * cos(angle);
            lastPosition.y = cy + radius * sin(angle);
            lastPosition.z = 0;

            angle = angle + omega * (simTime()-lastUpdate).dbl();

        }

        EV_DEBUG<<"isOutOfBorder="<<isOutOfBorder<<endl;
        EV_DEBUG<<"randomValue="<<randomValue<<endl;
        EV_DEBUG<<"state="<<state<<endl;
        EV_DEBUG<<"cx="<<cx<<", cy="<<cy<<endl;
        EV_DEBUG<<"lastPosition:"<<lastPosition<<endl;

    }
    else
    {
        EV_DEBUG<<"out of border..."<<endl;
        isOutOfBorder=false;

        if(simTime()>=nextTransition)
        {
            EV_DEBUG<<"exe if(simTime()>=nextTransition)"<<endl;
            nextTransition=simTime()+duration;
            EV_DEBUG<<"Current time "<<simTime()<<", and next transition is "<<nextTransition<<endl;

            state=getNextStateIndex();

            EV_DEBUG<<"Current state: "<<state<<endl;

            //turn left
            if(state==1)
            {
                cx=lastPosition.x+r*cos(angle);
                cy=lastPosition.y-r*sin(angle);
            }
            else
            {
                //turn right
                if(state==2)
                {
                    cx=lastPosition.x-r*cos(angle);
                    cy=lastPosition.y+r*sin(angle);
                }
            }
        }


        if(state==0)
        {
            lastSpeed.x = sin(angle) * speed;
            lastSpeed.y = cos(angle) * speed;
            lastSpeed.z=0;

            lastPosition+=lastSpeed*(simTime()-lastUpdate).dbl();
        }
        else
        {
            if(state==1)
            {
                lastPosition.x = cx - r * cos(angle);
                lastPosition.y = cy + r * sin(angle);
                lastPosition.z = 0;

                angle = angle + omega * (simTime()-lastUpdate).dbl();
            }
            else
            {
                if(state==2)
                {
                    lastPosition.x = cx + r * cos(angle);
                    lastPosition.y = cy - r * sin(angle);
                    lastPosition.z = 0;

                    angle = angle - omega * (simTime()-lastUpdate).dbl();
                }
            }

            lastSpeed.x = sin(angle) * speed;
            lastSpeed.y = cos(angle) * speed;
            lastSpeed.z = 0;
        }

        EV_DEBUG<<"state="<<state<<endl;
    }

    EV_DEBUG<<"after move, current position: "<<lastPosition<<endl;
}

int ThreeWayRandomMobility::getNextStateIndex()
{
        double sum=0;
        randomValue=dblrand();
        EV<<"random value:"<<randomValue<<endl;
        for(int i=0;i<3;i++)
        {
            sum+=stateMatrix[state][i];
            if(sum>=randomValue)
            {
                return i;
            }
        }
        EV_DEBUG<<"get next state index error! currentState= "<<state <<"random value = "<<randomValue<<endl;

        return state;
}


bool ThreeWayRandomMobility::isBorderHugging()
{
    bool left = (lastPosition.x < constraintAreaMin.x + margin);
    bool right = (lastPosition.x >= constraintAreaMax.x - margin);
    bool top = (lastPosition.y < constraintAreaMin.y + margin);
    bool bottom = (lastPosition.y >= constraintAreaMax.y - margin);
    return (left || right || top || bottom);
}

} // namespace inet



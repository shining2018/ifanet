/*
 * ThreeWayRandomMobility.h
 *
 *  Created on: 2017Äê12ÔÂ12ÈÕ
 *      Author: NETLAB
 */

#ifndef INET_MOBILITY_SINGLE_THREEWAYRANDOMMOBILITY_H_
#define INET_MOBILITY_SINGLE_THREEWAYRANDOMMOBILITY_H_
#include "inet/common/INETDefs.h"

#include "inet/mobility/base/MovingMobilityBase.h"

namespace inet {

/**
 * @brief Circle movement model. See NED file for more info.
 *
 * @ingroup mobility
 * @author Andras Varga
 */
class INET_API ThreeWayRandomMobility : public MovingMobilityBase
{
  protected:
    double r;
    double radius;
    double startAngle;
    double speed;
    /** @brief angular velocity [rad/s], derived from speed and radius. */
    double omega;
    int margin;
    double angleMean;

    /** @brief Direction from the center of the circle. */
    double angle;

    double duration;
    simtime_t nextTransition;

    double randomValue;
    int state=0;

    double cx=0;
    double cy=0;

    bool isOutOfBorder;


  protected:
    virtual int numInitStages() const override { return NUM_INIT_STAGES; }

    /** @brief Initializes mobility model parameters.*/
    virtual void initialize(int stage) override;

    /** @brief Initializes the position according to the mobility model. */
    virtual void setInitialPosition() override;

    /** @brief Move the host according to the current simulation time. */
    virtual void move() override;

    int getNextStateIndex();

    bool isBorderHugging();

  public:
    virtual double getMaxSpeed() const override { return speed; }
    ThreeWayRandomMobility();
};

} // namespace inet




#endif /* INET_MOBILITY_SINGLE_THREEWAYRANDOMMOBILITY_H_ */

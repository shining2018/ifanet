/*
 * StationaryMobility.h
 *
 *  Created on: 2018Äê1ÔÂ23ÈÕ
 *      Author: NETLAB
 */

#ifndef INET_MOBILITY_STATIC_STATIONARYMOBILITY_H_
#define INET_MOBILITY_STATIC_STATIONARYMOBILITY_H_

#include "inet/common/INETDefs.h"

#include "inet/mobility/base/MobilityBase.h"

namespace inet {

/**
 * This mobility module does not move at all; it can be used for standalone stationary nodes.
 *
 * @ingroup mobility
 * @author Andras Varga
 */
class INET_API StationaryMobility : public MobilityBase
{
  protected:
    /** @brief Never happens. */
    virtual void handleSelfMessage(cMessage *message) override;

  public:
    StationaryMobility()
    {
    }

    StationaryMobility(Coord position) { lastPosition = position; }

    /** @brief Returns the current position at the current simulation time. */
    virtual Coord getCurrentPosition() override { return lastPosition; }

    /** @brief Returns the current speed at the current simulation time. */
    virtual Coord getCurrentSpeed() override { return Coord::ZERO; }

    virtual double getMaxSpeed() const override { return 0; }

    virtual Coord getConstraintAreaMax() const override { return lastPosition; }
    virtual Coord getConstraintAreaMin() const override { return lastPosition; }
};

} // namespace inet




#endif /* INET_MOBILITY_STATIC_STATIONARYMOBILITY_H_ */

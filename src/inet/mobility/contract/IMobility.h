/*
 * IMobility.h
 *
 *  Created on: 2018Äê1ÔÂ23ÈÕ
 *      Author: NETLAB
 */

#ifndef INET_MOBILITY_CONTRACT_IMOBILITY_H_
#define INET_MOBILITY_CONTRACT_IMOBILITY_H_

#include "inet/common/INETDefs.h"

#include "inet/common/geometry/common/Coord.h"
#include "inet/common/geometry/common/EulerAngles.h"

namespace inet {

/**
 * @brief Abstract base class defining the public interface that must be provided by all mobility modules.
 *
 * @ingroup mobility
 * @author Levente Meszaros
 */
class INET_API IMobility
{
  public:
    /** @brief A signal used to publish mobility state changes. */
    static simsignal_t mobilityStateChangedSignal;

  public:
    virtual ~IMobility() {}

    /** @brief Returns the maximum possible speed at any future time. */
    virtual double getMaxSpeed() const = 0;

    /** @brief Returns the current position at the current simulation time. */
    virtual Coord getCurrentPosition() = 0;

    /** @brief Returns the current speed at the current simulation time. */
    virtual Coord getCurrentSpeed() = 0;

    /** @brief Returns the current acceleration at the current simulation time. */
    // virtual Coord getCurrentAcceleration() = 0;

    /** @brief Returns the current angular position at the current simulation time. */
    virtual EulerAngles getCurrentAngularPosition() = 0;

    /** @brief Returns the current angular speed at the current simulation time. */
    virtual EulerAngles getCurrentAngularSpeed() = 0;

    /** @brief Returns the current angular acceleration at the current simulation time. */
    // virtual Orientation getCurrentAngularAcceleration() = 0;

    virtual Coord getConstraintAreaMax() const = 0;
    virtual Coord getConstraintAreaMin() const = 0;
};

} // namespace inet



#endif /* INET_MOBILITY_CONTRACT_IMOBILITY_H_ */

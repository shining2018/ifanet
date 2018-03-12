/*
 * GeometricObjectBase.h
 *
 *  Created on: 2018Äê3ÔÂ12ÈÕ
 *      Author: NETLAB
 */

#ifndef INET_COMMON_GEOMETRY_BASE_GEOMETRICOBJECTBASE_H_
#define INET_COMMON_GEOMETRY_BASE_GEOMETRICOBJECTBASE_H_

#include "inet/common/INETDefs.h"

namespace inet {

/**
 * This class represents a 3 dimensional geometric object positioned and oriented
 * in 3 dimensional space.
 */
class INET_API GeometricObjectBase
{
  public:
    GeometricObjectBase() {}
    virtual ~GeometricObjectBase() {}

    /**
     * Returns true if this geometric object is the same as the unspecified
     * singleton instance of this type.
     */
    virtual bool isNil() const = 0;

    /**
     * Returns true if this geometric object is not completely specified.
     */
    virtual bool isUnspecified() const = 0;
};

} // namespace inet



#endif /* INET_COMMON_GEOMETRY_BASE_GEOMETRICOBJECTBASE_H_ */

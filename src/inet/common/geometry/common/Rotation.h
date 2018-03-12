/*
 * Rotation.h
 *
 *  Created on: 2018Äê1ÔÂ23ÈÕ
 *      Author: NETLAB
 */

#ifndef INET_COMMON_GEOMETRY_COMMON_ROTATION_H_
#define INET_COMMON_GEOMETRY_COMMON_ROTATION_H_

#include "inet/common/geometry/common/EulerAngles.h"
#include "inet/common/geometry/common/Coord.h"

namespace inet {

/*
 * This class efficiently computes the rotation of an arbitrary vector by an Euler Angle
 */
class INET_API Rotation
{
    protected:
        double rotationMatrix[3][3];
        void computeRotationMatrices(const double& q0, const double& q1, const double& q2, const double& q3);
        Coord matrixMultiplication(const double matrix[3][3], const Coord& vector) const;
        Coord matrixTransposeMultiplication(const double matrix[3][3], const Coord& vector) const;

    public:
        Rotation();
        Rotation(const EulerAngles& eulerAngle);
        Coord rotateVectorClockwise(const Coord& vector) const;
        Coord rotateVectorCounterClockwise(const Coord& vector) const;
};

} /* namespace inet */



#endif /* INET_COMMON_GEOMETRY_COMMON_ROTATION_H_ */

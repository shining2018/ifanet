/*
 * Rotation.cc
 *
 *  Created on: 2018Äê1ÔÂ23ÈÕ
 *      Author: NETLAB
 */

#include "inet/common/geometry/common/Rotation.h"

namespace inet {

Rotation::Rotation(const EulerAngles& eulerAngle)
{
    // Note that, we don't need to use our Quaternion class since we don't use its operators
    double q0 = cos(eulerAngle.alpha/2) * cos(eulerAngle.beta/2) * cos(eulerAngle.gamma/2) +
                sin(eulerAngle.alpha/2) * sin(eulerAngle.beta/2) * sin(eulerAngle.gamma/2);
    double q1 = sin(eulerAngle.alpha/2) * cos(eulerAngle.beta/2) * cos(eulerAngle.gamma/2) -
                cos(eulerAngle.alpha/2) * sin(eulerAngle.beta/2) * sin(eulerAngle.gamma/2);
    double q2 = cos(eulerAngle.alpha/2) * sin(eulerAngle.beta/2) * cos(eulerAngle.gamma/2) +
                sin(eulerAngle.alpha/2) * cos(eulerAngle.beta/2) * sin(eulerAngle.gamma/2);
    double q3 = cos(eulerAngle.alpha/2) * cos(eulerAngle.beta/2) * sin(eulerAngle.gamma/2) -
                sin(eulerAngle.alpha/2) * sin(eulerAngle.beta/2) * cos(eulerAngle.gamma/2);
    computeRotationMatrices(q0, q1, q2, q3);
}

void Rotation::computeRotationMatrices(const double& q0, const double& q1, const double& q2, const double& q3)
{
    // Ref: http://en.wikipedia.org/wiki/Conversion_between_quaternions_and_Euler_angles
    rotationMatrix[0][0] = 1 - 2*(q2*q2 + q3*q3);
    rotationMatrix[0][1] = 2*(q1*q2 - q0*q3);
    rotationMatrix[0][2] = 2*(q0*q2 + q1*q3);
    rotationMatrix[1][0] = 2*(q1*q2 + q0*q3);
    rotationMatrix[1][1] = 1 - 2*(q1*q1 + q3*q3);
    rotationMatrix[1][2] = 2*(q2*q3 - q0*q1);
    rotationMatrix[2][0] = 2*(q1*q3 - q0*q2);
    rotationMatrix[2][1] = 2*(q0*q1 + q2*q3);
    rotationMatrix[2][2] = 1 - 2*(q1*q1 + q2*q2);
}

Coord Rotation::rotateVectorClockwise(const Coord& vector) const
{
    return matrixMultiplication(rotationMatrix, vector);
}

Rotation::Rotation()
{
    // identity matrix
    rotationMatrix[0][0] = 1;
    rotationMatrix[0][1] = rotationMatrix[0][2] = 0;
    rotationMatrix[1][1] = 1;
    rotationMatrix[1][0] = rotationMatrix[1][2] = 0;
    rotationMatrix[2][2] = 1;
    rotationMatrix[2][1] = rotationMatrix[2][0] = 0;
}

Coord Rotation::rotateVectorCounterClockwise(const Coord& vector) const
{
    return matrixTransposeMultiplication(rotationMatrix, vector);
}

Coord Rotation::matrixMultiplication(const double matrix[3][3], const Coord& vector) const
{
    return Coord(
            vector.x * matrix[0][0] + vector.y * matrix[0][1] + vector.z * matrix[0][2],
            vector.x * matrix[1][0] + vector.y * matrix[1][1] + vector.z * matrix[1][2],
            vector.x * matrix[2][0] + vector.y * matrix[2][1] + vector.z * matrix[2][2]);
}

Coord Rotation::matrixTransposeMultiplication(const double matrix[3][3], const Coord& vector) const
{
    return Coord(
            vector.x * matrix[0][0] + vector.y * matrix[1][0] + vector.z * matrix[2][0],
            vector.x * matrix[0][1] + vector.y * matrix[1][1] + vector.z * matrix[2][1],
            vector.x * matrix[0][2] + vector.y * matrix[1][2] + vector.z * matrix[2][2]);
}

} /* namespace inet */




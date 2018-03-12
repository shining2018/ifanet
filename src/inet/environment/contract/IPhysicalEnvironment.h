/*
 * IPhysicalEnvironment.h
 *
 *  Created on: 2018Äê1ÔÂ23ÈÕ
 *      Author: NETLAB
 */

#ifndef INET_ENVIRONMENT_CONTRACT_IPHYSICALENVIRONMENT_H_
#define INET_ENVIRONMENT_CONTRACT_IPHYSICALENVIRONMENT_H_

#include "inet/common/IVisitor.h"
#include "inet/common/geometry/common/Coord.h"
#include "inet/common/geometry/common/Rotation.h"
#include "inet/common/geometry/common/EulerAngles.h"
#include "inet/environment/contract/IPhysicalObject.h"
#include "inet/environment/contract/IMaterialRegistry.h"

namespace inet {

namespace physicalenvironment {

class INET_API IPhysicalEnvironment
{
  public:
    virtual const Coord& getSpaceMin() const = 0;
    virtual const Coord& getSpaceMax() const = 0;
    virtual const EulerAngles& getViewAngle() const = 0;
    virtual const Rotation& getViewRotation() const = 0;
    virtual const cFigure::Point& getViewTranslation() const = 0;
    virtual const IMaterialRegistry *getMaterialRegistry() const = 0;

    virtual void visitObjects(const IVisitor *visitor, const LineSegment& lineSegment) const = 0;

    static cFigure::Point computeCanvasPoint(const Coord& point, const Rotation& rotation, const cFigure::Point& translation)
    {
        Coord rotatedPoint = rotation.rotateVectorClockwise(point);
        return cFigure::Point(rotatedPoint.x + translation.x, rotatedPoint.y + translation.y);
    }

    static cFigure::Point computeCanvasPoint(Coord point)
    {
        IPhysicalEnvironment *environment = dynamic_cast<IPhysicalEnvironment *>(getSimulation()->getSystemModule()->getSubmodule("environment"));
        if (environment != nullptr)
            return computeCanvasPoint(point, environment->getViewRotation(), environment->getViewTranslation());
        else
            return computeCanvasPoint(point, Rotation(EulerAngles(0,0,0)), cFigure::Point(0, 0));
    }
};

} // namespace physicalenvironment

} // namespace inet



#endif /* INET_ENVIRONMENT_CONTRACT_IPHYSICALENVIRONMENT_H_ */

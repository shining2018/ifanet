/*
 * IVisitor.h
 *
 *  Created on: 2018Äê1ÔÂ23ÈÕ
 *      Author: NETLAB
 */

#ifndef INET_COMMON_IVISITOR_H_
#define INET_COMMON_IVISITOR_H_

#include "inet/common/INETDefs.h"

namespace inet {

// This is the interface for data structure visitors
class INET_API IVisitor
{
    public:
        virtual void visit(const cObject *) const = 0;
        virtual ~IVisitor() {}
};

} /* namespace inet */



#endif /* INET_COMMON_IVISITOR_H_ */

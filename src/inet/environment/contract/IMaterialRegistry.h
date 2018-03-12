/*
 * IMaterialRegistry.h
 *
 *  Created on: 2018Äê1ÔÂ23ÈÕ
 *      Author: NETLAB
 */

#ifndef INET_ENVIRONMENT_CONTRACT_IMATERIALREGISTRY_H_
#define INET_ENVIRONMENT_CONTRACT_IMATERIALREGISTRY_H_

#include "inet/environment/common/Material.h"

namespace inet {

namespace physicalenvironment {

class INET_API IMaterialRegistry
{
  public:
    virtual const Material *getMaterial(const char *name) const = 0;
};

} // namespace physicalenvironment

} // namespace inet



#endif /* INET_ENVIRONMENT_CONTRACT_IMATERIALREGISTRY_H_ */

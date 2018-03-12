/*
 * ModuleAccess.h
 *
 *  Created on: 2018Äê3ÔÂ12ÈÕ
 *      Author: NETLAB
 */

#ifndef INET_COMMON_MODULEACCESS_H_
#define INET_COMMON_MODULEACCESS_H_

#include "inet/common/INETDefs.h"
//#include "inet/networklayer/contract/IInterfaceTable.h"

namespace inet {

/**
 * Returns true if the given module is a network node, i.e. a module
 * with the @networkNode property set.
 */
INET_API bool isNetworkNode(cModule *mod);

/**
 * Find a module with given name, and "closest" to module "from".
 *
 * Operation: gradually rises in the module hierarchy, and looks for a submodule
 * of the given name.
 */
INET_API cModule *findModuleSomewhereUp(const char *name, cModule *from);

/**
 * Find the node containing the given module.
 * Returns nullptr, if no containing node.
 */
INET_API cModule *findContainingNode(cModule *from);

/**
 * Find the node containing the given module.
 * throws error if no containing node.
 */
INET_API cModule *getContainingNode(cModule *from);

/**
 * Find the ancestor module under the node containing the given module.
 * Returns nullptr, if no such node found.
 */
INET_API cModule *findModuleUnderContainingNode(cModule *from);

/**
 * Finds a module in the module tree, given by its absolute or relative path
 * defined by 'par' parameter.
 * Returns nullptr if the 'par' parameter is empty.
 * Returns the pointer to a module of type T or throws an error if module not found
 * or type mismatch.
 */
template<typename T>
INET_API T *findModuleFromPar(cPar& par, cModule *from, bool required = true);

template<typename T>
T *findModuleFromPar(cPar& par, cModule *from, bool required)
{
    const char *path = par.stringValue();
    if (path && *path) {
        cModule *mod = from->getModuleByPath(path);
        if (!mod) {
            if (required)
                throw cRuntimeError("Module not found on path '%s' defined by par '%s'", path, par.getFullPath().c_str());
            else
                return nullptr;
        }
        T *m = dynamic_cast<T *>(mod);
        if (!m)
            throw cRuntimeError("Module can not cast to '%s' on path '%s' defined by par '%s'", opp_typename(typeid(T)), path, par.getFullPath().c_str());
        return m;
    }
    return nullptr;
}

/**
 * Gets a module in the module tree, given by its absolute or relative path
 * defined by 'par' parameter.
 * Returns the pointer to a module of type T or throws an error if module not found
 * or type mismatch.
 */
template<typename T>
INET_API T *getModuleFromPar(cPar& par, cModule *from, bool required = true);

template<typename T>
T *getModuleFromPar(cPar& par, cModule *from, bool required)
{
    const char *path = par.stringValue();
    cModule *mod = from->getModuleByPath(path);
    if (!mod) {
        if (required)
            throw cRuntimeError("Module not found on path '%s' defined by par '%s'", path, par.getFullPath().c_str());
        else
            return nullptr;
    }
    T *m = dynamic_cast<T *>(mod);
    if (!m)
        throw cRuntimeError("Module can not cast to '%s' on path '%s' defined by par '%s'", opp_typename(typeid(T)), path, par.getFullPath().c_str());
    return m;
}

} // namespace inet



#endif /* INET_COMMON_MODULEACCESS_H_ */

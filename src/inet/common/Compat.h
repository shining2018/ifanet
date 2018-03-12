/*
 * Compat.h
 *
 *  Created on: 2018Äê3ÔÂ12ÈÕ
 *      Author: NETLAB
 */

#ifndef INET_COMMON_COMPAT_H_
#define INET_COMMON_COMPAT_H_

#ifdef EV_GLOBAL_STREAM
// TODO: compiles but it doesn't do what it supposed to do
cLogStream cLogStream::globalStream;
#endif // ifdef EV_GLOBAL_STREAM

#include <iostream>
#include <omnetpp.h>

namespace omnetpp { }  // so "using namespace omnetpp" in INETDefs.h doesn't cause error for OMNeT++ 4.x

namespace inet {

    typedef uint64_t uint64;
    typedef int64_t  int64;
    typedef uint32_t uint32;
    typedef int32_t  int32;
    typedef uint16_t uint16;
    typedef int16_t  int16;
    typedef uint8_t  uint8;

#  define EVSTREAM                      EV

#ifdef _MSC_VER
// complementary error function, not in MSVC
double INET_API erfc(double x);

// ISO C99 function, not in MSVC
inline long lrint(double x)
{
    return (long)floor(x + 0.5);
}

// ISO C99 function, not in MSVC
inline double fmin(double a, double b)
{
    return a < b ? a : b;
}

// ISO C99 function, not in MSVC
inline double fmax(double a, double b)
{
    return a > b ? a : b;
}

//
// Implementation of the error function, from the Mobility Framework
//
// Unfortunately the windows math library does not provide an
// implementation of the error function, so we use an own
// implementation (Thanks to Jirka Klaue)
// Author Jirka Klaue
//
double INET_API erfc(double x)
{
    double t, u, y;

    if (x <= -6)
        return 2;
    if (x >= 6)
        return 0;

    t = 3.97886080735226 / (fabs(x) + 3.97886080735226);
    u = t - 0.5;
    y = (((((((((0.00127109764952614092 * u + 1.19314022838340944e-4) * u
                - 0.003963850973605135) * u - 8.70779635317295828e-4) * u
              + 0.00773672528313526668) * u + 0.00383335126264887303) * u
            - 0.0127223813782122755) * u - 0.0133823644533460069) * u
          + 0.0161315329733252248) * u + 0.0390976845588484035) * u
        + 0.00249367200053503304;
    y = ((((((((((((y * u - 0.0838864557023001992) * u
                   - 0.119463959964325415) * u + 0.0166207924969367356) * u
                 + 0.357524274449531043) * u + 0.805276408752910567) * u
               + 1.18902982909273333) * u + 1.37040217682338167) * u
             + 1.31314653831023098) * u + 1.07925515155856677) * u
           + 0.774368199119538609) * u + 0.490165080585318424) * u
         + 0.275374741597376782) * t * exp(-x * x);

    return x < 0 ? 2 - y : y;
}

#endif    // _MSC_VER


} // namespace inet



#endif /* INET_COMMON_COMPAT_H_ */

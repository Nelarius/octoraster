#ifndef INT_H
#define INT_H

#ifdef _MSC_VER
    typedef __int32 int32_t;
    typedef unsigned __int32 uint32_t;
#else
    #include <stdint.h>
#endif

#endif
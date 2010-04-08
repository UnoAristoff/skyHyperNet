#ifndef _ahn_types_h
#define _ahn_types_h

typedef unsigned int   Uint32;
typedef unsigned short Uint16;

enum IServType {
ServLog,
ServFile,
ServScreen,

ServLast,
ServCustom = ServLast + 1
};

#endif

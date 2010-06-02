#ifndef _ahn_types_h
#define _ahn_types_h

typedef unsigned int   Uint32;
typedef unsigned short Uint16;

enum tServType {
tServLog = 1,
tServFile,
tServGra,
tServSnd,

tServLast,
tServCustom
};


///// GEOMETRIC

struct rect_dat{
    unsigned int width;
    unsigned int height;
};

#endif

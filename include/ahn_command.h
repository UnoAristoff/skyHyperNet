#ifndef _command_h
#define _command_h

typedef unsigned int UID;
typedef unsigned int NUC;   // Number Of Operation

struct ahn_command_head {
    UID from;
    UID to;
    NUC operation;
    unsigned int size;
};

#endif

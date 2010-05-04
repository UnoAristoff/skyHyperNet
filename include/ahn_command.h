#ifndef _command_h
#define _command_h

typedef unsigned int UID;
typedef unsigned int NOP;   // Number Of Operation

struct ahn_command_head {
    UID from;
    UID to;
    NOP operation;
};

#endif

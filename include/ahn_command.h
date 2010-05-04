#ifndef _command_h
#define _command_h

typedef int UID;
typedef int NOP;   // Number Of Operation

struct ahn_command_head {
    UID from;
    UID to;
    NOP operation;
};

#endif

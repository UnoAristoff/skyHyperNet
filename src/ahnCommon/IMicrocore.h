#ifndef _I_MICROCORE_H
#define _I_MICROCORE_H

#include "ahn_types.h"
#include "IService.h"

#include "ahn_command.h"

class IMicrocore {

public:

    virtual int Init(Uint16 port)=0;
    virtual int Start(bool loop)=0;
    virtual int Release()=0;

    virtual UID GetUID(const char* ServName)=0;
    virtual bool SendCommand( ahn_command_head& head, void* data )=0;

};

#endif

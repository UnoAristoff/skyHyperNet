#ifndef _I_SERVICE_H
#define _I_SERVICE_H

#include "ahn_types.h"
#include "ahn_command.h"

class IMicrocore;

class IService {

public:

    virtual bool CallFunc( ahn_command_head& head, void* data)=0;
//    virtual bool CallFunc( void* ptr, long size )=0;

    virtual const char *getName()=0;
    virtual tServType getType()=0;
    virtual void Release()=0;

    virtual void setUID(UID id, IMicrocore* p_Core)=0;
    virtual UID getUID()=0;

};

#endif

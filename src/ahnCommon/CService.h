#ifndef _C_SERVICE_H
#define _C_SERVICE_H

#include "IMicrocore.h"
#include "IService.h"
#include <vector>

class CService: public IService {

typedef bool (CService::*CALLFUNC)( ahn_command_head& head, void* data, int size);

public:

    CService();
    virtual ~CService();

    bool CallFunc( ahn_command_head& head, void* data, int size);

    bool TestFunc1( ahn_command_head& head, void* data, int size);
    bool TestFunc2( ahn_command_head& head, void* data, int size);
    bool TestFunc3( ahn_command_head& head, void* data, int size);

    virtual const char *getName()=0;
    virtual tServType getType()=0;
    virtual void Release()=0;

    void setUID(UID id, IMicrocore* pCore){ myID=id; myCore=pCore; }
    UID getUID(){ return myID; }

protected:

    IMicrocore* myCore;
    UID myID;

    void RegFunc( CALLFUNC &func_ptr );
    NUC num_func;
    CALLFUNC func_list[10];

};

#endif

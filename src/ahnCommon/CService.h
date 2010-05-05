#ifndef _C_SERVICE_H
#define _C_SERVICE_H

#include "IService.h"
#include "IMicrocore.h"
#include <vector>

//typedef bool (*GETCORELIB)( void* data, int size );

class CService: public IService {

//friend class CMicrocore;

public:

    CService();
    virtual ~CService();

    bool CallFunc( ahn_command_head& head, void* data, int size);

    virtual const char *getName()=0;
    virtual tServType getType()=0;
    virtual void Release()=0;

    void setUID(UID id, IMicrocore* pCore){ myID=id; myCore=pCore; }
    UID getUID(){ return myID; }

    bool TestFunc( ahn_command_head& head, void* data, int size );

protected:

    IMicrocore* myCore;
    UID myID;
    void RegFunc( void* func_ptr );
    std::vector<void*> func_list;

};

#endif

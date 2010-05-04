#ifndef _C_SERVICE_H
#define _C_SERVICE_H

#include "IService.h"
#include <vector>

class CService: public IService {

//friend class CMicrocore;

public:

    CService();
    virtual ~CService();

    bool CallFunc( ahn_command_head& head, void* data, int size);

    virtual const char *getName()=0;
    virtual IServType getType()=0;
    virtual void Release()=0;

    void setUID(UID id){ myID=id; }
    UID getUID(){ return myID; }

protected:

    UID myID;
    void RegFunc( void* func_ptr );
    std::vector<void*> func_list;

};

#endif

#ifndef _I_MICROCORE_H
#define _I_MICROCORE_H

#include "ahn_types.h"
#include "IService.h"

class IMicrocore {

public:

    virtual int Init(Uint16 port)=0;
    virtual int Start(bool loop)=0;
    virtual int Release()=0;

    virtual void regService( IService* newService )=0;
    virtual IService* getService( IServType servType )=0;

};

#endif

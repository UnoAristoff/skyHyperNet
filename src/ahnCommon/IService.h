#ifndef _I_SERVICE_H
#define _I_SERVICE_H

#include "ahn_types.h"

class IService {

public:

    virtual const char *getName()=0;
    virtual IServType getType()=0;
    virtual void Release()=0;

};

#endif

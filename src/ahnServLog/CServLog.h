#ifndef _C_SERVLOG_H
#define _C_SERVLOG_H

#include "CService.h"

class CServLog: public CService {

    public:

//    bool CallFunc( void* ptr, long size );

        const char *getName(){ return "ServLog"; }
        IServType getType(){ return ServLog; }
        void Release(){ delete this; }

        CServLog();
        ~CServLog();


};

#endif

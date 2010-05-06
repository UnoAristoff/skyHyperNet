#ifndef _C_SERVLOG_H
#define _C_SERVLOG_H

#include "CService.h"

class CServLog: public CService {

    public:

//    bool CallFunc( void* ptr, long size );

        const char *getName(){ return "ServLog"; }
        tServType getType(){ return tServLog; }
        void Release(){ delete this; }

        bool ServLogFunc( ahn_command_head& head, void* data, int size );

        CServLog();
        ~CServLog();


};

#endif

#ifndef _C_SERVLOG_H
#define _C_SERVLOG_H

#include "TService.h"
#include <string>
#include <stdio.h>

class CServLog: public TService<CServLog> {

    public:
//    bool CallFunc( void* ptr, long size );
        const char *getName(){ return "ServLog"; }
        tServType getType(){ return tServLog; }
        void Release(){ delete this; }

	bool LogMsg( ahn_command_head& head, void* data );
	bool ErrMsg( ahn_command_head& head, void* data );

//        bool ServLogFunc1( ahn_command_head& head, void* data, int size );
//        bool ServLogFunc2( ahn_command_head& head, void* data, int size );
//        bool ServLogFunc3( ahn_command_head& head, void* data, int size );
//        bool ServLogFunc4( ahn_command_head& head, void* data, int size );

        CServLog();
        ~CServLog();

    protected:

	std::string LogName;
	FILE* log_file;
};

#endif

#ifndef _C_SERVFILE_H
#define _C_SERVFILE_H

#include "TService.h"
#include <string>
#include <stdio.h>

class CServFile: public TService<CServFile> {

    public:

        const char *getName(){ return "ServFile"; }
        tServType getType(){ return tServFile; }
        void Release(){ delete this; }

//	bool LogMsg( ahn_command_head& head, void* data );
//	bool ErrMsg( ahn_command_head& head, void* data );

//        bool ServLogFunc1( ahn_command_head& head, void* data, int size );
//        bool ServLogFunc2( ahn_command_head& head, void* data, int size );
//        bool ServLogFunc3( ahn_command_head& head, void* data, int size );
//        bool ServLogFunc4( ahn_command_head& head, void* data, int size );

        CServFile();
        ~CServFile();

    protected:

//	std::string LogName;
//	FILE* log_file;
};

#endif

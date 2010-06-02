#ifndef _C_SERVGRA_H
#define _C_SERVGRA_H

#include "TService.h"
#include <string>
#include <stdio.h>

class CServGra: public TService<CServGra> {

    public:

        const char *getName(){ return "ServGra"; }
        tServType getType(){ return tServGra; }
        void Release(){ delete this; }

	bool  AddWindow( ahn_command_head& head, void* data );
	bool  DelWindow( ahn_command_head& head, void* data );

        CServGra();
        ~CServGra();

    protected:

//	std::string LogName;
//	FILE* log_file;
};

#endif

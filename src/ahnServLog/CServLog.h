#ifndef _C_SERVLOG_H
#define _C_SERVLOG_H

#include "IService.h"

class CServLog: public IService {

    public:

        const char *getName(){ return "ServLog"; }
        IServType getType(){ return ServLog; }
	void Release(){ delete this; }

	CServLog();
	virtual ~CServLog();


};

#endif

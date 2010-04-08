#include <stdio.h>
#include <iostream.h>

#include "CMicrocore.h"
#include "plug_loader.h"

static CMicrocore* _myCore=NULL;

void get_mod(void* mod_ptr){

    _myCore->regService( (IService*) mod_ptr );

}

IMicrocore* GetCore(){

    if (_myCore) return _myCore;

    _myCore = new CMicrocore();
    _myCore->Init(9099);

    scan_mod( "services" ); // load services
    return _myCore;

}

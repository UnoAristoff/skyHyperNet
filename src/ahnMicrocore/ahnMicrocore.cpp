#ifdef _WIN32
#include <windows.h>
#endif

#include <stdio.h>
#include <iostream.h>

#include "CMicrocore.h"
#include "plug_loader.h"

CMicrocore* _myCore=NULL;

void get_mod(void* mod_ptr){

    cout << "get mod " << endl;
    _myCore->regService( (IService*) mod_ptr );
    cout << "get mod ok" << endl;
}

extern "C"
#ifdef _WIN32
    __declspec(dllexport)
#endif
    void GetCore( IMicrocore** ppCore )
{
//    *ppOutput = new CEngine();
//};
//extern "C"
//#ifdef _WIN32
//    __declspec(dllexport)
//#endif
//IMicrocore* GetCore(){

//    if (_myCore) { *ppCore = _myCore; return; }

    _myCore = new CMicrocore();
    _myCore->Init(9099);

    scan_mod( "services" ); // load services

    cout << "scan end" << endl;
    *ppCore = _myCore;

}

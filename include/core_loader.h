#ifndef _core_loader_h
#define _core_loader_h

#include "IMicrocore.h"
//#include <dirent.h>
//#include <sys/stat.h>

#ifndef _WIN32
#include <dlfcn.h>
#else
#include <windows.h>
#endif

static IMicrocore* _myCore=NULL;
void *library_handler =NULL;

typedef void (*GETCORELIB)( IMicrocore** );

//typedef IMicrocore* (*GETCORELIB)( void );
//void* (IMicrocore* *GetCoreLib)(void);
//void GetCore( IMicrocore** ppCore )
void FreeCore(){

if (_myCore) _myCore->Release();

if (library_handler) {
    #ifndef _WIN32
    dlclose(library_handler);
    #else
    FreeLibrary( (HINSTANCE)library_handler);
    #endif
    }
}
IMicrocore* GetCore(){

if (_myCore) return _myCore;

#ifndef _WIN32
const char *ModuleName="./lib_ahnMicrocore.so";
#else
const char *ModuleName="./ahnMicrocore.dll";
#endif

#ifndef _WIN32
    library_handler = dlopen(ModuleName,RTLD_NOW);
   if (!library_handler){
    fprintf(stderr,"dlopen() error: %s\n", dlerror());
    return NULL;
    }
#else
    library_handler = LoadLibrary(ModuleName);
    if (!library_handler) return NULL;
#endif

//IMicrocore* GetCore(){

#ifndef _WIN32
    GETCORELIB func_p=(GETCORELIB)dlsym(library_handler, "GetCore");
#else
    GETCORELIB func_p=(GETCORELIB)GetProcAddress( (HINSTANCE)library_handler, "GetCore" );
#endif

//    GETCORELIB GetCoreLib = (GETCORELIB)func_p;
//    IMicrocore* myCore = GetCoreLib();
	func_p( & _myCore );

    return _myCore;
//    return GetCoreLib();

}

#endif

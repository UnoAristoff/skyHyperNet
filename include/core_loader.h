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

typedef void (*GETCORELIB)( IMicrocore** );

//typedef IMicrocore* (*GETCORELIB)( void );
//void* (IMicrocore* *GetCoreLib)(void);
//void GetCore( IMicrocore** ppCore )

IMicrocore* GetCore(){

    if (_myCore) return _myCore;

#ifndef _WIN32
const char *ModuleName="./lib_ahnMicrocore.so";
#else
const char *ModuleName="./ahnMicrocore.dll";
#endif

#ifndef _WIN32
    void *library_handler = dlopen(ModuleName,RTLD_NOW);
#else
    void *library_handler = LoadLibrary(ModuleName);
#endif

    if (!library_handler){
    fprintf(stderr,"dlopen() error: %s\n", dlerror());
    return NULL;
    }

//IMicrocore* GetCore(){

#ifndef _WIN32
    GETCORELIB func_p=(GETCORELIB)dlsym(library_handler, "GetCore");
#else
    GETCORELIB func_p=(GETCORELIB)GetProcAddress( (HINSTANCE)handl, "GetCore" );
#endif

//    GETCORELIB GetCoreLib = (GETCORELIB)func_p;
//    IMicrocore* myCore = GetCoreLib();
	func_p( & _myCore );

#ifndef _WIN32
dlclose(library_handler);
#else
FreeLibrary( (HINSTANCE)library_handler);
#endif

    return _myCore;
//    return GetCoreLib();

}

#endif

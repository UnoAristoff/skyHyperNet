#ifdef _WIN32
#include <windows.h>
#endif

#include "CServLog.h"

extern "C"
#ifdef _WIN32
    __declspec(dllexport)
#endif
void GetService( IService** ppService )
{
    *ppService = new CServLog();
};

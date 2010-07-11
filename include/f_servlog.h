#ifndef f_servlog_h
#define f_servlog_h

#include "ahn_servlog.h"
#include <string.h>

#include <stdarg.h>

extern IMicrocore* pCore;

inline bool LogMsg( const char* Msg, ... ){

    UID myLog = pCore->GetUID("ServLog");
    if (!myLog) return false;
//cout << "Msg" << endl;
    char str[1024]; memset(str, 0, 1024);

    va_list args;  va_start(args, Msg);
    vsnprintf( str, 1024-1, Msg, args);

    ahn_command_head my_command;
    my_command.from = myLog;
    my_command.to = myLog;
    my_command.operation = FLogMsg;
    my_command.size = strlen(str)+1;

    return pCore->SendCommand( my_command, (void*)str );

    };

inline bool ErrMsg( const char* Msg, ... ){

    UID myLog = pCore->GetUID("ServLog");
    if (!myLog) return false;

    char str[1024]; memset(str, 0, 1024);

    va_list args;  va_start(args, Msg);
    vsnprintf( str, 1024-1, Msg, args);

    ahn_command_head my_command;
    my_command.from = myLog;
    my_command.to = myLog;
    my_command.operation = FErrMsg;
    my_command.size = strlen(str)+1;

    return pCore->SendCommand( my_command, (void*)str );

    };

#endif

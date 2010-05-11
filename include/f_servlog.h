#ifndef f_servlog_h
#define f_servlog_h

#include "ahn_servlog.h"
#include <string>

extern IMicrocore* myCore;

inline bool LogMsg( const char* Msg ){

    UID myLog = myCore->GetUID("ServLog");
//    cout << "myLog ID : " << myLog << endl;
    if (!myLog) return false;

    ahn_command_head my_command;
    my_command.from = myLog;
    my_command.to = myLog;
    my_command.operation = FLogMsg;

    return myCore->SendCommand( my_command, (void*)Msg, strlen(Msg) );

    };


inline bool ErrMsg( const char* Msg ){

    UID myLog = myCore->GetUID("ServLog");
//    cout << "myLog ID : " << myLog << endl;
    if (!myLog) return false;

    ahn_command_head my_command;
    my_command.from = myLog;
    my_command.to = myLog;
    my_command.operation = FErrMsg;

    return myCore->SendCommand( my_command, (void*)Msg, strlen(Msg) );

    };

#endif

#ifndef f_servsnd_h
#define f_servsnd_h

#include "ahn_servsnd.h"
#include <string>

extern IMicrocore* myCore;

inline bool PlayFX( const char* fx_name ){

    UID myLog = myCore->GetUID("ServSnd");
    if (!myLog) return false;

    ahn_command_head my_command;
    my_command.from = myLog;
    my_command.to = myLog;
    my_command.operation = FPlayFX;
    my_command.size = strlen(fx_name+1);

    return myCore->SendCommand( my_command, (void*)fx_name );

    };


inline bool PlayMusic( const char* mus_name ){

    UID myLog = myCore->GetUID("ServSnd");
    if (!myLog) return false;

    ahn_command_head my_command;
    my_command.from = myLog;
    my_command.to = myLog;
    my_command.operation = FPlayMusic;
    my_command.size = strlen(mus_name)+1;

    return myCore->SendCommand( my_command, (void*)mus_name );

    };

#endif

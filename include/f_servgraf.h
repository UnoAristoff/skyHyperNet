#ifndef f_servgraf_h
#define f_servgraf_h

#include "ahn_servgraf.h"
#include <string>

#include <ahn_types.h>
#include <stdarg.h>

extern IMicrocore* pCore;

inline bool AddWindow( unsigned int width, unsigned int height ){

    UID myID = pCore->GetUID("ServGraf");
    if (!myID) return false;

    rect_dat myRect;
    myRect.width = width;
    myRect.height = height;

    ahn_command_head my_command;
    my_command.from = myID;
    my_command.to = myID;
    my_command.operation = FAddWindow;
    my_command.size = sizeof(myRect);

    return pCore->SendCommand( my_command, (void*)&myRect );

    };

inline bool DelWindow( UID winID ){

    UID myID = pCore->GetUID("ServGraf");
    if (!myID) return false;

    ahn_command_head my_command;
    my_command.from = myID;
    my_command.to = myID;
    my_command.operation = FAddWindow;
    my_command.size = sizeof(winID);

    return pCore->SendCommand( my_command, (void*)&winID );

}

#endif

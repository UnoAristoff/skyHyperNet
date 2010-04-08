#ifndef _C_MICROCORE_H
#define _C_MICROCORE_H

#include "IMicrocore.h"
#include <map>

#include "SDL/SDL.h"
#include "SDL/SDL_net.h"
#include "SDL/SDL_thread.h"

struct CNetworkListener{
    IPaddress ip;
    TCPsocket socket;
};

class CMicrocore: public IMicrocore {
    public:

    CMicrocore();

    int Init(Uint16 port);
    int Start(bool loop);
    int Release();

    IService* getService( IServType servType );
    void regService( IService* newService );

    int Process(); // return status

    protected:

    ~CMicrocore();
    int GetMsg(TCPsocket socket, char *buffer, int buf_size);
    int PutMsg(TCPsocket socket, char *buffer, int buf_size);

    int status; // 1 - created, 2 - initialized, 0 - exit
    SDL_Thread* coreThread;

    CNetworkListener Listener;
    SDLNet_SocketSet set;

    std::map<IServType, IService*> ServiceList;

};

#endif
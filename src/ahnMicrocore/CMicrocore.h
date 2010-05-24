#ifndef _C_MICROCORE_H
#define _C_MICROCORE_H

#include "IMicrocore.h"
#include <string>
#include <vector>
#include <map>

#include "SDL/SDL.h"
#include "SDL/SDL_net.h"
#include "SDL/SDL_thread.h"

#include "IService.h"
//#include "TList.h"

struct CNetworkListener{
    IPaddress ip;
    TCPsocket socket;
};

//typedef TService<IService> CService; // pseudo-class :)

class CMicrocore: public IMicrocore {
    public:

    CMicrocore();

    int Init(Uint16 port);
    int Start(bool loop);
    int Release();

    UID GetUID(tServType serv_type);
    UID GetUID(const char* serv_name);

//    UID GetUID(const char* ServName);
    bool SendCommand( ahn_command_head& head, void* data );

//    IService* getService( IServType servType );
    void regService( IService* myService );
    void unrService( UID servID );

    int Process(); // return status

    protected:

    Uint16 ext_port;

    bool CheckID( UID testID ); // true - valid, false - not valid

    virtual ~CMicrocore();
    int GetMsg(TCPsocket socket, char *buffer, unsigned int buf_size);
    int PutMsg(TCPsocket socket, char *buffer, unsigned int buf_size);
//    TCPsocket Connect(const char* ServerName, Uint16 port);

    int status; // 1 - created, 2 - initialized, 0 - exit
    SDL_Thread* coreThread;

    CNetworkListener Listener;
    CNetworkListener Sender;
//    TCPsocket accept_s;

    SDLNet_SocketSet set;

    std::vector< IService* > ServiceList;          // for UID
    std::map<tServType, IService* > ServiceList_t; // for types
    std::map<std::string, IService* > ServiceList_n; // for names

//    TLeaf* topLeaf;
//    TLeaf* curLeaf;

};

#endif

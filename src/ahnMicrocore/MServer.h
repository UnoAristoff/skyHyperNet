#ifndef _M_SERVER_H
#define _M_SERVER_H

#include <list>
#include "SDL/SDL.h"
#include "SDL/SDL_net.h"

#include <iostream>

// типа mixin
#define MAX_SOCKET_OPEN 1

using namespace std;

class MServer {

protected:

    MServer(){

	setList = SDLNet_AllocSocketSet(MAX_SOCKET_OPEN);
	num_open_socket = 0;

    };

    virtual ~MServer(){

	SDLNet_FreeSocketSet(setList);
	SDLNet_FreeSocketSet(servList);

    }

void CheckSockets(){

	SDLNet_CheckSockets(servList, 0);
	if (SDLNet_SocketReady(Listen)) AddSocket(Listen);

	int num_ready = SDLNet_CheckSockets(setList, 0);

//cout << "check.." << num_ready << endl;

	if ( num_ready == 0 ) return;

	if ( num_ready == -1) {
//	    cout << "SDLNet_CheckSockets: "<< SDLNet_GetError() << endl;
	    return;
	    }

	for (int i=0; i< num_open_socket; i++){

	    if(SDLNet_SocketReady(sockList[i])){
		if ( HandleSocket( i ) ) { DelSocket(i); i--; }
		num_ready--;
	    }

	}

    };

    virtual bool HandleSocket( int num ) = 0; // true - socket closed

    void AddSocket(TCPsocket serverSocket){

	if (num_open_socket==MAX_SOCKET_OPEN) return;

    cout << "add socket " << num_open_socket << endl;

	TCPsocket new_socket = SDLNet_TCP_Accept(serverSocket);
	SDLNet_TCP_AddSocket(setList, new_socket );
	sockList[num_open_socket] = new_socket;
	num_open_socket++;

    }

    void DelSocket( int num ){

    cout << "del socket " << num << endl;
	SDLNet_TCP_DelSocket( setList, sockList[num] );
	num_open_socket--;

	if(num_open_socket>num)
		memmove(&sockList[num], &sockList[num+1], (num_open_socket-num)*sizeof(TCPsocket));

    }


    void ReCreateSockSet(){

    SDLNet_FreeSocketSet(setList);

    setList = SDLNet_AllocSocketSet(MAX_SOCKET_OPEN);

    if(!setList) {
		printf("SDLNet_AllocSocketSet: %s\n", SDLNet_GetError());
		setList=NULL; return;
	}

	for(int i=0; i<num_open_socket;i++) SDLNet_TCP_AddSocket(setList,sockList[i]);
};


TCPsocket Listen;
SDLNet_SocketSet servList;

TCPsocket sockList[MAX_SOCKET_OPEN];
SDLNet_SocketSet setList;

int num_open_socket;

};

#endif

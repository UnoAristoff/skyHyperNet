#include "CMicrocore.h"
#include <iostream>
using namespace std;

#include "SDL/SDL.h"
#include "SDL/SDL_net.h"
#include "SDL/SDL_thread.h"

#include "CService.h"

static int alive = 0;

int ThreadFunc(void* data){

    CMicrocore* ptrCore = (CMicrocore*) data;

    while(true){
	if (alive==0) return 0;
	if (alive==1)
	    if ( !ptrCore->Process() ) { cout << "proc end" << endl; return 0; }
	SDL_Delay(1*1000);
	}

};

CMicrocore::CMicrocore(){
    status = 1;
    coreThread = NULL;
    cout << "CMicrocore created..." << endl;
}

CMicrocore::~CMicrocore(){

    if (coreThread) {
	alive = 0;
	SDL_WaitThread(coreThread, NULL);
//	SDL_KillThread(coreThread); // ОЕ ОБДП ХВЙЧБФШ ОЙФШ - ПОБ ХЦЕ ЪБЛПОЮЕОБ РП alive=0;
	}

    cout << "CMicrocore THREAD stop..." << endl;
    // shutdown SDL_net
    SDLNet_Quit();

    // shutdown SDL
    SDL_Quit();


    std::vector<IService*>::iterator _it;
    for (_it=ServiceList.begin(); _it!= ServiceList.end();_it++ ){
	if ( !(*_it) ) continue; // ХЦЕ ХДБМЕО
	UID myID = ((CService*)(*_it))->getUID();
	unrService( myID );
    };

    cout << "CMicrocore deleted..." << endl;

}

int CMicrocore::Init(Uint16 port){

    if ( SDL_Init(0) < 0 ) {
	fprintf(stderr, "Couldn't initialize SDL: %s\n",SDL_GetError());

	return 0;
	}

    SDLNet_Init();

    alive = 2; // "pause"

    Listener.ip.port = port;
    return 1;
}

int CMicrocore::Start(bool loop=false){

    Uint16 port = Listener.ip.port;

    SDLNet_ResolveHost(&Listener.ip, NULL, port);
    Listener.socket=SDLNet_TCP_Open(&Listener.ip);

    if(!Listener.socket)
    {
    	printf("fuu: %s\n",SDLNet_GetError());
	status = 0;
	return 0;
    }

    set=SDLNet_AllocSocketSet(1);
    SDLNet_TCP_AddSocket(set,Listener.socket);

    coreThread = SDL_CreateThread(ThreadFunc, this);
    if ( coreThread == NULL ) {
	fprintf(stderr, "Couldn't create thread: %s\n", SDL_GetError());
	status = 0;
	return 0;
	}

    cout << "CMicrocore init on " << port << " port " << endl;
    alive = 1; // "start"

    status = 2; // УПЪДБОП Й ЙОЙГЙБМЙЪЙТПЧБОП

    if (loop) {
        cout << "CMicrocore loop started..." << endl;
	while ( status !=0 ) {  }
        cout << "CMicrocore loop ended..." << endl;
	}

    return 0;

};

int CMicrocore::Release(){
    delete this;
    cout << "CMicrocore release..." << endl;
    return 0;
}

// **************** функция приема сообщения из сокета **************************
// на входе - сокет, буфер, размер буфера
// на выходе - размер принятого сообщения или -1 в случае ошибки
int CMicrocore::GetMsg(TCPsocket socket, char *buffer, int buf_size){
int len=SDLNet_TCP_Recv(socket,buffer,buf_size);
printf("%d GET--> %d", buf_size, len );
		if(!len) return (-1);
return len;
};

// *************** функция отправки сообщения в сокет ****************************
// на входе - сокет, буфер, размер передаваемого сообщения
// на выходе - размер переданного сообщения или -1 в случае ошибки
int CMicrocore::PutMsg(TCPsocket socket, char *buffer, int buf_size){
int len=SDLNet_TCP_Send(socket,buffer,buf_size);
printf("%d <--PUT %d", buf_size, len );
		if(!len) return (-1);
return len;
};

int CMicrocore::Process(){

char message[1024];

TCPsocket new_socket;
int numready;
IPaddress *remoteip;

    numready = SDLNet_CheckSockets(set, 0/*(Uint32)-1*/);

    if(!numready) return status;

    if (SDLNet_SocketReady(Listener.socket)){ // listener что-то уловил
	new_socket = SDLNet_TCP_Accept(Listener.socket); // принимаем соединение от listener'а, получаем номер сокета, с которым будем работать дальше
	numready--;
	if (new_socket) {
	    remoteip = SDLNet_TCP_GetPeerAddress(new_socket);

	    if(remoteip) {
		// print out the clients IP and port number
		Uint32 ipaddr=SDL_SwapBE32(remoteip->host);
		printf("Accepted a connection from %d.%d.%d.%d port %hu\n",
		ipaddr>>24,
		(ipaddr>>16)&0xff,
		(ipaddr>>8)&0xff,
		ipaddr&0xff,
		remoteip->port);
		} //if(remoteip)
		else {  printf("SDLNet_TCP_Accept: %s\n",SDLNet_GetError()); }

	    int len = GetMsg( new_socket, message, 1024); // читаем сокет клиента
	    message[len]='\0';
	    cout << "Length: " << len << endl;
	    cout << "---- d a t a ----" << endl;
	    cout << message << "---- - - - - ----" << endl;
	    SDLNet_TCP_Close( new_socket ); //закрываем сокет клиента
	    status = 0;

	    } // if(new_socket)
    }

    cout << "CMicrocore process..." << endl;
    return status;

}

//IService* CMicrocore::getService( IServType servType ){
//    if (ServiceList.find(servType)!=ServiceList.end() )
//	return ServiceList[servType];
//	return NULL;
//};

void CMicrocore::regService( IService* myService ){

	const char* servName = myService->getName();
//	IServType servType = myService->getType();

	ServiceList.push_back( myService );
	((CService*)myService)->setUID( ServiceList.size() );
	cout << "[" << servName << "] registered " << endl;

};

//void CMicrocore::unrService( IService* myService ){
void CMicrocore::unrService( UID servID ){

	if ( !CheckID(servID) ) return;
	ServiceList[servID-1]->Release();
	ServiceList[servID-1]=NULL;

};

UID CMicrocore::GetUID(const char* ServName){
return 0;
};

bool CMicrocore::CheckID( UID testID ){

	if ( testID>ServiceList.size() ) return false;
	if ( ServiceList[testID-1]==NULL ) return false;

    return true;

};

bool CMicrocore::SendCommand( ahn_command_head& head, void* data, int size ){

	if ( !CheckID(head.from) ) return false;
	if ( !CheckID(head.to) ) return false;
    return true;
};

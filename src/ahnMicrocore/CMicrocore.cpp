#include "CMicrocore.h"
#include <iostream>
using namespace std;

#include "SDL/SDL.h"
#include "SDL/SDL_net.h"
#include "SDL/SDL_thread.h"

IMicrocore* pCore;

static int alive = 0;

int ThreadFunc(void* data){

    CMicrocore* ptrCore = (CMicrocore*) data;

    while(true){
//    cout << "thread.." << alive << endl;
	if (alive==0) { ptrCore->Process(); return 0;}
	if (alive==1)
	    if ( ptrCore->Process() ) { cout << "proc end" << endl; return 0; }
	SDL_Delay(1); //без задержки почему-то не работает под Windows
	}

};

CMicrocore::CMicrocore(){
    pCore = this;
    status = 1;
    coreThread = NULL;
    cout << "CMicrocore created..." << endl;
//    topLeaf = new TLeaf();
//    curLeaf = topLeaf;
}

CMicrocore::~CMicrocore(){

    if (coreThread) {
	alive = 0;
	SDL_WaitThread(coreThread, NULL);
//	SDL_KillThread(coreThread); // ОЕ ОБДП ХВЙЧБФШ ОЙФШ - ПОБ ХЦЕ ЪБЛПОЮЕОБ РП alive=0;, ОЕФ, ОБДП :) ЙВП ЮФЕОЙЕ ЙЪ УПЛЕФПЧ
	}

    cout << "CMicrocore THREAD stop..." << endl;
    // shutdown SDL_net
    SDLNet_Quit();

    // shutdown SDL
    SDL_Quit();

    std::vector< IService* >::iterator _it;
    for (_it=ServiceList.begin(); _it!= ServiceList.end();_it++ ){
	if ( !(*_it) ) continue; // ХЦЕ ХДБМЕО
	UID myID = (*_it)->getUID();
	unrService( myID );
    };

    cout << "CMicrocore deleted..." << endl;

}

int CMicrocore::Init(Uint16 port){

    ext_port = port;

    if ( SDL_Init(0) < 0 ) {
	fprintf(stderr, "Couldn't initialize SDL: %s\n",SDL_GetError());

	return 0;
	}

    SDLNet_Init();

    alive = 2; // "pause"

    Listener.ip.port = port;
    Sender.ip.port = port;

    return 1;
}

int CMicrocore::Start(bool loop=false){

//    accept_s = NULL;
//    Uint16 port = Listener.ip.port;

    SDLNet_ResolveHost(&Listener.ip, NULL, ext_port);
//    Listener.socket=SDLNet_TCP_Open(&Listener.ip);
    Listen = SDLNet_TCP_Open(&Listener.ip);

    if(!Listen)
    {
	printf("fuu: %s\n",SDLNet_GetError());
	status = 0;
	return 0;
    }

    servList=SDLNet_AllocSocketSet(1);
    SDLNet_TCP_AddSocket(servList,Listen);

//    Listen = Listener.socket;

//    SDLNet_ResolveHost(&Sender.ip, "localhost", port);
//    Sender.socket=SDLNet_TCP_Open(&Sender.ip);

//    if(!Sender.socket)
//    {
//	printf("fuu: %s\n",SDLNet_GetError());
//	status = 0;
//	return 0;
//    }


//    set=SDLNet_AllocSocketSet(1);
//    SDLNet_TCP_AddSocket(set,Listener.socket);

//char* test = new char[100];
//PutMsg(Sender.socket, test, 100);
//    int numready =
//SDLNet_CheckSockets(set, (Uint32)-1);
//    (SDLNet_SocketReady(Listener.socket)){ // listener что-то уловил
//TCPsocket new_socket = SDLNet_TCP_Accept(Listener.socket);
//GetMsg(new_socket, test, 100);
//SDLNet_TCP_Close( new_socket );
//delete []test;

//if (len!=100) return 0;

//    Sender.socket = Connect();

    coreThread = SDL_CreateThread(ThreadFunc, this);
    if ( coreThread == NULL ) {
	fprintf(stderr, "Couldn't create thread: %s\n", SDL_GetError());
	status = 0;
	return 0;
	}

    cout << "CMicrocore init on " << ext_port << " port " << endl;
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
int CMicrocore::GetMsg(TCPsocket socket, char *buffer, unsigned int buf_size){

    int len=SDLNet_TCP_Recv(socket,buffer,buf_size);
//    printf("%d GET--> %d\n", buf_size, len );
    if(!len) return (-1);
    return len;

};

// *************** функция отправки сообщения в сокет ****************************
// на входе - сокет, буфер, размер передаваемого сообщения
// на выходе - размер переданного сообщения или -1 в случае ошибки
int CMicrocore::PutMsg(TCPsocket socket, char *buffer, unsigned int buf_size){

//    cout << "Put msg " << buf_size << endl;

    int len=SDLNet_TCP_Send(socket,buffer,buf_size);
//    printf("%d <--PUT %d\n", buf_size, len );
    if(!len) return (-1);
    return len;

};

/*
TCPsocket CMicrocore::Connect(const char* ServerName, int port){

IPaddress _new_ip;

	if(SDLNet_ResolveHost(&_new_ip,(char*)ServerName,port)==-1)
	{
		printf("SDLNet_ResolveHost: %s\n",SDLNet_GetError());
		return NULL;
	}

TCPsocket _new_socket=SDLNet_TCP_Open(&_new_ip);

	if(!_new_socket)
	{
		printf("SDLNet_TCP_Open: %s\n",SDLNet_GetError());
		return NULL;
	}
return _new_socket;

};
*/

int CMicrocore::Process(){

//    cout << "CMicrocore process..." << endl;
//    TLeaf* myLeaf = topLeaf;
//    topLeaf = new TLeaf();
//    curLeaf = topLeaf;

//char message[1024];

//TCPsocket new_socket;
//int numready;
//IPaddress *remoteip;

//    set=SDLNet_AllocSocketSet(1);
//    SDLNet_TCP_AddSocket(set,Listener.socket);

//    int numready = SDLNet_CheckSockets(set, 0/*(Uint32)-1*/);
//    if(!numready) return status;


/*
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
*/

/*
    if (SDLNet_SocketReady(Listener.socket)){ // listener что-то уловил

	    TCPsocket new_socket = SDLNet_TCP_Accept(Listener.socket);
	    SDLNet_SocketSet set_s = SDLNet_AllocSocketSet(1);
	    SDLNet_TCP_AddSocket(set_s, new_socket);

//	    int numready = SDLNet_CheckSockets(set, 0(Uint32)-1);
//    cout << numready << endl;
//    if(!numready) return status;

	    while( SDLNet_CheckSockets(set_s,0) ) {

//	    cout << " .. true .. " << endl;
	    ahn_command_head myComm;
	    ahn_command_head* p_myComm = &myComm;
//	    if (!SDLNet_SocketReady(new_socket)) {  SDLNet_TCP_Close( new_socket ); return 1; } // exit
	    int len = GetMsg( new_socket, (char*)p_myComm, sizeof(ahn_command_head) ); // читаем сокет клиента
	    if (len==-1) {  SDLNet_TCP_Close( new_socket ); return 1; } // exit
//	    message[len]='\0';
	    cout << "Length: " << len << endl;
	    cout << "---- header ----" << endl;
//	    ahn_command_head myComm = (ahn_command_head*) message;
	    cout << "from: " << myComm.from << endl;
	    cout << "to: " << myComm.to << endl;
	    cout << "operation: " << myComm.operation << endl;
	    cout << "size: " << myComm.size << endl;

	    char* mess = new char[myComm.size];
	    len = GetMsg( new_socket, mess, myComm.size ); // читаем сокет клиента
	    ServiceList[myComm.to-1]->CallFunc( myComm, mess );
	    delete []mess;

	    }
	    SDLNet_TCP_Close( new_socket ); return 1;

    }
*/

//    cout << "CMicrocore process..." << endl;

    CheckSockets();
    return 0;

}

bool CMicrocore::HandleSocket( int num ){

cout << "handle : " << num << endl;

    ahn_command_head myComm;
    ahn_command_head* p_myComm = &myComm;

    TCPsocket new_socket = sockList[num];

    int len = GetMsg( new_socket, (char*)p_myComm, sizeof(ahn_command_head) );
    if (len==-1) return true;

//    cout << "---- header ----" << endl;
//    cout << "from " << myComm.from;
//    cout << " to " << myComm.to << endl;
//    cout << "operation " << myComm.operation;
//    cout << " size: " << myComm.size << endl;

    char* mess = new char[myComm.size];
    len = GetMsg( new_socket, mess, myComm.size ); // читаем сокет клиента
    if (len==-1) return true;

    ServiceList[myComm.to-1]->CallFunc( myComm, mess );
    delete []mess;

    return false;

};

void CMicrocore::regService( IService* myService ){

	std::string servName = myService->getName();
	tServType servType = myService->getType();

	ServiceList.push_back( myService );
	myService->setUID( ServiceList.size(), this );

if ( servType < tServLast )  // if service have a manager type
	ServiceList_t[myService->getType()] = myService;

if ( servName !="-" ) // if service have a correct name
	ServiceList_n[servName] = myService;

	cout << "[" << servName << "] registered " << endl;

};

//void CMicrocore::unrService( IService* myService ){
void CMicrocore::unrService( UID servID ){

	if ( !CheckID(servID) ) return;

	IService* myService  = ServiceList[servID-1];
	std::string servName = myService->getName();
	tServType servType   = myService->getType();

if ( servType < tServLast )  // if service have a manager type
	ServiceList_t.erase( ServiceList_t.find(servType) );

if ( servName !="-" )        // if service have a correct name
	ServiceList_n.erase( ServiceList_n.find(servName) );

	myService->Release();
	ServiceList[servID-1]=NULL;

};

UID CMicrocore::GetUID(tServType serv_type){

    if (ServiceList_t.find(serv_type)!=ServiceList_t.end() )
	return ServiceList_t[serv_type]->getUID();

    return 0;

};

UID CMicrocore::GetUID(const char* serv_name){

    if (ServiceList_n.find(serv_name)!=ServiceList_n.end() )
	return ServiceList_n[serv_name]->getUID();

    return 0;

};

bool CMicrocore::CheckID( UID testID ){

cout << "test id: " << testID << endl;

	if ( testID>ServiceList.size() ) return false;
	if ( ServiceList[testID-1]==NULL ) return false;

    return true;

};

bool CMicrocore::SendCommand( ahn_command_head& head, void* data ){

	if ( !CheckID(head.from) ) return false;
	if ( !CheckID(head.to) ) return false;

cout << "CMicrocore::SendCommand" << endl;

//TCPSocket mySock = Connect("127.0.0.1", Listener.ip.port);

    SDLNet_ResolveHost(&Sender.ip, "localhost", ext_port );
    Sender.socket=SDLNet_TCP_Open(&Sender.ip);

    if(!Sender.socket)
    {
	printf("fuu: %s\n",SDLNet_GetError());
	status = 0;
	return 0;
    }

cout <<  PutMsg(Sender.socket, (char*)&head, sizeof(ahn_command_head) ) << endl;

cout <<  PutMsg(Sender.socket, (char*)data, head.size ) << endl;

	SDLNet_TCP_Close( Sender.socket );

//	curLeaf = curLeaf->AddLeaf( head, (const char*) data );

//TLeaf* myLeaf = new TLeaf();
//	if ( PoolList.find(head.to)==PoolList.end() ){
//	    PoolList[head.to] = new TLeaf();
//	};


//	PoolList[head.to]->AddLeaf( head, (const char*) data );

//    return ServiceList[head.to-1]->CallFunc( head, data );

    return true;

};

#ifndef _basenet_h
#define _basenet_h

#include "ahn_types.h"

typedef int sock_id;

extern sock_id net_init(Uint16 port, char *host=NULL); // init network (local or remote!)
extern void net_off();

extern sock_id serv_get(char* service_name);  // get service_id by service_name

extern int net_send(sock_id Id, char* buff, int size);
extern int net_recv(sock_id Id, char* buff, int size);

#endif

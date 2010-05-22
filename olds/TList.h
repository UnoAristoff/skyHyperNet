#ifndef _T_LIST_H
#define _T_LIST_H

#include "ahn_command.h"

class TLeaf {

public: 

    TLeaf( ){
	d_size = 0;
	data = NULL;
	prev = NULL;
	post = NULL;
	}

    ~TLeaf(){
	if(data) delete []data;
	if(prev) { prev->post = NULL; }
	}

    TLeaf* AddLeaf(ahn_command_head& comm, const char* data){
	TLeaf* myLeaf = new TLeaf();
	myLeaf->data = new char[ comm.size + sizeof(ahn_command_head) ];
//	ahn_command_head* p_comm = &comm;
	memcpy( myLeaf->data, &comm, sizeof(ahn_command_head) );
	memcpy( myLeaf->data + sizeof(ahn_command_head), data, comm.size );
	myLeaf->d_size = comm.size + sizeof(ahn_command_head);
	return myLeaf;
    }


protected:

    char* data;
    int d_size;
    TLeaf* prev;
    TLeaf* post;

};

#endif

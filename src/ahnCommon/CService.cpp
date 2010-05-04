#include "CService.h"

CService::CService(){
    myID = 0;
};

CService::~CService(){

};

void CService::RegFunc( void* func_ptr ){
    func_list.push_back( func_ptr );
};

bool CService::CallFunc( ahn_command_head& head, void* data, int size){

    if ( myID != head.to ) return false; 
    if ( func_list.size() < head.operation ) return false;


};

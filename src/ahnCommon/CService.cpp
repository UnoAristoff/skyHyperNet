#include "CService.h"


//typedef bool (CService::FUNC_PTR*)( ahn_command_head& head, void* data, int size );

CService::CService(){

    myID = 0;
    myCore = NULL;

    void* ptrFunc = &CService::TestFunc;

    RegFunc( ptrFunc );

};

CService::~CService(){

};

bool CService::TestFunc( ahn_command_head& head, void* data, int size ){

};

void CService::RegFunc( void* func_ptr ){
    func_list.push_back( func_ptr );
};

bool CService::CallFunc( ahn_command_head& head, void* data, int size){

    if ( myID != head.to ) return false;
    if ( func_list.size() < head.operation ) return false;

    return true;

};

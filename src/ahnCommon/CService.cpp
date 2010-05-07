#include "CService.h"
#include <iostream>
using namespace std;

CService::CService(){
    myID = 0;
    num_func = 0;

    CALLFUNC myF = &CService::TestFunc1;
    RegFunc( myF );

    myF = &CService::TestFunc2;
    RegFunc( myF );

    myF = &CService::TestFunc3;
    RegFunc( myF );

};

CService::~CService(){

};

void CService::RegFunc( CALLFUNC &func_ptr ){
//    func_list.push_back( func_ptr );
    func_list[ num_func ] = func_ptr;
    num_func++;
};

bool CService::TestFunc1( ahn_command_head& head, void* data, int size){
cout << "TestFunc1" << endl;
return true;
};

bool CService::TestFunc2( ahn_command_head& head, void* data, int size){
cout << "TestFunc2" << endl;
return true;
};

bool CService::TestFunc3( ahn_command_head& head, void* data, int size){
cout << "TestFunc3" << endl;
return true;
};

bool CService::CallFunc( ahn_command_head& head, void* data, int size){

    if ( myID != head.to ) return false;
    if ( num_func < head.operation ) return false;

    CALLFUNC myF = func_list[head.operation];
    (this->*myF)( head, data, size );

    return true;
};

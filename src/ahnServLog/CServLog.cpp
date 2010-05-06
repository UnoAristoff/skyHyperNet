#include "CServLog.h"
#include <iostream>
using namespace std;

CServLog::CServLog(){

    cout << "ServLog created.. " << endl;

    //CALLFUNC myF = &CServLog::ServLogFunc;
    //RegFunc( myF );

};

CServLog::~CServLog(){

    cout << "ServLog deleted.." << endl;

};

bool CServLog::ServLogFunc( ahn_command_head& head, void* data, int size ){
    return true;
};

//bool CServLog::CallFunc( void* ptr, long size ){
//
//
//};

#include "CServLog.h"
#include <iostream>
using namespace std;

CServLog::CServLog(){

    cout << "ServLog created.. " << endl;

    CALLFUNC myF = &CServLog::ServLogFunc1;
    RegFunc( myF );

    myF = &CServLog::ServLogFunc2;
    RegFunc( myF );

    myF = &CServLog::ServLogFunc3;
    RegFunc( myF );

    myF = &CServLog::ServLogFunc4;
    RegFunc( myF );

};

CServLog::~CServLog(){

    cout << "ServLog deleted.." << endl;

};

bool CServLog::ServLogFunc1( ahn_command_head& head, void* data, int size ){
    cout << "ServLog Func1.." << endl;
    return true;
};

bool CServLog::ServLogFunc2( ahn_command_head& head, void* data, int size ){
    cout << "ServLog Func2.." << endl;
    return true;
};

bool CServLog::ServLogFunc3( ahn_command_head& head, void* data, int size ){
    cout << "ServLog Func3.." << endl;
    return true;
};

bool CServLog::ServLogFunc4( ahn_command_head& head, void* data, int size ){
    cout << "ServLog Func4.." << endl;
    return true;
};

//bool CServLog::CallFunc( void* ptr, long size ){
//
//
//};

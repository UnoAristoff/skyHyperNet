#include "CServLog.h"
#include <iostream>

#include "ahn_servlog.h"

#include "ahn_function.h"

using namespace std;
IMicrocore* pCore;
char buffer[ 80 ];

const char *get_date(){
time_t time_of_day=time(NULL);
strftime( buffer, 80, "%Y%m%d%H%M%S", localtime( &time_of_day ) );
return buffer;
};

const char *get_time(){
time_t time_of_day=time(NULL);
strftime( buffer, 80, "%H:%M:%S", localtime( &time_of_day ) );
return buffer;
};

CServLog::CServLog(){

    cout << "ServLog created.. " << endl;

    INI_FUNC( FServLogEndF );
    REG_FUNC( CServLog, FLogMsg, LogMsg );
    REG_FUNC( CServLog, FErrMsg, ErrMsg );

    LogName = std::string("log/")+std::string(get_date())+".log";

    log_file = fopen( LogName.c_str(),"a+b");

    if (!log_file) { cout<< "CServLog:: can't init LogFile!" << endl; }

};

CServLog::~CServLog(){

    fclose(log_file);
    cout << "ServLog deleted.." << endl;

};

bool CServLog::LogMsg( ahn_command_head& head, void* data ){

    if ( !log_file ) return false;

//    cout << (char*)data << endl;

    fputs( get_time(), log_file );
    fputs(": ", log_file);

    fputs( (const char*) data, log_file );
    fputs("\n", log_file );

    fflush( log_file );

    return true;

};

bool CServLog::ErrMsg( ahn_command_head& head, void* data ){

    if ( !log_file ) return false;
    fputs( get_time(), log_file );
    fputs(": ", log_file);

    fputs( (const char*) data, log_file );
    fputs("\n", log_file );

    fflush( log_file );

    return true;
};

/*
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
*/


//bool CServLog::CallFunc( void* ptr, long size ){
//
//
//};

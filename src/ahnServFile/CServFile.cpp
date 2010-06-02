#include "CServFile.h"
#include <iostream>

//#include "ahn_servlog.h"

#include "ahn_function.h"

using namespace std;
IMicrocore* pCore;

CServFile::CServFile(){

    cout << "ServFile created.. " << endl;

//    INI_FUNC( FServLogEndF );
//    REG_FUNC( CServLog, FLogMsg, LogMsg );
//    REG_FUNC( CServLog, FErrMsg, ErrMsg );

};

CServFile::~CServFile(){

    cout << "ServFile deleted.." << endl;

};

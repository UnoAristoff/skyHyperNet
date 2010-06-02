#include "CServGra.h"
#include <iostream>

#include "ahn_servgraf.h"

#include "ahn_function.h"

using namespace std;
IMicrocore* pCore;

CServGra::CServGra(){

    cout << "ServGra created.. " << endl;

    INI_FUNC( FServGraEndF );
    REG_FUNC( CServGra, FAddWindow, AddWindow );
    REG_FUNC( CServGra, FAddWindow, AddWindow );

};

CServGra::~CServGra(){

    cout << "ServGra deleted.." << endl;

};

bool  CServGra::AddWindow( ahn_command_head& head, void* data ){


    return true;
};

bool  CServGra::DelWindow( ahn_command_head& head, void* data ){


    return true;
};

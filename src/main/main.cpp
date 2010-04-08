#include <stdio.h>
#include <iostream.h>

#include "CMicrocore.h"

IMicrocore* myCore;

extern IMicrocore* GetCore();

int main(int argc, char *argv[])
{

    printf("Hello world!\n");

    myCore = GetCore();
    myCore = GetCore();    myCore = GetCore();    myCore = GetCore();    myCore = GetCore();    myCore = GetCore();    myCore = GetCore();    myCore = GetCore();    myCore = GetCore();    myCore = GetCore();    myCore = GetCore();    myCore = GetCore();    myCore = GetCore();    myCore = GetCore();    myCore = GetCore();    myCore = GetCore();    myCore = GetCore();    myCore = GetCore();    myCore = GetCore();    myCore = GetCore();    myCore = GetCore();    myCore = GetCore();    
    myCore->Start(false);

    cout << "press <Enter> to quit...";
    getchar();
    cout << "[OK]" << endl;
//    myCore->Start(true); // loop

    myCore->Release();
    return 0;

}

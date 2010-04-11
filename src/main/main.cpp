#include <stdio.h>
#include <iostream.h>

//#include "IMicrocore.h"

#include "core_loader.h"

IMicrocore* myCore;

extern IMicrocore* GetCore();

int main(int argc, char *argv[])
{

    printf("Hello world!\n");

    myCore = GetCore();

    if (!myCore) {

	cout << "can't init core. exit..." <<endl;
	return 1;

    }

cout << "yesss" << endl;


//    myCore = GetCore();    myCore = GetCore();    myCore = GetCore();    myCore = GetCore();    myCore = GetCore();    myCore = GetCore();    myCore = GetCore();    myCore = GetCore();    myCore = GetCore();    myCore = GetCore();    myCore = GetCore();    myCore = GetCore();    myCore = GetCore();    myCore = GetCore();    myCore = GetCore();    myCore = GetCore();    myCore = GetCore();    myCore = GetCore();    myCore = GetCore();    myCore = GetCore();    myCore = GetCore();    
    myCore->Start(false);

    cout << "press <Enter> to quit...";
    getchar();
    cout << "[OK]" << endl;
//    myCore->Start(true); // loop

    myCore->Release();
    return 0;

}

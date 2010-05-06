#include <stdio.h>
#include <iostream>
using namespace std;

#include "core_loader.h"

IMicrocore* myCore;

extern IMicrocore* GetCore();

int main(int argc, char *argv[])
{

//    printf("Hello world!\n");

    myCore = GetCore();

    if (!myCore) {

	cout << "can't init core. exit..." <<endl;
	return 1;

    }

// cout << "yesss" << endl;
// myCore = GetCore();    myCore = GetCore();    myCore = GetCore();    myCore = GetCore();    myCore = GetCore();    myCore = GetCore();    myCore = GetCore();    myCore = GetCore();    myCore = GetCore();    myCore = GetCore();    myCore = GetCore();    myCore = GetCore();    myCore = GetCore();    myCore = GetCore();    myCore = GetCore();    myCore = GetCore();    myCore = GetCore();    myCore = GetCore();    myCore = GetCore();    myCore = GetCore();    myCore = GetCore();

    myCore->Start(false);

    UID myLog = myCore->GetUID("ServLog");

    cout << "myLog ID : " << myLog << endl;

    ahn_command_head my_command;
    my_command.from = myLog;
    my_command.to = myLog;
    my_command.operation = 0;
    myCore->SendCommand( my_command, NULL, 0);

    my_command.operation = 1;
    myCore->SendCommand( my_command, NULL, 0);

    my_command.operation = 2;
    myCore->SendCommand( my_command, NULL, 0);

    cout << "press <Enter> to quit...";
    getchar();
    cout << "[OK]" << endl;


//    myCore->Start(true); // loop
    FreeCore();
    return 0;

}

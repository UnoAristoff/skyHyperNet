#ifndef _T_SERVICE_H
#define _T_SERVICE_H

#include "IMicrocore.h"
#include "IService.h"

template <class T> class TService: public IService {
public:
typedef bool (T::*CALLFUNC)( ahn_command_head& head, void* data, int size);

    TService(){
        myID = 0;
        num_func = 0;
        }

    virtual ~TService(){

        }

bool CallFunc( ahn_command_head& head, void* data, int size){

    if ( myID != head.to ) return false;
    if ( num_func < head.operation ) return false;

    CALLFUNC myF = func_list[head.operation];

    T* myPtr = dynamic_cast<T*>(this);
    (myPtr->*myF)( head, data, size );

    return true;
};

protected:

    void RegFunc( CALLFUNC &func_ptr ){
        func_list[ num_func ] = func_ptr;
        num_func++;
//        cout << "reg func: " << num_func;
    };

    IMicrocore* myCore;
    UID myID;

    NUC num_func;
    CALLFUNC func_list[10];

};

#endif

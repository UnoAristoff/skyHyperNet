#include "plug_loader.h"
#include "os_loadmodule.h"

#include <stdio.h>

#include <stdio.h>
#include <iostream>

//#include "CMicrocore.h"
#include <string>
#include <dirent.h>
#include <sys/stat.h>

#include "os_loadmodule.h"
#include "os_deps.h"

using namespace std;

typedef void* (*GETSERVICE)( void );

void load_mod( const char* mod_name ){

    void* hLibrary = os_LoadObject( mod_name );
    if (!hLibrary) {fprintf(stdout,"[ERROR!]\n"); return; }
//    fprintf(stdout,"[OK]\n");

    /// Определяем адрес функции GetPlugin
    GETSERVICE FPlugLoad = (GETSERVICE)os_LoadFunction( hLibrary, "GetService" );

    /// Если определить не удаётся - выгружаем модуль и возвращаем NULL
    if (!FPlugLoad) {
//    fprintf(stderr,"%s: I can't find GetPlugin function in %s module :(\n",__FILE__,ModuleName.c_str());
    os_UnloadObject(hLibrary);
    return;
    }

    void* myServ = FPlugLoad();

    // если в myGenerator не экземпляр класса-генератора а NULL то выгружаем модуль и выходим
    if (!myServ) {
	os_UnloadObject(hLibrary);
	return;
	}

//myGenerator->Initialize(Engine); //инициализируем генератор
//    _myCore->regService( myServ );
	get_mod( myServ );

}

void scan_mod( const char* dir_name, bool Recursive ){
    os_finddata_t fdata;
    os_dir_t hFile;

    std::string DirName = dir_name;

// если путь не заканчивается слэшем ставим его
	if (DirName[DirName.length()-1]!='/') DirName=DirName+'/';

// начали
	hFile = os_findfirst( dir_name , &fdata);
	if (!hFile) return;

	do
	{

	if (fdata.name=="..") continue;
	if (fdata.name==".") continue;

	if (fdata.subdir & Recursive) {
//     printf("scan dir: %s\n", fdata.name.c_str());
     scan_mod( std::string(fdata.dir_name+fdata.name).c_str(), true );
     }
    else {
//	printf("find file: %s\n", fdata.name.c_str());
	load_mod( std::string(DirName+fdata.name).c_str() );
//     std::string FileExt=GetFileExt(DirName+fdata.name);
//     if (FileExt==ASN_MODULE_EXTENSION_NAME) LoadASNModule(DirName+fdata.name);
         }

	} while (os_findnext( hFile, &fdata )!= NULL);
	os_findclose(hFile);

};


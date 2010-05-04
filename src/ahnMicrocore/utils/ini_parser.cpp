//#include <stdio.h>
//#include <iostream.h>
//#include "CMicrocore.h"
//#include <string>
//#include <dirent.h>
//#include <sys/stat.h>
//#include "os_deps.h"
//#include "os_loadmodule.h"

#include "ini_parser.h"

#include <string>
#include <map>

#include <stdio.h>
#include <iostream.h>
#include <fstream>

#include "asn_utils.h"

std::map< std::string, std::string > ParseList;

void parse_ini(const char* file_name )
{

    std::string GroupName="Root_";

    char buffer[512];
    char *Param;
    char *Value;
    std::string ParamStr;
    std::string ValueStr;

    std::ifstream infile( file_name );

    if (! infile.is_open() )
    {
        //      fprintf(stderr,"Can't load %s file as ini-file!\n",FileName.c_str());
        return;
    };

    fprintf(stdout,"Using ini-file: %s\n", file_name);

    while(!infile.eof())
    {
        infile.getline(buffer, sizeof(buffer)); //������ ������ �� �����
        if ( buffer[0]==';' )
            continue; //���������� �������, ��� �����������!
        Param = strtok(buffer, "="); // ���� ������ ����� �� ����� =
        if(Param == NULL)
            continue; // ���� ������ ��� - ���������� ����
        ParamStr=Param; //� string ��� !
        if (ParamStr[0]=='[')
        {
            GroupName=Trim(ParamStr);
        } //  ��� ������ [������] � ini-�����
        else
        {
            Value = strtok(NULL, "="); // ������ ��� ��� ������, ������� ����� = ������ �� �����
            if ( Value!=NULL )
            { // ���� ����������
                ValueStr=Value; // � string ���
                //    printf("{%s}={%s}\n",(GroupName+Trim(ParamStr)).c_str(),Trim(ValueStr).c_str());
		//    Engine->SetEnvParam(ASN_Str(GroupName+Trim(ParamStr)).c_str(),Trim(ValueStr).c_str() );
                ParseList[GroupName+Trim(ParamStr)]=Trim(ValueStr);
            }
            else
            {
                //       printf("{%s}={%s}\n",(GroupName+Trim(ParamStr)).c_str(),);
                //            printf("Param: {%s}\n",(GroupName+Trim(ParamStr)).c_str());
                //            Engine->SetEnvParam(GroupName+Trim(ParamStr),"1"); //������ �������� �� ���������
            };
        };
        // printf("BUFFER: %s\n",buffer);
    };

};

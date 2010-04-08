#include "asn_utils.h"

#include <string>

std::string Trim(std::string& s,const std::string& drop)
{
    //printf("TRY TRIM {%s}\n",s.c_str());
    std::string t=s;
    size_t i=t.find(0xd);
    if (i>0)
        t=t.substr(0,i);
    std::string::size_type posLast=t.find_last_not_of(drop)+1;
    std::string::size_type posFirst=t.find_first_not_of(drop);
    return std::string(t, posFirst, posLast-posFirst);
};

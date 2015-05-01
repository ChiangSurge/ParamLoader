#include "TypeUtil.h"
#include "StringUtil.h"
#include <cassert>
using namespace std;
const string TypeUtil::
Boolean2String(bool flag)
{
    string str;
    if (flag)
    {
        str.assign("TRUE");
    }
    else
    {
        str.assign("FALSE");
    }
    return str;
}

bool TypeUtil::
IsNumeric(const std::string& str)
{
    // if the string only contains
    // 0~9
    // .e-
    // it is considered as numeric
    for (int i=0; i<int(str.length()); i++)
    {
        if ((str[i] >= '0' && str[i] <= '9')
            || str[i] == '-' || str[i] == '.'
            || str[i] == 'e' || str[i] == '+')
        {
            continue;
        }
        return false;
    }
    return true;
}

double TypeUtil::
String2Number(const std::string& str)
{
	std::string trimStr = StringUtil::Trim(str, " ");
	if (!IsNumeric(trimStr)) {
		printf("%s is not numberic!\n", str.c_str());
        fflush(stdout);
        return 0.0;
	}
    istringstream iss(trimStr);
    double val;
    iss >> val;
    return val;
}

int TypeUtil::
String2Integer(const std::string& str)
{
	std::string trimStr = StringUtil::Trim(str, " ");
	if(!IsNumeric(trimStr)) {
		printf("TypeUtil::String2Integer %s is not numeric!\n", str.c_str());
		assert(false);
	}
	istringstream iss(trimStr);
	int val;
	iss >> val;
	return val;
}


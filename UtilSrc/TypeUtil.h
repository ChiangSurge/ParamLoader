#ifndef Params_TYPE_UTIL_H
#define Params_TYPE_UTIL_H
namespace TypeUtil
{
    const std::string Boolean2String(bool flag);
    double String2Number(const std::string& str);
	int String2Integer(const std::string& str);
    bool IsNumeric(const std::string& st);
};
#endif
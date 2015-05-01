#ifndef PARAMS_STRING_UTIL_H_
#define PARAMS_STRING_UTIL_H_
#include <vector>
#include <string>
#include <sstream>
#include <fstream>

namespace StringUtil
{
	void ParseIntegers(const char* args, std::vector<int>& integers,char delimit = ',');
	std::vector<std::string> Split(const std::string& str, char sep);
	std::vector<std::string> Split(const std::string& str, const std::string& seps);
    const std::string Join(const std::vector<std::string>& array, char sep);
	std::string Trim(const std::string& str, const char* s);
	bool Contains(const std::string& str1, const std::string& str2);
	const std::string Upper(const std::string& str);
	const std::string Lower(const std::string& str);
	std::vector<std::string> Name2Tags(const std::string& str);
	const std::string Number2String(int num);
	const std::string Number2String(double num);
    const std::string Array2String(const std::vector<int>& array);
	// Sorting
	void BubbleSort(std::vector<std::string>& strings);
	void BubbleSort(const std::vector<std::string>& strings,
					std::vector<int>& ranked_index);
    // VKString
    const std::string ParseVKString(FILE* fin);
    // Replace
    const std::string Replace(const std::string& inputStr,
                              char orgChar, char newChar);
};
#endif
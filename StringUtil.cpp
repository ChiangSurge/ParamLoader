#include <algorithm>
#include <string>
#include <sstream>
#include <iterator>
#include "StringUtil.h"
#include "TypeUtil.h"

using namespace std;
void StringUtil::
ParseIntegers(const char* args, std::vector<int>& integers, char delimit)
{
    string str(args);
	str = Trim(str, "\n");
    istringstream iss(str);
    string word;
    while (getline(iss, word, delimit))
    {
        int x = TypeUtil::String2Number(word);
        integers.push_back(x);
    }
}

vector<string> StringUtil::
Split(const std::string& filename, char sep)
{

	vector<int> critical_indices;
	string::size_type idx = -1;
	critical_indices.push_back(-1);
	string::size_type new_idx = filename.find(sep);
	while (new_idx != string::npos)
	{
		idx = new_idx + idx + 1;
		critical_indices.push_back(idx);
		new_idx = filename.substr(idx+1).find(sep);
	}
	vector<string> segments;
	for (int i=0; i<int(critical_indices.size()-1); i++)
	{
		int start_idx = critical_indices[i]+1;
		int len = critical_indices[i+1] - start_idx;
		if (len <= 0) continue;
		segments.push_back(filename.substr(start_idx, len));
	}
	int start_idx = critical_indices[critical_indices.size()-1] + 1;
	if (filename.substr(start_idx).length() > 0) segments.push_back(filename.substr(start_idx));
	return segments;
}

vector<string> StringUtil::
Split(const std::string& str, const string& seps)
{
	string str2 = str;
	// replace seps[i] by ' '
	for (int i=0; i<int(seps.length()); i++) {
		replace(str2.begin(), str2.end(), seps[i], ' ');
	}
	return Split(str2, ' ');
}

const string StringUtil::
Join(const vector<string>& array, char _sep)
{
    if ((int)array.size() == 0) return "";
    string str = array[0];
    string sep(1, _sep);
    for (int i=1; i<(int)array.size(); i++) {
        str = str + sep + array[i];
    }
    return str;
}

string StringUtil::
Trim(const string& str, const char* s)
{
	size_t begin = str.find_first_not_of(s);
	size_t end = str.find_last_not_of(s);
	if (begin == string::npos || end == string::npos) return "";
	else return str.substr(begin, end - begin + 1);
}

bool StringUtil::
Contains(const std::string& str1, const std::string& str2)
{
	return (Lower(str1).find(Lower(str2)) != string::npos);
}

const string StringUtil::
Upper(const string& str)
{
	string upper;
	transform(str.begin(), str.end(), back_inserter(upper), ::toupper);
	return upper;
}

const string StringUtil::
Lower(const string& str)
{
	string lower;
	transform(str.begin(), str.end(), back_inserter(lower), ::tolower);
	return lower;
}

vector<string> StringUtil::
Name2Tags(const string& str)
{
	// find all non-alphabetical ascii symbols
	string skipped_letters("");
	for (int i=1; i<128; i++) {
		if (i>='A' && i<='Z') continue;
		if (i>='a' && i<='z') continue;
		skipped_letters.append(1, char(i));
	}
	return Split(str, skipped_letters);
}

const string StringUtil::
Number2String(int num)
{
	ostringstream oss;
	oss << num;
	return oss.str();
}

const string StringUtil::
Number2String(double num)
{
	ostringstream oss;
	oss << num;
	return oss.str();
}


const string StringUtil::
Array2String(const vector<int>& array)
{
    vector<string> strArray;
    for (int i=0; i<(int)array.size(); i++) {
        strArray.push_back(Number2String(array[i]));
    }
    return Join(strArray, '|');
}


void StringUtil::
BubbleSort(vector<string>& values)
{
	vector<int> ranking;
	BubbleSort(values, ranking);
	vector<string> sorted_array;
	for (int i=0; i<int(ranking.size()); i++) {
		sorted_array.push_back(values[ranking[i]]);
	}
	values = sorted_array;
}

// sort to ascending order
void StringUtil::
BubbleSort(const vector<string>& values,
		   vector<int>& ranked_index)
{
    int n = values.size();
    ranked_index.clear();
    for (int i=0; i<n; i++)
    {
        ranked_index.push_back(i);
    }
    
    for (int i=0; i<n-1; i++)
    {
        for (int j=0; j<n-1-i; j++)
        {
            if (values[ranked_index[j]] > values[ranked_index[j+1]])
            {
                // swap j and j+1
                int temp = ranked_index[j+1];
                ranked_index[j+1] = ranked_index[j];
                ranked_index[j] = temp;
            }
        }
    }
}

// VKString
const string StringUtil::
ParseVKString(FILE* fin)
{
    int length = -1;
    fread(&length, sizeof(int), 1, fin);
    char* str = new char[length];
    fread(str, sizeof(char), length, fin);
    string newString(str);
    delete[] str;
    return newString;
}

// Replace letters
const string StringUtil::
Replace(const string& inputStr, char orgChar, char newChar)
{
    string outputStr = inputStr;
    for (int i=0; i<(int)outputStr.length(); i++) {
        if (outputStr[i] == orgChar) {
            outputStr.replace(i, 1, 1, newChar);
        }
    }
    return outputStr;
}

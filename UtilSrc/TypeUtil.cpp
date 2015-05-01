#include "Utils.h"
using namespace std;
typedef std::vector<RNScalar> ScalarArray;
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
	if (!IsNumeric(str)) {
		printf("%s is not numberic!\n", str.c_str());
        fflush(stdout);
        return 0.0;
	}
    assert(IsNumeric(str));
    istringstream iss(str);
    double val;
    iss >> val;
    return val;
}

int TypeUtil::
String2Integer(const std::string& str)
{
	if(!IsNumeric(str)) {
		printf("TypeUtil::String2Integer %s is not numeric!\n", str.c_str());
		assert(false);
	}
	istringstream iss(str);
	int val;
	iss >> val;
	return val;
}

const ScalarArray TypeUtil::
String2Array(const std::string& str)
{
    ScalarArray ans;
    // split by '|'
    vector<string> segs = StringUtil::Split(str, '|');
    for (int i=0; i<(int)segs.size(); i++) {
        ans.push_back(String2Number(segs[i]));
    }
    return ans;
}

const R3Affine TypeUtil::
String2Affine(const std::string& str)
{
    ScalarArray ans = String2Array(str);
    if ((int)ans.size() != 16) {
        fprintf(stderr, "TypeUtil::String2Affine dim = %d\n", (int)ans.size());
        exit(-1);
    }
    R4Matrix matrix(ans[0], ans[1], ans[2], ans[3],
                    ans[4], ans[5], ans[6], ans[7],
                    ans[8], ans[9], ans[10], ans[11],
                    ans[12], ans[13], ans[14], ans[15]);
    return R3Affine(matrix);
}


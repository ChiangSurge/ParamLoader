#include <fstream>
#include <sstream>
#include "UtilsConfigParser.h"
#include "StringUtil.h"
#include "TypeUtil.h"

using namespace std;
//ConfigParser MyConfigParser;

ConfigParser::
ConfigParser(void)
:isLoaded(false)
{}

void ConfigParser::
Import(const char* filename, bool create_new)
{
    ifstream fin(filename);
	if (!fin)
	{
		fprintf(stderr, "Unable to open setting file %s\n", filename);
		return;
	}
    string buffer;
	string current_section = "";
	int line_counter = 0;
	bool fail_flag = false;
    while (!fin.eof())
    {
        getline(fin, buffer);
		line_counter ++;
		// comments
        if (buffer.empty() || buffer[0] == '#' ) continue;
		// section name
		else if (buffer[0] == '[') {
			size_t last_pos = buffer.find_last_of("]");
			if (last_pos == string::npos) {
				fprintf(stderr, "ConfigParser::Import syntax error found at"
						" line %d\n", line_counter);
				fail_flag = true;
				break;
			}
			else {
				current_section = buffer.substr(1, last_pos-1);
			}
		}
		// option name
		else {
			// empty line
			if (buffer.length() == 0) continue;
			if (current_section.length() == 0) {
				fprintf(stderr, "ConfigParser::Import syntax error found at"
						" line %d\n", line_counter);
				fail_flag = true;
				break;
			}
			size_t equal_pos = buffer.find_last_of("=");
			if (equal_pos == string::npos) {
				fprintf(stderr, "ConfigParser::Import syntax error found at"
						" line %d\n", line_counter);
				fail_flag = true;
				break;
			}
			string opt_part = buffer.substr(0, equal_pos);
			string val_part = buffer.substr(equal_pos+1);
			Set(current_section, StringUtil::Trim(opt_part, " "),
				StringUtil::Trim(val_part, " "),
				create_new);
		}
    }
    fin.close();
	if (!fail_flag) {
		isLoaded = true;
	}
	else
	{
		fprintf(stderr, "ConfigParser::Import fail to import %s\n",
				filename);
	}
    ImportOptValues();
}

void ConfigParser::
ImportOptValues(void)
{

}

bool ConfigParser::
HasSection(const string& sec) const
{
	return (m_sec_opts_vals.find(sec) != m_sec_opts_vals.end());
}

bool ConfigParser::
HasOption(const string& sec, const string& opt) const
{
	if (!HasSection(sec)) return false;
	map<string, map<string, string> >::const_iterator sec_map =
		m_sec_opts_vals.find(sec);
	return ((*sec_map).second.find(opt) != (*sec_map).second.end());
}

bool ConfigParser::
IsLoaded(void) const
{
	return isLoaded;
}

void ConfigParser::
Set(const std::string& sec, const std::string& opt,
	const std::string& val, bool create_new)
{
	if( (!create_new && !HasOption(sec, opt)) || val.empty()){
		fprintf(stderr, "ConfigParser::Set Option %s::%s doesn't exist!\n", sec.c_str(), opt.c_str());
		return;
	}
	m_sec_opts_vals[sec][opt] = val;
}

const string ConfigParser::
Get(const std::string& sec, const std::string& opt) const
{
	if (!HasOption(sec, opt)) {
		fprintf(stderr, "ConfigParser::Get Unable to find %s::%s\n",
				sec.c_str(), opt.c_str());
	}
	map<string, map<string, string> >::const_iterator sec_map = m_sec_opts_vals.find(sec);
	map<string, string>::const_iterator opt_map = (*sec_map).second.find(opt);
	return (*opt_map).second;
}

double ConfigParser::
GetScalar(const std::string& sec, const std::string& opt) const
{
	return TypeUtil::String2Number(Get(sec, opt));
}

int ConfigParser::
GetInt(const std::string& sec, const std::string& opt) const
{
	return int(GetScalar(sec, opt));
}

const char* ConfigParser::
GetCharArray(const std::string& sec, const std::string& opt) const
{
	return Get(sec, opt).c_str();
}

const std::vector<double> ConfigParser::
GetScalarArray(const std::string& sec,
			   const std::string& opt) const
{
	std::string str = Get(sec, opt);
	std::vector<std::string> segments = StringUtil::Split(str, ',');
	std::vector<double> scalar_array;
	for (int i=0; i<int(segments.size()); i++) {
		segments[i] = StringUtil::Trim(segments[i], "");
		scalar_array.push_back(TypeUtil::String2Number(segments[i]));
	}
	return scalar_array;
}

bool ConfigParser::
IsEnabled(const std::string& sec, const std::string& opt) const
{
	return Get(sec, opt) == "on";
}

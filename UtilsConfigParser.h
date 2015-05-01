#ifndef ___CONFIG_PARSER_H
#define ___CONFIG_PARSER_H
#include <string>
#include <map>
#include <vector>
#include "StringUtil.h"
#include "TypeUtil.h"
// inherite this class to define the parameters.
class ConfigParser 
{
public:
    enum {SUM, MIN} SpatialOperation;
public:
	ConfigParser(void);
	virtual void Import(const char* filename, bool create_new = false);
    virtual void ImportOptValues(void) = 0;
    // Check
    bool HasSection(const std::string& sec) const;
	bool HasOption(const std::string& sec,
						const std::string& opt) const;
	bool IsLoaded(void) const;
    // Set
    void Set(const std::string& sec, const std::string& opt,
			 const std::string& val, bool create_new = true);
    // Get
	double GetScalar(const std::string& sec, const std::string& opt) const;
	int GetInt(const std::string& sec, const std::string& opt) const;
	const std::string Get(const std::string& sec,
						  const std::string& opt) const;
	const char* GetCharArray(const std::string& sec,
							 const std::string& opt) const;
	const std::vector<double> GetScalarArray(const std::string& sec,
										 const std::string& opt) const;
    bool IsEnabled(const std::string& sec,
						const std::string& opt) const;
public:
    // define the parameters.
	
protected:
	// Data
    std::map<std::string, std::map<std::string,std::string> > m_sec_opts_vals;
	bool isLoaded;
};

//extern ConfigParser MyConfigParser;
#endif

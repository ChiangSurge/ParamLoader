#ifndef COMMON_HPP
#define COMMON_HPP
#include <iostream>
#include <string>
#include <algorithm>
#include <iostream>
#include <vector>
#include <iomanip>
#include <time.h>
#include <QFileInfo>
#include <QDir>

	/////////////////////////////////////////////////////////////////////// 
	double beta_func(float alpha, int size);
	double dirichlet_prob(float alpha, std::vector<float> probs);

	extern double g_eps_min;

	class HTimer{
	public:
		void startTimer();
		double stopTimer();
	private:
		clock_t m_start;
		clock_t m_finish;
	};

	//////////////////////////////////////////////////////////////////////////////
	class HLogger{
	public:
		enum LoggerType{ 
			NOTEST, DEBUG, INFO, NOTICE, WARN, ERROR, ALERT, FATAL,
		};
	public:
		static void initial();
		static void log(LoggerType type,const std::string info);
		static log4cpp::CategoryStream log(LoggerType type);
		static bool m_initialized;
	};

	extern std::string cvt2str(const char *s,...);

	//////////////////////////////////////////////////////////////////////////////
	// class params;
	struct HParams:public ConfigParser{
	public:
		std::string m_grammarDir;
		std::string m_xmlDir;
		std::string m_rootLabel;
		std::string m_queryFile;

		// Bayesian method;
		double		m_priorWeight;
		double		m_priorLenLambda;
		double		m_priorAlpha;


		// grammar derivation;
		bool		m_isolated;
		bool		m_withSym;
		bool		m_ruleSymbRep;
		bool        m_sameSymbRep;
		Geex::vec2  m_LayoutSize;

		int m_nTrain;

		// logging setting;
		HLogger::LoggerType m_attribLog;
		HLogger::LoggerType m_graphEditLog;
		HLogger::LoggerType m_analyzeLog;
		HLogger::LoggerType m_BGILog;
		HLogger::LoggerType m_sampleLog;
	public:
		HParams();

		virtual void Import(const char* filename, bool create_new = true);
		virtual void ImportOptValues(void);
		bool NoSymbRep(){ return !m_ruleSymbRep && !m_sameSymbRep;}
	private:
		std::string m_configPath;
	};

	extern HParams g_params;


#endif
#include "Common.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <cmath>
#include <stdarg.h>

	//////////////////////////////////////////////////////////////////////////////
	HParams::HParams()
	{
		m_configPath = "params.config";
		m_grammarDir = ".//data//Grammar//";
		m_xmlDir = ".//data//TestData//";
		m_queryFile = "queryRules.txt";
		m_rootLabel = "window";
		m_priorAlpha = 1.0;
		m_priorLenLambda = 0.8;
		m_priorWeight = 0.7;
		m_nTrain = 50;

		m_withSym = true;
		m_ruleSymbRep = true;
		m_sameSymbRep = true;
		m_isolated = true;
		m_LayoutSize = Geex::vec2(1.0 ,1.0);

		//m_analyzeLog = HLogger::LoggerType::NOTEST;
		m_graphEditLog = HLogger::LoggerType::NOTICE;
		m_attribLog = HLogger::LoggerType::NOTEST;
		m_analyzeLog = HLogger::LoggerType::NOTEST;
		m_BGILog = HLogger::LoggerType::NOTICE;
		m_sampleLog = HLogger::LoggerType::NOTEST;
		Import(m_configPath.c_str());
	}


	void HParams::Import(const char* filename, bool create_new) 
	{
		if(filename != NULL)
			m_configPath = filename;
		ConfigParser::Import( m_configPath.c_str(), create_new);
		ImportOptValues();
	}

	void HParams::ImportOptValues(void) 
	{
		if(HasOption("File", "grammar_path"))
			m_grammarDir = Get("File", "grammar_path");
		else m_grammarDir = "data/Grammar/";

		if(HasOption("File", "xml_path"))
			m_xmlDir = Get("File", "xml_path");
		else m_xmlDir = "data/TestData/";
		
		if(HasOption("File", "query_path"))
			m_queryFile = Get("File", "query_path");
		else m_queryFile = "queryRule.txt";

	
		if(HasOption("Dataset", "root_label"))
			m_rootLabel = Get("Dataset", "root_label");
		else m_rootLabel = "window";
		if(HasOption("Dataset", "train_size"))
			m_nTrain = GetScalar("Dataset", "train_size");
		else m_nTrain = 50;


		if(HasOption("Sampling", "symmetry"))
			m_withSym = IsEnabled("Sampling", "symmetry");
		else m_withSym = true;
		if(HasOption("Sampling", "rule_symbol_rep"))
			m_ruleSymbRep = IsEnabled("Sampling", "rule_symbol_rep");
		else m_ruleSymbRep = true;
		if(HasOption("Sampling", "symbol_same_rep"))
			m_sameSymbRep = IsEnabled("Sampling", "symbol_same_rep");
		else m_sameSymbRep = true;
		if(HasOption("Sampling", "isolated"))
			m_isolated = IsEnabled("Sampling", "isolated");
		else m_isolated = true;
		if(HasOption("Sampling", "layout_size"))
		{
			std::vector<double> sizeArray;
			sizeArray = GetScalarArray("Sampling", "layout_size");
			m_LayoutSize[0] = sizeArray[0];  m_LayoutSize[1] = sizeArray[1];
		}else m_LayoutSize = Geex::vec2(1.0, 1.0);


		//// logging;
		std::vector<double> logArray;
		if(HasOption("Logging", "log"))
			logArray = GetScalarArray("Logging", "log");	
		else logArray = std::vector<double>(5, 1.0);
		m_graphEditLog = HLogger::LoggerType::NOTICE;
		m_attribLog = HLogger::LoggerType::NOTEST;
		m_analyzeLog = HLogger::LoggerType::NOTEST;
		m_BGILog = HLogger::LoggerType::NOTICE;
		m_sampleLog = HLogger::LoggerType::NOTEST;	
	}



	HParams g_params;

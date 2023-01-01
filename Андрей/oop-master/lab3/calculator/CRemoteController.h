#pragma once
#include "CCalculator.h"
#include "common_libs.h"

class CRemoteController
{
public:
	CRemoteController(CCalculator& calculator, std::istream& input, std::ostream& output);
	bool HandleCommand();

	struct Arguments
	{
		std::string identifierName;
		char operationSymbol;
		std::string firstOperand;
		std::string secondOperand;
	};

	CRemoteController::Arguments ParseArguments(const std::string& inputLine);

private:
	bool CreateVar(const std::string& args);
	bool SetVarValue(const std::string& args);
	bool CreateFunctionWithValue(const std::string& args);
	bool PrintIdentifier(const std::string& args);
	bool PrintAllVars(const std::string& args);
	bool PrintAllFunctions(const std::string& args);
	bool Help(const std::string& args) const;

private:
	using Handler = std::function<bool(std::string& args)>;

	using ActionMap = std::map<std::string, Handler>;

	CCalculator& m_calculator;
	std::istream& m_input;
	std::ostream& m_output;

	const ActionMap m_actionMap;
};

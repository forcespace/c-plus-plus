#pragma once
#include "common_libs.h"

class CCalculator
{
public:
	using Expression = std::pair<char, std::vector<std::string>>;
	using Function = std::pair<std::string, Expression>;

	bool CreateNewVar(const std::string& varName);
	bool SetVarValue(const std::string& varName, const std::string& value);
	bool SetFunctionValue(const Function& function);
	double GetIdentifierValue(const std::string& identifierName) const;
	std::map<std::string, double> GetAllVars() const;
	std::map<std::string, double> GetAllFunctions() const;

private:
	std::vector<char> m_operators = { '+', '-', '*', '/' };

	std::map<std::string, double> m_memory;
	std::map<std::string, Expression> m_memoryFn;
		
	bool IsVarAlreadyExist(const std::string& varName) const;
	bool IsValidName(const std::string& varName) const;
	bool IsValidFunction(const Function& function) const;
	bool isValidOperands(const std::string& functionName, const std::vector<std::string>& operands) const;
	double CalculateFunctionValue(const std::string& functionName) const;
};

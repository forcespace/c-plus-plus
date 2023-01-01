#include "CRemoteController.h"
#include "common_libs.h"

CRemoteController::CRemoteController(CCalculator& calculator, std::istream& input, std::ostream& output)
	: m_calculator(calculator)
	, m_input(input)
	, m_output(output)
	, m_actionMap({ { "var", [this](const std::string& args) { return CreateVar(args); } },
		  { "let", [this](const std::string& args) { return SetVarValue(args); } },
		  { "fn", [this](const std::string& args) { return CreateFunctionWithValue(args); } },
		  { "print", [this](const std::string& args) { return PrintIdentifier(args); } },
		  { "printvars", [this](const std::string& args) { return PrintAllVars(args); } },
		  { "printfns", [this](const std::string& args) { return PrintAllFunctions(args); } },
		  { "help", [this](const std::string& args) { return Help(args); } } })
{
}

bool CRemoteController::HandleCommand()
{
	std::string commandLine;
	std::getline(m_input, commandLine);

	std::istringstream stream(commandLine);

	std::string action;
	std::string args;
	std::getline(stream, action, ' ');
	args = std::getline(stream, args) ? args : "";

	auto it = m_actionMap.find(action);
	if (it != m_actionMap.end())
	{
		return it->second(args);
	}

	return false;
}

bool CRemoteController::Help(const std::string& /*args*/) const
{
	m_output << "var - create variable without value" << std::endl;
	m_output << "let - create(or initialize) variable with value" << std::endl;
	m_output << "fn - create function type of: <variable> <operator(+, -, *, /)> <variable>" << std::endl;
	m_output << "print <identifier> - print identifier (if identifier did not initialize you get NaN)" << std::endl;
	m_output << "printvars - print all vars with their values" << std::endl;
	m_output << "printfn - print all functions with their values" << std::endl;

	return true;
}

bool CRemoteController::CreateVar(const std::string& args)
{
	auto arguments = ParseArguments(args);
	if (arguments.identifierName.empty() || !arguments.firstOperand.empty() || !arguments.secondOperand.empty() || arguments.operationSymbol != ' ')
	{
		return false;
	}

	return m_calculator.CreateNewVar(arguments.identifierName);
}

bool CRemoteController::SetVarValue(const std::string& args)
{
	auto arguments = ParseArguments(args);
	if (arguments.identifierName.empty() || arguments.firstOperand.empty() || !arguments.secondOperand.empty() || arguments.operationSymbol != ' ')
	{
		return false;
	}

	return m_calculator.SetVarValue(arguments.identifierName, arguments.firstOperand);
}

bool CRemoteController::CreateFunctionWithValue(const std::string& args)
{
	auto arguments = ParseArguments(args);
	std::vector<std::string> expression;
	if (!arguments.firstOperand.empty())
	{
		expression.push_back(arguments.firstOperand);
	}
	
	if (!arguments.secondOperand.empty())
	{
		expression.push_back(arguments.secondOperand);
	}

	return m_calculator.SetFunctionValue(std::pair<std::string, CCalculator::Expression>(arguments.identifierName, std::pair<char, std::vector<std::string>>(arguments.operationSymbol, expression)));
}

bool CRemoteController::PrintAllFunctions(const std::string& /*args*/)
{
	auto functionMap = m_calculator.GetAllFunctions();
	if (functionMap.empty())
	{
		m_output << "There is no functions" << std::endl;
		return true;
	}

	for (const auto element : functionMap)
	{
		m_output << element.first << " : ";

		if (std::isnan(element.second))
		{
			m_output << "nan" << std::endl;
		}
		else
		{
			m_output << std::fixed << std::setprecision(2) << element.second << std::endl;
		}
	}

	return true;
}

bool CRemoteController::PrintAllVars(const std::string& /*args*/)
{
	auto varsMap = m_calculator.GetAllVars();
	if (varsMap.empty())
	{
		m_output << "There is no vars" << std::endl;
		return true;
	}

	for (const auto element : varsMap)
	{
		m_output << element.first << " : "; 
		
		if (std::isnan(element.second))
		{
			m_output << "nan" << std::endl; 
		}
		else
		{
			m_output << std::fixed << std::setprecision(2) << element.second << std::endl;
		}
	}

	return true;
}

bool CRemoteController::PrintIdentifier(const std::string& args)
{
	auto arguments = ParseArguments(args);
	if (arguments.identifierName.empty() || !arguments.firstOperand.empty() || !arguments.secondOperand.empty() || arguments.operationSymbol != ' ')
	{
		m_output << "You missed identifier" << std::endl;
		return false;
	}

	if (std::isnan(m_calculator.GetIdentifierValue(arguments.identifierName)))
	{
		m_output << "nan" << std::endl;
	}
	else
	{
		m_output << arguments.identifierName << " : " << std::fixed << std::setprecision(2) << m_calculator.GetIdentifierValue(arguments.identifierName) << std::endl;
	}

	return true;
}

CRemoteController::Arguments CRemoteController::ParseArguments(const std::string& inputLine)
{
	Arguments arguments;
	arguments.identifierName = "";
	arguments.firstOperand = "";
	arguments.operationSymbol = ' ';
	arguments.secondOperand = "";

	if (inputLine.empty())
	{
		return arguments;
	}

	std::istringstream stream(inputLine);
	std::string name;

	stream >> name;

	if (name.empty())
	{
		return arguments;
	}

	arguments.identifierName = name;

	std::string equalSymbol;
	stream >> equalSymbol;

	if (equalSymbol != "=")
	{
		return arguments;
	}

	std::string operand;
	std::string operationSymbol;
	stream >> operand;

	if (operand.empty())
	{
		return arguments;
	}

	arguments.firstOperand = operand;
	stream >> operationSymbol;

	if (operationSymbol.empty())
	{
		return arguments;
	}

	arguments.operationSymbol = operationSymbol[0];
	stream >> operand;

	if (operand.empty())
	{
		return arguments;
	}

	arguments.secondOperand = operand;

	return arguments;
}

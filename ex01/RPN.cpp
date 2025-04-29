#include "RPN.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

RPN::RPN()
{
}

RPN::RPN( const RPN & src )
{
	*this = src;
}

RPN::RPN( std::string args )
{
	std::istringstream i_stream(args);
	std::string buf;
	while (getline(i_stream, buf, ' '))
	{
		isValidInput(buf);

		if (!buf.empty() && isDigit(buf))
			this->rpn.push(buf);
		else if (!buf.empty() && isOperator(buf))
			this->calculate(buf);
	}

	int result = static_cast<int>(std::atoi(this->rpn.top().c_str()));
	this->rpn.pop();


	if (!this->rpn.empty())
		throw std::runtime_error("stack is not empty");
	std::cout << result << std::endl;
}

/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

RPN::~RPN()
{
}


/*
** --------------------------------- OVERLOAD ---------------------------------
*/

RPN &				RPN::operator=( RPN const & rhs )
{
	this->rpn = rhs.rpn;
	return *this;
}

/*
** --------------------------------- METHODS ----------------------------------
*/


void RPN::isValidInput( std::string arg )
{
	if ((arg.size() != 1 || (arg < "0" || arg > "9")) && arg != "+" && arg != "-" && arg != "*" && arg != "/")
		throw std::runtime_error("is not valid input");
}

bool RPN::isDigit(std::string arg)
{
	if (arg < "0" || arg  > "9")
		return (false);
	return (true);
}

bool RPN::isOperator(std::string arg)
{
	if (arg != "+" && arg != "-" && arg != "*" && arg != "/")
		return (false);
	return (true);
}



void RPN::calculate( std::string operators )
{
	int val1;
	int val2;
	int result;

	val1 = static_cast<int>(std::atoi(this->rpn.top().c_str()));
	this->rpn.pop();
	if (this->rpn.empty())
		throw std::runtime_error("invalid input");

	val2 = static_cast<int>(std::atoi(this->rpn.top().c_str()));
	this->rpn.pop();

	if (operators == "+")
		result = val2 + val1;
	else if (operators == "-")
		result = val2 - val1;
	else if (operators == "*")
		result = val2 * val1;
	else if (operators == "/")
		result = val2 / val1;
	else
		throw std::runtime_error("can not find operator");

	std::ostringstream oss;
	oss << result;
	this->rpn.push(oss.str());
}


/*
** --------------------------------- ACCESSOR ---------------------------------
*/


/* ************************************************************************** */
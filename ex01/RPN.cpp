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
		if (!buf.empty())
			this->rpn.push(buf);
	}

	int result = this->calculate();

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


void RPN::isValidDigit( std::string arg )
{
	if (arg.size() != 1 || arg < "0" || arg > "9")
		throw std::runtime_error("is not valid digit");
}

int RPN::calculate( void )
{
	int val1;
	int val2;
	std::string operators;

	int result;

	while (!this->rpn.empty())
	{
		val1 = static_cast<int>(std::atoi(this->rpn.top().c_str()));
		this->rpn.pop();
		if (this->rpn.empty())
			throw std::runtime_error("invalid input");
		isValidDigit(this->rpn.top());
		val2 = static_cast<int>(std::atoi(this->rpn.top().c_str()));
		this->rpn.pop();
		if (this->rpn.empty())
			throw std::runtime_error("can not find operator");
		operators = this->rpn.top();
		this->rpn.pop();
	
		if (operators == "+")
			result = val1 + val2;
		else if (operators == "-")
			result = val1 - val2;
		else if (operators == "*")
			result = val1 * val2;
		else if (operators == "/")
			result = val1 / val2;
		else
			throw std::runtime_error("can not find operator");

		if (this->rpn.empty())
			return (result);
	
		std::ostringstream oss;
	
		oss << result;
		this->rpn.push(oss.str());		
	}

	throw std::runtime_error("something went wrong");
}


/*
** --------------------------------- ACCESSOR ---------------------------------
*/


/* ************************************************************************** */
#ifndef RPN_HPP
# define RPN_HPP

# include <iostream>
# include <string>
# include <stack>
# include <fstream>
# include <sstream>
# include <algorithm>
# include <cstdlib>

class RPN
{
	public:

		RPN();
		RPN( RPN const & src );
		RPN( std::string args );
		~RPN();

		RPN &		operator=( RPN const & rhs );

	private:
		std::stack<std::string> rpn;

		void isValidDigit( std::string value );
		int calculate( void );

};

#endif /* ************************************************************* RPN_H */
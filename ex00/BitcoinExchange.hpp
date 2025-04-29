#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

# include <iostream>
# include <fstream>
# include <sstream>
# include <string>
# include <cstdlib>
# include <ctime>
# include <map>
# include <algorithm>

class BitcoinExchange
{

	public:

		BitcoinExchange();
		BitcoinExchange( BitcoinExchange const & src );
		BitcoinExchange( char* inputPath );
		~BitcoinExchange();

		BitcoinExchange &		operator=( BitcoinExchange const & rhs );

		class BadInputException : public std::exception {
			public:
				virtual const char *what() const throw();
		};

		class TooLargeNumberException : public std::exception {
			public:
				virtual const char *what() const throw();
		};

		class NotPositiveNumberException : public std::exception {
			public:
				virtual const char *what() const throw();
		};

		class IsNotValidValueException : public std::exception {
			public:
				virtual const char *what() const throw();
		};

		class IsNotValidHeader : public std::exception {
			public:
				virtual const char *what() const throw();
		};

	private:
		std::map<std::string, float> csvDatabase;

		void initializeCsvDatabase( void );
		void isValidDate( std::string date );
		void isValidValue( std::string value, bool isCsv );
		void isValidHeader( std::string ifs, char delim );
		float calculateExchange( std::string value, float rate );
		float searchLowerDateValue( std::string date );
		std::string trim( std::string src );

};


#endif /* ************************************************* BITCOINEXCHANGE_H */
#include "BitcoinExchange.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

BitcoinExchange::BitcoinExchange()
{
}

BitcoinExchange::BitcoinExchange( const BitcoinExchange & src )
{
	*this = src;
}

BitcoinExchange::BitcoinExchange( char* inputPath )
{
	std::string strBuf;
	std::string strPipeBuf;
	std::ifstream inputFile(inputPath);
	this->initializeCsvDatabase();

	// check header
	getline(inputFile, strBuf);
	isValidHeader(strBuf, '|');

	while (getline(inputFile, strBuf))
	{

		if (std::count(strBuf.begin(), strBuf.end(), '|') > 1)
		{
			std::cerr << "Error: invalid line" << std::endl;
			continue;
		}
		std::istringstream i_stream(strBuf);
		std::string inputFileKey;
		std::string inputFileValue;
		double csvDatabaseValue;
		double calculatedValue;

		getline(i_stream, strPipeBuf, '|');
		inputFileKey = trim(strPipeBuf);
		try {
			csvDatabaseValue = searchLowerDateValue(inputFileKey);			
		} catch (std::exception &e)
		{
			std::cerr << "Error: " << e.what() << " => " << inputFileKey << std::endl;
			getline(i_stream, strPipeBuf, '|');
			continue;
		}
		getline(i_stream, strPipeBuf, '|');
		inputFileValue = trim(strPipeBuf);
		try {
			calculatedValue = calculateExchange(inputFileValue, csvDatabaseValue);
			std::cout << inputFileKey << " => " << inputFileValue << " = " << calculatedValue << std::endl;
		} catch (std::exception &e)
		{
			std::cerr << "Error: " << e.what() << "." << std::endl;
			continue;
		}
	}
}


/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

BitcoinExchange::~BitcoinExchange()
{
}


/*
** --------------------------------- OVERLOAD ---------------------------------
*/

BitcoinExchange &				BitcoinExchange::operator=( BitcoinExchange const & rhs )
{
	if ( this != &rhs )
	{
		this->csvDatabase = rhs.csvDatabase;
	}
	return *this;
}



/*
** --------------------------------- METHODS ----------------------------------
*/

void BitcoinExchange::initializeCsvDatabase( void )
{
	std::string strBuf;
	std::string strCommaBuf;
	std::ifstream inputCsvFile("data.csv");

	// check header
	getline(inputCsvFile, strBuf);
	isValidHeader(strBuf, ',');

	while (getline(inputCsvFile, strBuf))
	{
		
		std::istringstream i_stream(strBuf);
		std::string key;

		for (int i = 0; getline(i_stream, strCommaBuf, ','); i++)
		{
			if (i % 2 == 0)
			{
				isValidDate(strCommaBuf);
				this->csvDatabase[strCommaBuf] = 0;
				key = strCommaBuf;
			}
			else if (i % 2 == 1)
			{
				isValidValue(strCommaBuf, true);
				this->csvDatabase[key] = static_cast<float>(std::atof(strCommaBuf.c_str()));
			}
		}
	}
}

std::string  BitcoinExchange::trim( std::string src )
{
    size_t start = src.find_first_not_of(" ");
    size_t end = src.find_last_not_of(" ");
    std::string dst = src.substr(start, end - start + 1);
    return dst;
}

float BitcoinExchange::searchLowerDateValue( std::string date )
{
	isValidDate(date);
	int year, month, day;
	char sep1, sep2;
	std::istringstream iss(date);
	iss >> year >> sep1 >> month >> sep2 >> day;
	// std::ostringstream oss;

	// oss << year << sep1 << month << sep2 << (day - 1);

	std::tm timeinfo = {};
	timeinfo.tm_year = year - 1900;
	timeinfo.tm_mon = month - 1;
	timeinfo.tm_mday = day - 1;

	char buffer[11];
	float result;
	std::strftime(buffer, sizeof(buffer), "%Y-%m-%d", &timeinfo);
	result = this->csvDatabase[std::string(buffer)];
	if (!result)
		return searchLowerDateValue(std::string(buffer));
	return (result);
}

float BitcoinExchange::calculateExchange( std::string value, float rate )
{
	isValidValue(value, false);
	float castValue = static_cast<float>(std::atof(value.c_str()));
	return (rate * castValue);
}

void BitcoinExchange::isValidDate( std::string date )
{
	int year, month, day;
	char sep1, sep2;
	std::istringstream iss(date);
	iss >> year >> sep1 >> month >> sep2 >> day;

	if (month > 12 || day > 31 || month <= 0 || day <= 0 || year < 2009 || year > 2025)
		throw BadInputException();
}

void BitcoinExchange::isValidValue( std::string value, bool isCsv )
{
	for (size_t i = 0; i < value.length(); i++)
	{
		if ((value[i] < '0' || value[i] > '9') && value[i] != '.' && value[i] != '-')
			throw IsNotValidValueException();
	}
	if (!isCsv)
	{
		float castValue = static_cast<float>(std::atof(value.c_str()));
		if (castValue < 0)
			throw NotPositiveNumberException();
		if (castValue > 1000)
			throw TooLargeNumberException();
	}
}

void BitcoinExchange::isValidHeader(std::string strBuf, char delim)
{
	std::istringstream ifs(strBuf);
	std::string buf;
	std::string header1 = "date";
	std::string header2;

	if (delim == ',')
		header2 = "exchange_rate";
	else
		header2 = "value";

	getline(ifs, buf, delim);
	buf = trim(buf);
	if (buf != header1) {
		std::cerr << "header1: " << buf << std::endl;
		throw IsNotValidHeader();
	}
	getline(ifs, buf, delim);
	buf = trim(buf);
	if (buf != header2) {
		std::cout << "header2: " << buf << std::endl;
		throw IsNotValidHeader();
	}

	if (getline(ifs,buf, delim))
		throw IsNotValidHeader();

}

const char *BitcoinExchange::BadInputException::what() const throw() {
	return ("bad input");
}

const char *BitcoinExchange::TooLargeNumberException::what() const throw() {
	return ("too large a number");
}

const char *BitcoinExchange::NotPositiveNumberException::what() const throw() {
	return ("not a positive number");
}

const char *BitcoinExchange::IsNotValidValueException::what() const throw() {
	return ("is not valid value");
}

const char *BitcoinExchange::IsNotValidHeader::what() const throw() {
	return ("not valid header");
}

/*
** --------------------------------- ACCESSOR ---------------------------------
*/


/* ************************************************************************** */
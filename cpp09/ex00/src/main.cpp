#include "BitcoinExchange.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <chrono>

void	findKey( std::string line, const BitcoinExchange& data ) {
	size_t pipe_pos = line.find('|');
	std::string date = line.substr(0, 10);
	std::string value_str = line.substr(pipe_pos + 1);
	float value = std::stof(value_str);

	const std::map<std::string, float>& database = data.getDatabase();
	std::map<std::string, float>::const_iterator it = database.find(date);

	if (it == database.end())
	{
		it = database.upper_bound(date);
		it--;
	}
	std::cout
	<< line.substr(0, 10) << " => "
	<< it->second << " = "
	<< value * it->second
	<< std::endl;
}

void	checkExtraSpaces( std::string line ) {
	if (!(line[10] == ' ' && line[12] == ' '))
		throw std::runtime_error("Error: bad input => " + line);
	size_t count = 0;
	for (size_t i = 0; i < line.size(); ++i)
	{
		if (std::isspace(static_cast<unsigned char>(line[i])))
			count++;
	}
	if (count != 2)
		throw std::runtime_error("Error: bad input => " + line);
}

void	checkDateValidity( std::chrono::year_month_day& ymd ) {
	if (!ymd.ok()) {
		throw std::invalid_argument("Invalid date: " +
			std::to_string(static_cast<int>(ymd.year())) + "-" +
			std::to_string(static_cast<unsigned int>(ymd.month())) + "-" +
			std::to_string(static_cast<unsigned int>(ymd.day())));
	}
}

void	checkDateAndValueBounds( const BitcoinExchange& data, std::string line, float value ) {
	if (value > 1000)
		throw std::runtime_error("Error: number too large");
	if (value < 0)
		throw std::runtime_error("Error: number too small");

	std::string first_date = data.getDatabase().begin()->first;

	if (line.substr(0,10) < first_date)
		throw std::runtime_error("Error: date is before database in the past");

	std::map<std::string, float>::const_iterator it = data.getDatabase().end();
	it--;
	std::string last_date = it->first;

	if (line.substr(0,10) > last_date)
		throw std::runtime_error("Error: date is beyond database in future");
}

void	parseLine( std::string line, const BitcoinExchange& data ) {
	std::istringstream iss(line);
	int year;
	unsigned int month, day;
	char sep1, sep2, sep3, extra;
	float value;

	if (!(iss >> year >> sep1 >> month >> sep2 >> day >> sep3 >> value))
		throw std::runtime_error("Error: bad input => " + line);
	if (sep1 != '-' || sep2 != '-' || sep3 != '|')
		throw std::runtime_error("Error: bad input => " + line);
	if (iss >> extra && extra != 'f')
		throw std::runtime_error("Error: bad input => " + line);

	std::chrono::year_month_day ymd{
	std::chrono::year{year},
	std::chrono::month{month},
	std::chrono::day{day}
	};

	checkExtraSpaces(line);
	checkDateValidity(ymd);
	checkDateAndValueBounds(data, line, value);
}

int	main(int ac, char **av)
{
	if (ac != 2) {
		std::cout << "Usage: ./btc <filename>" << std::endl;
		return 1;
	}

	std::ifstream infile(av[1]);
	if (!infile.is_open()) {
		std::cout << "Error: could not open the file for reading" << std::endl;
		return 1;
	}

	try {
		BitcoinExchange database;
		if (database.getDatabase().size() == 0)
			throw std::runtime_error("Error: database empty");
		std::string line;

		while (1)
		{
			if(!std::getline(infile, line))
				break ;
			if (line == "date | value")
				continue ;
			try {
				parseLine(line, database);
				findKey(line, database);
			}
			catch (std::runtime_error& e) {
				std::cout << e.what() << std::endl;
			}
			catch (std::invalid_argument& e) {
				std::cout << e.what() << std::endl;
			}
		}
	} catch (std::runtime_error& e) {
		std::cout << e.what() << std::endl;
	}
	return 0;
}

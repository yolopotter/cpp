#include "RPN.hpp"
#include "unitTests.hpp"
#include <iostream>
#include <sstream>
#include <limits>

void	inputValidation( std::string input ) {
	if (input.empty())
		throw std::runtime_error("Error: empty input");
	std::istringstream	iss(input);
	std::string			str;
	std::string			valid = "0123456789+-*/";
	std::string			valid_nb = "0123456789";
	while (iss >> str)
	{
		if (str.size() == 1)
		{
			if (valid.find(str[0]) == std::string::npos)
				throw std::runtime_error("Error: input: " + str);
		}
		if (str.size() == 2 && str[0] == '-')
		{
			if (valid_nb.find(str[1]) == std::string::npos)
				throw std::runtime_error("Error: input: " + str);
			continue ;
		}
		if (str.size() != 1)
			throw std::runtime_error("Error: input: " + str);
	}
}

void	checkSubstractionOverflow( int nb1, int nb2 ) {
	if (nb1 <= 0 && nb2 > 0)
	{
		if (std::numeric_limits<int>::min() + nb2 > nb1)
			throw std::runtime_error("Error: overflow");
	}
	if (nb1 >= 0 && nb2 < 0)
	{
		if (std::numeric_limits<int>::max() + nb2 < nb1)
			throw std::runtime_error("Error: overflow");
	}
}

void	checkAdditionOverflow( int nb1, int nb2 ) {
	if (nb1 < 0 && nb2 < 0)
	{
		if (std::numeric_limits<int>::min() - nb2 > nb1)
			throw std::runtime_error("Error: overflow");
	}
	if (nb1 > 0 && nb2 > 0)
	{
		if (std::numeric_limits<int>::max() - nb2 < nb1)
			throw std::runtime_error("Error: overflow");
	}
}

void	checkMultiplicationOverflow( int nb1, int nb2 ) {
	if (nb1 == 0 || nb2 == 0)
		return ;

	int64_t res = static_cast<int64_t>(nb1) * static_cast<int64_t>(nb2);

	if (res > std::numeric_limits<int>::max() || res < std::numeric_limits<int>::min())
		throw std::runtime_error("Error: overflow");
}

int	calculate( int nb1, int nb2, std::string op_str ) {
	int res;
	char op = op_str[0];

	switch (op) {
		case '-':
			res = nb1 - nb2;
			checkSubstractionOverflow(nb1, nb2);
			return res;
		case '+':
			res = nb1 + nb2;
			checkAdditionOverflow(nb1, nb2);
			return res;
		case '*':
			res = nb1 * nb2;
			checkMultiplicationOverflow(nb1, nb2);
			return res;
		case '/':
			if (nb2 == 0)
				throw std::runtime_error("Error: division by 0");
			res = nb1 / nb2;
			return res;
		default:
			throw std::runtime_error("Error: unreachable code");
	}
}

bool	isNb( std::string token ) {
	std::string	valid_nb = "0123456789";

	if (token.size() == 1)
		if (valid_nb.find(token[0]) == std::string::npos)
			return 0;
	if (token.size() == 2)
		if (valid_nb.find(token[1]) == std::string::npos)
			return 0;
	return 1;
}

void	calculation( std::string input ) {
	RPN stack;

	std::istringstream	iss(input);
	std::string			token;
	while (iss >> token)
	{
		if (isNb(token))
			stack.getStack().push(std::stoi(token));
		else
		{
			if (stack.getStack().size() < 2)
				throw std::runtime_error("Error: operators not balanced with numbers");
			int nb2 = stack.getStack().top();
			stack.getStack().pop();
			int nb1 = stack.getStack().top();
			stack.getStack().pop();
			int res = calculate(nb1, nb2, token);
			stack.getStack().push(res);
		}
	}
	if (stack.getStack().size() != 1)
		throw std::runtime_error("Error: operators not balanced with numbers");
	std::cout << stack.getStack().top() << std::endl;
}

int	main(int ac, char **av)
{
	if (ac != 2) {
		std::cout << "Incorrect amount of arguments." << std::endl;
		std::cout << "Usage: ./RPN <reverse polish notation>" << std::endl;
		std::cout << "Do you want to launch automated unit-tests for overflows? (y/n) ";
		std::string	input;
		std::cin >> input;
		if (input == "y") {
			std::cout << std::endl;
			test1();
			test2();
			test3();
		}
		return 1;
	}
	try {
		inputValidation(av[1]);
		calculation(av[1]);
	}
	catch (std::runtime_error& e) {
		std::cout << e.what() << std::endl;
	}
	return 0;
}

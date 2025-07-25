#include "Harl.hpp"

void	Harl::debug( void ) {
	std::cout << "[ DEBUG ]" << std::endl;
	std::cout << "I love having extra bacon for my 420XL-double-cheese-\
undecuple-pickle-special-ketchup burger. I really do!" << std::endl << std::endl;
}

void	Harl::info( void ) {
	std::cout << "[ INFO ]" << std::endl;
	std::cout << "I cannot believe adding extra bacon costs more money. You didn’t put \
enough bacon in my burger! If you did, I wouldn’t be asking for more!" << std::endl << std::endl;
}

void	Harl::warning( void ) {
	std::cout << "[ WARNING ]" << std::endl;
	std::cout << "I think I deserve to have some extra bacon for free. I’ve been coming for \
years whereas you started working here since last month." << std::endl << std::endl;
}

void	Harl::error( void ) {
	std::cout << "[ ERROR ]" << std::endl;
	std::cout << "This is unacceptable! I want to speak to the manager now." << std::endl << std::endl;
}

void	defaultCase( void ) {
	std::cout << "Such level is beyond comprehension of Harl, he is simple man!" << std::endl;
}

void	Harl::complain( std::string level ) {

	void (Harl::*funcs[])(void) = {
		&Harl::debug,
		&Harl::info,
		&Harl::warning,
		&Harl::error
	};

	std::string levels[] = {"DEBUG", "INFO", "WARNING", "ERROR"};

	Harl obj;

	int no_of_level = -1;
	for (int i = 0; i < 4; i++) {
		if (levels[i] == level)
		{
			no_of_level = i;
			break ;
		}
	}

	switch (no_of_level) {
		case 0:
			(obj.*funcs[0])();
			// fall through
		case 1:
			(obj.*funcs[1])();
			// fall through
		case 2:
			(obj.*funcs[2])();
			// fall through
		case 3:
			(obj.*funcs[3])();
			break ;
		default:
			defaultCase();
	}
}

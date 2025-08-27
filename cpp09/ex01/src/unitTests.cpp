#include "../inc/unitTests.hpp"
#include <iostream>
#include <limits>
#include <stdexcept>
#include <iomanip>

#define RED "\033[0;31m"
#define GREEN "\033[0;32m"
#define CYAN "\033[0;36m"
#define RESET "\033[0;0m"

void	test1() {
	std::cout << std::endl;
	std::cout << RED << "test1: substraction overflow" << RESET << std::endl << std::endl;

	const int INT_MIN = std::numeric_limits<int>::min();
	const int INT_MAX = std::numeric_limits<int>::max();

	int tests[][2] = {
		{0, 0},						// Safe
		{INT_MAX, 0},				// Safe
		{0, INT_MAX},				// Safe
		{INT_MIN, 0},				// Safe
		{0, INT_MIN},				// Overflow
		{1, INT_MAX},				// Safe
		{INT_MAX, 1},				// Safe
		{-1, INT_MIN},				// Safe
		{INT_MIN, -1},				// Safe
		{-1, INT_MAX},				// Safe
		{INT_MAX, -1},				// Overflow
		{-2, INT_MAX},				// Overflow
		{INT_MIN, 1},				// Overflow
		{1, INT_MIN},				// Overflow
		{INT_MAX, INT_MAX},			// Safe
		{INT_MIN, INT_MIN},			// Safe
		{1073741824, 1073741824},	// Safe
		{-1073741824, 1073741824},	// Safe
		{-1073741825, 1073741824},	// Overflow
		{1073741824, -1073741824},	// Overflow
	};

	int num_tests = sizeof(tests) / sizeof(tests[0]);

	for (int i = 0; i < num_tests; ++i) {
		int nb1 = tests[i][0];
		int nb2 = tests[i][1];

		bool overflow = false;
		try {
			checkSubstractionOverflow(nb1, nb2);
		} catch (const std::runtime_error&) {
			overflow = true;
		}

		std::cout << "Test " << std::left << std::setw(2) << i + 1 << ": "
			<< std::left << std::setw(11) << nb1 << " - " << std::left << std::setw(11) << nb2
			<< " -> "  << (overflow ? "Overflow" : "Safe")
			<< std::endl;
	}
}
void	test2() {
	std::cout << std::endl;
	std::cout << RED << "test2: addition overflow" << RESET << std::endl << std::endl;

	const int INT_MIN = std::numeric_limits<int>::min();
	const int INT_MAX = std::numeric_limits<int>::max();

	int tests[][2] = {
		{0, 0},						// Safe
		{INT_MAX, 0},				// Safe
		{0, INT_MAX},				// Safe
		{INT_MIN, 0},				// Safe
		{0, INT_MIN},				// Safe
		{1, INT_MAX},				// Overflow
		{INT_MAX, 1},				// Overflow
		{-1, INT_MIN},				// Overflow
		{INT_MIN, -1},				// Overflow
		{INT_MIN, 1},				// Safe
		{1, INT_MIN},				// Safe
		{INT_MAX, INT_MAX},			// Overflow
		{INT_MIN, INT_MIN},			// Overflow
		{1073741824, 1073741824},	// Overflow
		{1073741824, 1073741823},	// Safe
		{-1073741825, -1073741824},	// Overflow
		{-1073741824, -1073741824},	// Safe
	};

	int num_tests = sizeof(tests) / sizeof(tests[0]);

	for (int i = 0; i < num_tests; ++i) {
		int nb1 = tests[i][0];
		int nb2 = tests[i][1];

		bool overflow = false;
		try {
			checkAdditionOverflow(nb1, nb2);
		} catch (const std::runtime_error&) {
			overflow = true;
		}

		std::cout << "Test " << std::left << std::setw(2) << i + 1 << ": "
			<< std::left << std::setw(11) << nb1 << " + " << std::left << std::setw(11) << nb2
			<< " -> "  << (overflow ? "Overflow" : "Safe")
			<< std::endl;
	}
}

void	test3() {
	std::cout << std::endl;
	std::cout << RED << "test3: multiplication overflow" << RESET << std::endl << std::endl;

	const int INT_MIN = std::numeric_limits<int>::min();
	const int INT_MAX = std::numeric_limits<int>::max();

	int tests[][2] = {
		{0, 0},					// Safe
		{INT_MAX, 0},			// Safe
		{0, INT_MAX},			// Safe
		{INT_MIN, 0},			// Safe
		{0, INT_MIN},			// Safe
		{INT_MIN, 1},			// Safe
		{1, INT_MIN},			// Safe
		{1, INT_MAX},			// Safe
		{INT_MAX, 1},			// Safe
		{-1, INT_MIN},			// Overflow
		{INT_MIN, -1},			// Overflow
		{2, INT_MAX / 2},		// Safe
		{INT_MAX / 2, 2},		// Safe
		{2, INT_MAX / 2 + 1},	// Overflow
		{INT_MAX / 2 + 1, 2},	// Overflow
		{-2, INT_MIN / 2},		// Overflow
		{INT_MIN / 2, -2},		// Overflow
		{-2, INT_MIN / 2 - 1},	// Overflow
		{INT_MIN / 2 - 1, -2},	// Overflow
		{INT_MAX, INT_MAX},		// Overflow
		{46341, 46341},			// Overflow
		{46340, 46340},			// Safe
		{-46341, 46341},		// Overflow
		{-46341, -46341},		// Overflow
	};

	int num_tests = sizeof(tests) / sizeof(tests[0]);

	for (int i = 0; i < num_tests; ++i) {
		int nb1 = tests[i][0];
		int nb2 = tests[i][1];

		bool overflow = false;
		try {
			checkMultiplicationOverflow(nb1, nb2);
		} catch (const std::runtime_error&) {
			overflow = true;
		}

		std::cout << "Test " << std::left << std::setw(2) << i + 1 << ": "
			<< std::left << std::setw(11) << nb1 << " * " << std::left << std::setw(11) << nb2
			<< " -> "  << (overflow ? "Overflow" : "Safe")
			<< std::endl;
	}
}

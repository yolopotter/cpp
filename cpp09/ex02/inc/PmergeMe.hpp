#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <deque>
#include <unordered_set>
#include <unordered_map>
#include <cmath>
#include <optional>
#include <regex>
#include <sstream>

template <typename T>
class PmergeMe {

	private:
		T		arr;
		size_t	comparisons;

	public:
		PmergeMe( void ) = delete;
		PmergeMe( T arr );
		PmergeMe( const PmergeMe& other ) = delete;
		PmergeMe& operator=( const PmergeMe& other ) = delete;
		~PmergeMe( void ) = default;

		static T	parse( int ac, char **av );
		void		sort( void );
		void		verifySorted( void ) const;
		void		print( std::string msg ) const;

		const T&	getData() const;
		size_t		getComparisons( void ) const;
};


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

namespace parsing_utils {

	template <typename T>
	void	checkDoubles( T& arr );

	template <typename T>
	T		parseSingle( std::string input );

	template <typename T>
	T		parseMultiple( char** input );
}

namespace algo_utils {

	template <typename T>
	size_t	relatedKey( T& main_chain, int value, std::unordered_map<int, int>& new_pairs );

	template <typename T>
	size_t	binaryInsertPos( T& main_chain, int value, std::unordered_map<int, int>& new_pairs, size_t& comparisons );

	size_t	getJacobsthalSequenceRounds( size_t b_values_to_insert );
	size_t	get_current( size_t b_values_to_insert, size_t k );

	template <typename T>
	T		fillFullBChain( T& main_chain, std::unordered_map<int, int>& new_pairs, std::optional<int> remainder );

	template <typename T>
	void	fillMainchain( T& main_chain, std::unordered_map<int, int>& new_pairs, std::optional<int> remainder, size_t& comparisons );

	template <typename T>
	T		recursiveSplitting( T& keys, size_t& comparisons);
}

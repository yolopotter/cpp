#include "PmergeMe.hpp"

namespace parsing_utils {

	template <typename T>
	void	checkDoubles( T& arr ) {
		std::unordered_set<int>	present;
		for (int nb : arr)
		{
			if (present.insert(nb).second == false)
				throw std::runtime_error("Error");
		}
	}

	template <typename T>
	T	parseSingle( std::string input ) {
		std::istringstream	iss(input);
		std::string			token;
		T					arr;

		std::regex valid("^\\d+(, \\d+)*$");

		if (!std::regex_match(input, valid))
			throw std::runtime_error("Error");

		while (std::getline(iss, token, ','))
		{
			size_t pos;
			int nb = std::stoi(token, &pos);
			if (nb < 1 || pos != token.length())
				throw std::runtime_error("Error");
			arr.push_back(nb);
		}
		checkDoubles(arr);
		return arr;
	}

	template <typename T>
	T	parseMultiple( char** input ) {
		size_t	i = 1;
		T		arr;

		while (input[i])
		{
			std::string token(input[i]);
			size_t pos;
			int nb = std::stoi(token, &pos);
			if (nb < 1 || pos != token.length())
				throw std::runtime_error("Error");
			arr.push_back(nb);
			i++;
		}
		checkDoubles(arr);
		return arr;
	}
}

namespace algo_utils {

	template <typename T>
	size_t	relatedKey( T& main_chain, int value, std::unordered_map<int, int>& new_pairs ) {
		for (auto& pair : new_pairs)
		{
			if (pair.second == value)
			{
				for (size_t j = 0; j < main_chain.size(); ++j)
				{
					if (main_chain[j] == pair.first)
						return j;
				}
			}
		}
		return main_chain.size();
	}

	template <typename T>
	size_t	binaryInsertPos( T& main_chain, int value, std::unordered_map<int, int>& new_pairs, size_t& comparisons ) {
		size_t left = 0;
		size_t right = relatedKey(main_chain, value, new_pairs);
		while (left < right)
		{
			size_t mid = left + (right - left) / 2;
			if (main_chain[mid] < value)
				left = mid + 1;
			else
				right = mid;
			comparisons++;
		}
		return left;
	}

	size_t	getJacobsthalSequenceRounds( size_t b_values_to_insert ) {
		size_t	k = 2;
		size_t	t = 3;
		while (t < (b_values_to_insert + 1))
		{
			k++;
			t = (pow(2, k + 1) + pow(-1, k)) / 3;
		}
		return (k - 1);
	}

	size_t get_current( size_t b_values_to_insert, size_t k ) {
		size_t t_curr = (pow(2, k + 1) + pow(-1, k)) / 3;
		if (t_curr > b_values_to_insert + 1)
			return (b_values_to_insert + 1);
		return t_curr;
	}

	template <typename T>
	T	fillFullBChain( T& main_chain, std::unordered_map<int, int>& new_pairs, std::optional<int> remainder ) {
		size_t k = 2;
		T full_b_chain;
		size_t amount_b_values_to_insert;
		if (remainder.has_value())
			amount_b_values_to_insert = main_chain.size() - 2 + 1;
		else
			amount_b_values_to_insert = main_chain.size() - 2;
		size_t jacobsthal_sequence_rounds = getJacobsthalSequenceRounds(amount_b_values_to_insert);
		for (size_t i = 0; i < jacobsthal_sequence_rounds; ++i, ++k)
		{
			size_t t_prev = (pow(2, k) + pow(-1, k - 1)) / 3;
			size_t t_curr = get_current(amount_b_values_to_insert, k );
			size_t new_additions = t_curr - t_prev;
			for (size_t j = 0; j < new_additions; ++j)
			{
				if (j == 0 && (i == jacobsthal_sequence_rounds - 1) && remainder.has_value())
				{
					full_b_chain.push_back(remainder.value());
					continue ;
				}
				size_t	b_pos = t_curr - j;
				if (b_pos > (main_chain.size() - 1))
					break ;
				size_t	last = new_pairs[main_chain[b_pos]];
				full_b_chain.push_back(last);
			}
		}
		return full_b_chain;
	}

	template <typename T>
	void	fillMainchain( T& main_chain, std::unordered_map<int, int>& new_pairs, std::optional<int> remainder, size_t& comparisons ) {
		main_chain.insert(main_chain.begin(), new_pairs[main_chain[0]]);
		T	full_b_chain = fillFullBChain(main_chain, new_pairs, remainder);
		for (size_t i = 0; i < full_b_chain.size(); ++i)
		{
			size_t value_to_insert = full_b_chain[i];
			size_t new_pos = binaryInsertPos(main_chain, value_to_insert, new_pairs, comparisons);
			main_chain.insert(main_chain.begin() + new_pos, value_to_insert);
		}
	}

	template <typename T>
	T	recursiveSplitting( T& keys, size_t& comparisons) {
		std::unordered_map<int, int> new_pairs;
		T	new_keys;
		T	main_chain;
		std::optional<int> remainder = std::nullopt;

		if (keys.size() < 2)
		{
			main_chain.push_back(keys[0]);
			return main_chain;
		}
		if (keys.size() % 2 != 0)
		{
			remainder =	keys.back();
			keys.pop_back();
		}
		for (size_t i = 0; i < keys.size(); i += 2)
		{
			if (keys[i] > keys[i + 1])
			{
				new_keys.push_back(keys[i]);
				new_pairs[keys[i]] = keys[i + 1];
			}
			else
			{
				new_keys.push_back(keys[i + 1]);
				new_pairs[keys[i + 1]] = keys[i];
			}
			comparisons++;
		}

		main_chain = recursiveSplitting(new_keys, comparisons);
		fillMainchain(main_chain, new_pairs, remainder, comparisons);
		return main_chain;
	}
}

namespace main_utils {

	size_t calcMaxComparisons(size_t size) {
		size_t sum = 0;
		for (size_t k = 1; k <= size; ++k) {
			double val = (3.0 / 4.0) * k;
			sum += static_cast<size_t>(std::ceil(std::log2(val)));
		}
		return sum;
	}
}

template <typename T>
PmergeMe<T>::PmergeMe( T arr ) {
	comparisons = 0;
	this->arr = std::move(arr);
};

template <typename T>
void	PmergeMe<T>::sort( void ) {
	T sorted = algo_utils::recursiveSplitting(this->arr, this->comparisons);
	this->arr = std::move(sorted);
	this->verifySorted();
}

template <typename T>
T	PmergeMe<T>::parse( int ac, char **av ) {
	if (ac < 2)
		throw std::runtime_error("Error");
	if (ac == 2)
		return (parsing_utils::parseSingle<T>(av[1]));
	else
		return (parsing_utils::parseMultiple<T>(av));
}

template <typename T>
void	PmergeMe<T>::print( std::string msg ) const {
	if (msg == "Before")
		std::cout << msg << ":";
	else
		std::cout << msg << ": ";
	for (int nb : getData())
		std::cout << " " << nb;
	std::cout << std::endl;
}

template <typename T>
void	PmergeMe<T>::verifySorted( void ) const {
	if(!std::is_sorted(arr.begin(), arr.end()))
		throw std::runtime_error("Sorting error");
}

template <typename T>
const	T&	PmergeMe<T>::getData() const {
	return arr;
}

template <typename T>
size_t	PmergeMe<T>::getComparisons( void ) const {
	return comparisons;
}

template class PmergeMe<std::vector<int>>;
template class PmergeMe<std::deque<int>>;

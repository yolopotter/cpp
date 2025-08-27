#include "PmergeMe.hpp"
#include <chrono>

namespace main_utils {
	size_t calcMaxComparisons(size_t size);
}

int	main(int ac, char **av)
{
	try {
		auto start_vector = std::chrono::high_resolution_clock::now();
		std::vector<int> vector_data = PmergeMe<std::vector<int>>::parse(ac, av);
		PmergeMe<std::vector<int>> sorter_vec(vector_data);
		sorter_vec.sort();
		auto end_vector = std::chrono::high_resolution_clock::now();

		auto start_deque = std::chrono::high_resolution_clock::now();
		std::deque<int> deque_data = PmergeMe<std::deque<int>>::parse(ac, av);
		PmergeMe<std::deque<int>> sorter_deq(deque_data);
		sorter_deq.print("Before");
		sorter_deq.sort();
		sorter_deq.print("After");
		auto end_deque = std::chrono::high_resolution_clock::now();

		std::chrono::duration<double, std::milli> duration_vector = end_vector - start_vector;
		std::cout
		<< "Time to process a range of "
		<< sorter_vec.getData().size()
		<< " elements with std::vector<int> : "
		<< duration_vector.count() << " ms" << std::endl;

		std::chrono::duration<double, std::milli> duration_deque = end_deque - start_deque;
		std::cout
		<< "Time to process a range of "
		<< sorter_deq.getData().size()
		<< " elements with std::deque<int>  : "
		<< duration_deque.count() << " ms" << std::endl;

		// size_t max_comparisons = main_utils::calcMaxComparisons(sorter_vec.getData().size());
		// std::cout << "Comparisons (vector): " << sorter_vec.getComparisons() << std::endl;		//uncomment to see amount of comparisons
		// std::cout << "Comparisons (deque): " << sorter_deq.getComparisons() << std::endl;		//uncomment to see amount of comparisons
		// std::cout << "Max comparisons F(n): " << max_comparisons << std::endl;					//uncomment to see amount of comparisons

	} catch (std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
		return 1;
	}

	return 0;
}

# to run the tests go to testing directory and run "python3 test_pmergeme.py"

import subprocess
import os
import random

BOLD = "\033[1m"
MAGENDA = "\033[95m"
RESET = "\033[0m"

def build():
	script_dir = os.path.dirname(os.path.abspath(__file__))
	makefile_dir = os.path.join(script_dir, "..")
	subprocess.run(["make", "re"], cwd=makefile_dir, check=True)

def run_test1(cmd, description):
	print(f"Test {description}: \"{BOLD}{MAGENDA}{cmd}{RESET}\"")
	result = subprocess.run(cmd, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)

	print(result.stdout)
	if result.stderr:
		print("Error output:")
		print(result.stderr)
	print("-" * 40)

def run_test2(num_elements):
	cmd = f"../PmergeMe `shuf -i 1-100000 -n {num_elements} | tr '\\n' ' '`"

	print(f"Test with {BOLD}{MAGENDA}{num_elements}{RESET} elements:")
	result = subprocess.run(cmd, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)

	print(result.stdout)
	if result.stderr:
		print("Error output:")
		print(result.stderr)
	print("-" * 40)

def parse_comparisons(output):
	comparisons_vec = comparisons_deq = max_comp = None
	for line in output.splitlines():
		if line.startswith("Comparisons (vector):"):
			comparisons_vec = int(line.split(":", 1)[1].strip())
		elif line.startswith("Comparisons (deque):"):
			comparisons_deq = int(line.split(":", 1)[1].strip())
		elif line.startswith("Max comparisons F(n):"):
			max_comp = int(line.split(":", 1)[1].strip())
	return comparisons_vec, comparisons_deq, max_comp

def test_comparisons_amount():
	test_cases = []

	for size in range(1, 101):
		values = random.sample(range(1, 10000), size)
		cmd = f"../PmergeMe {' '.join(map(str, values))}"
		test_cases.append(cmd)

	for cmd in test_cases:
		result = subprocess.run(cmd, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)

		comparisons_vec, comparisons_deq, max_comp = parse_comparisons(result.stdout)
		if all(x is not None for x in [comparisons_vec, comparisons_deq, max_comp]):
			# print(f"Vector {comparisons_vec}, deque {comparisons_deq}, max {max_comp}") # uncomment to show comaprisons amount
			assert comparisons_vec <= max_comp, f"Vector comparisons {comparisons_vec} is larger than F(n) = {max_comp} for input: {cmd}"
			assert comparisons_deq <= max_comp, f"Deque comparisons {comparisons_deq} is larger than F(n) = {max_comp} for input: {cmd}"


def main():
	test_cases_errors = [
		("../PmergeMe", "with no arguments"),
		("../PmergeMe a 2", "with invalid input"),
		("../PmergeMe 1a 2", "with invalid input"),
		("../PmergeMe ++1 2", "with invalid input"),
		("../PmergeMe +-1 2", "with invalid input"),
		("../PmergeMe --1 2", "with invalid input"),
		("../PmergeMe 2 -1", "with negative input"),
		("../PmergeMe 2 0", "with zero as input"),
		("../PmergeMe 2 2 3", "with double input"),
		("../PmergeMe \"2, 2, 3\"", "with double input"),
		("../PmergeMe \"2 1 3\"", "commas missing"),
		("../PmergeMe \"2, 1,  3\"", "too many spaces"),
		("../PmergeMe \"\"", "empty string"),
		("../PmergeMe \" 1 999999999999999999\"", "overflow"),
	]

	test_cases_basic = [
		("../PmergeMe 003 0004 0000001", "leading zeros"),
		("../PmergeMe 3", "one number"),
		("../PmergeMe 3 1", "two numbers"),
		("../PmergeMe 1 3", "already sorted, two numbers"),
		("../PmergeMe 1 3 5", "already sorted, three numbers"),
		("../PmergeMe 1 3 5 9", "already sorted, four numbers"),
		("../PmergeMe 3 7 8 1 2", "no quotes, 5 elements"),
		("../PmergeMe 3 7 8 1 2 4", "no quotes, 6 elements"),
		("../PmergeMe \"3, 7, 8, 1, 2\"", "quotes, 5 elements"),
		("../PmergeMe \"3, 7, 8, 1, 2, 4\"", "quotes, 6 elements"),
		("../PmergeMe \"4, 1, 3, 17, 5, 15, 20, 2, 6, 10, 8, 18, 9, 16, 19, 7, 14, 12, 11, 34, 21\"", "normal sorting case, 21 elements"),
		("../PmergeMe \"4, 1, 3, 17, 5, 15, 20, 2, 6, 10, 8, 18, 9, 16, 19, 7\"", "normal sorting case, 16 elements"),
		("../PmergeMe \"4, 1, 3, 20, 5, 15, 17, 8, 9, 2, 12, 11\"", "normal sorting case, 12 elements"),
		("../PmergeMe \"5, 1, 6, 10, 7, 8, 4, 9, 2\"", "normal sorting case, 9 elements"),
		("../PmergeMe \"4, 1, 3, 5, 6, 2, 9, 10\"", "normal sorting case, 8 elements"),
		("../PmergeMe \"17, 8, 9, 2, 12, 11, 3, 1\"", "normal sorting case, 8 elements"),
		("../PmergeMe \"2, 4, 9, 1, 5, 8, 3\"", "normal sorting case, 7 elements"),
		("../PmergeMe \"2, 9, 4, 6, 3, 7\"", "normal sorting case, 6 elements"),
	]


	for cmd, desc in test_cases_errors:
		run_test1(cmd, desc)

	for cmd, desc in test_cases_basic:
		run_test1(cmd, desc)

	test_sizes = [10, 100, 1000, 3000, 10000]
	for size in test_sizes:
		run_test2(size)

	test_comparisons_amount()


if __name__ == "__main__":
	build()
	main()

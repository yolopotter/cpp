#!/bin/bash

test_cases=(
	"8 9 * 9 - 9 - 9 - 4 - 1 +"		# 42
	"7 7 * 7 -"						# 42
	"1 2 * 2 / 2 * 2 4 - +"			# 0
	"-1 2 * 2 / 2 * 2 4 - +"		# -4
	"2"								# 2
	""								# Error
	"-1a 2 *"						# Error
	"0.4 2 *"						# Error
	"-1 a 2 *"						# Error
	"-10 2 *"						# Error
	"10 2 *"						# Error
	"-- 2 *"						# Error
	"(1 + 1)"						# Error
	"1 0 /"							# Error
	"1 +"							# Error
	"+ 1"							# Error
	"1 1 1 +"						# Error
	"1 4294967294 +"			# Error
	"9 9 9 * * 9 9 * * 9 * 9 * 9 * 6 * 2 * 2 * 2 *"	# 2066242608
	"9 9 9 * * 9 9 * * 9 * 9 * 9 * 6 * 2 * 2 * 3 *"	# overflow
	"9 9 9 * * 9 9 * * 9 * 9 * 9 * 6 * 2 * 2 * 3 * 9 /"	# overflow
)

for expr in "${test_cases[@]}"; do
	echo "Test: \"$expr\""
	./RPN "$expr"
	echo "-------------------------"
done

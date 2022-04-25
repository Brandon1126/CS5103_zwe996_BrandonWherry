#!/bin/bash

TEST_NUMS=('test0.txt' 'test1.txt' 'test2.txt' 'test3.txt' 'test4.txt' \
'test5.txt' 'test6.txt' 'test7.txt' 'test8.txt' 'test9.txt')

# This line is to remove old results
rm -f unusual_tests_results.txt

# Double forloop to execute all possible combinations of inputs. 100 different tests will be generated
# and redirected to unusual_tests_results.txt
for test_num_fileA in "${TEST_NUMS[@]}"
do
  for test_num_fileB in "${TEST_NUMS[@]}"
  do
    echo "@@@@@@ A = $test_num_fileA @@@@@@@@@ B = $test_num_fileB @@@@@@" >> unusual_tests_results.txt
    echo "Performing +, -, and * on A and B" >> normal_tests_results.txt
    ./BigNumberMath add testnums_unusual/"$test_num_fileA" testnums_unusual/"$test_num_fileB" &>> unusual_tests_results.txt
    ./BigNumberMath sub testnums_unusual/"$test_num_fileA" testnums_unusual/"$test_num_fileB" &>> unusual_tests_results.txt
    ./BigNumberMath mul testnums_unusual/"$test_num_fileA" testnums_unusual/"$test_num_fileB" &>> unusual_tests_results.txt
    echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" >> unusual_tests_results.txt
  done
done
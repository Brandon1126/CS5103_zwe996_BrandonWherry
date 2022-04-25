#!/bin/bash

TEST_NUMS=('test0.txt' 'test1.txt' 'test2.txt' 'test3.txt' 'test4.txt' \
'test5.txt' 'test6.txt' 'test7.txt' 'test8.txt' 'test9.txt')


# Double loop to execute all possible combinations of inputs. 100 different tests will be generated
for test_num_fileA in "${TEST_NUMS[@]}"
do
  for test_num_fileB in "${TEST_NUMS[@]}"
  do
    echo "@@@@@@ A = $test_num_fileA @@@@@@@@@ B = $test_num_fileB @@@@@@"
    echo "Performing +, -, and * on A and B"
    ./BigNumberMath add testnums_unusual/"$test_num_fileA" testnums_unusual/"$test_num_fileB"
    ./BigNumberMath sub testnums_unusual/"$test_num_fileA" testnums_unusual/"$test_num_fileB"
    ./BigNumberMath mul testnums_unusual/"$test_num_fileA" testnums_unusual/"$test_num_fileB"
    echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
  done
done

# Other testing
echo " "
echo "Invalid program inputs"
echo " "
echo " "

# No arguments provided
echo "Trying command ./BigNumberMath with no arguments"
./BigNumberMath
echo " "

# Wrong operation provided - "blah"
echo "Trying command ./BigNumberMath blah A.txt B.txt"
./BigNumberMath blah testnums_unusual/test0.txt testnums_unusual/test1.txt
echo " "

# Missing input one file
echo "Trying command ./BigNumberMath add A.txt"
./BigNumberMath add testnums_unusual/test0.txt
echo " "
echo "Testing completed"



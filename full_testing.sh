#!/bin/bash

# These lines remove old results
rm -f normal_tests_results.txt
rm -f unusual_tests_results.txt

echo "Starting unusual tests"
./testsuite_unusual.sh &>> unusual_tests_results.txt
echo "Done with unusual testing"
echo "@@@@@@@@@@@@@@@@@@@@@@@@@"
echo "Starting normal tests"
./testsuite_normal.sh &>> normal_tests_results.txt
echo "Done with normal testing"
echo "Wrote full test results to unusual_tests_results.txt and normal_tests_results.txt"
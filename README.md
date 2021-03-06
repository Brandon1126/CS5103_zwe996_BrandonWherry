## CS5103_zwe996_BrandonWherry
Version: 2.0
Course Project - Big number Computation

A.txt and B.txt are 2 source files for the numbers to be added, subtracted, or multiple.



# Allowed formats for A.txt or B.txt

Only 1 decimal place allowed, it can be at the very beginning, or very end, or anywhere between, or not at all.

For example:

 .012 - Allowed

  12. - Allowed

0.012 - Allowed

   12 - (Also allowed, do not need decimal)

Both A and B are allowed to have a decimal place.

Only accepts digits 0-9, and one decimal place. All other characters will produce an undefined result

Whitespace the end of each line is ignored. So one could use multiple lines.
For example: (in A.txt or B.txt)

3100000012

12345.677891   - Allowed

1234673

This would result in the number 310000001212345.6778911234673

All none numerical characters will throw an exception


# How to run code
To Compile: (when pwd = main directory)

./compile.sh

or

g++ src/*.cpp -o BigNumberMath 


# To add:

./BigNumberMath add A.txt B.txt

or 

./add.sh

or

bash add.sh


# To subtract:

./BigNumberMath sub A.txt B.txt

or 

./sub.sh

or

bash sub.sh



# To Multiply:

./BigNumberMath mul A.txt B.txt

or

./sub.sh

or

bash sub.sh


# Execution by scripts

If add.sh, sub.sh, or mul.sh are used, then the inputs are automatically loaded from A.txt and B.txt

# Format of the answer
Both A and B will be printed back in scientific notation with 5 sig figs.
This is to get a general sense of magnitude for each number.
The answer is printed out in scientific notation, and
the exact answer is redirected to "C.txt".

# Testing suites
See TESTSUITE.md to see testing details


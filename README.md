## CS5103_zwe996_BrandonWherry
Course Project - Big number Computation

A.txt and B.txt are 2 source files for the numbers to be added or subtracted.
Only addition works right now, subtraction will be fixed soon.



# Allowed formats for A.txt or B.txt

Only 1 decimal place allowed, it can be at the very beginning, or very end, or anywhere between.
For example:

 .012 - Allowed
  12. - Allowed
0.012 - Allowed
   12 - (Also allowed, do not need decimal)

Both A and B are allowed to have a decimal place.

Only accepts digits 0-9, and one decimal place

Whitespace the end of each line is ignored. So one could use multiple lines.
For example: (in A.txt or B.txt)

3100000012
12345.677891   - Allowed
1234673

This would result in the number 310000001212345.6778911234673

Whitespace at the beginning of line has undefined behavior. (this may be adjusted in the future)



# How to run code
To Compile: (when pwd = main directory)

./compile.sh

or

g++ src/*.cpp -o BigNumberMath  (if using g++)

To Run: (when pwd = main directory)

./BigNumberMath add A.txt B.txt

or 

./BigNumberMath sub A.txt B.txt (currently disabled, will be working soon)


# Format of the answer
Both A and B will be printed back in scientific notation with 5 sig figures.
This is to get a general sense of magnitude of the inputted numbers
The answer is printed back in scientific notation.
The exact answer is redirected to "C.txt".


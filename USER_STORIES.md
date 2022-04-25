# User Stories & Test Cases:


# Completed:
Story:
I should be able to multiply two numbers together, and the exact answer should be printed to a file, while the approximate
answer should be printed in scientific notation on the console.

Test cases:
Testing is demonstrated in TESTSUITE.md




Story:
I should be able to specify add when running the program, the answer should be printed in scientific notation, and also stored in "C.txt" in exact form.

Test cases:
a) If I entered two numbers that have the same sign, addition should be performed, 
and the sign should carry to the result.
b) If I entered two numbers that have a different sign, subtraction should be performed instead, and the sign of the result will be equal to the number with the higher absolute value.





Story:
I would like to load in two numbers by two file name arguments when running my program, and these numbers should be printed back to me in scientific notation, so I get a general sense of the number's I've loaded in.

Test cases:
a) If the file name is not found, I must get an error telling me exactly that.
b) If I do not enter two file names, for two numbers, I must get an error telling me that.
c) I should be able to enter file names with a relative or absolute path.
d) The first file I enter will be considered 'A', and the second file should be considered 'B'
e) I should be able to verify the numbers entered by seeing "A = 1.75e107" or "B = -2.56e-200" to confirm that the numbers were correctly obtained.
f) White space between numbers should be ignored, if there are any non-numberic characters (aside from "." and "-") I should get an error message. 




Story:
I should recieve the output of a big number computation in 2 ways, one is by a print out of the answer to screen in scientific notation, (A + B = 1.87e1045, for example) the other is to an output file named "C.txt" which should hold the exact result.

Test cases:
a) Both results, from console output and file output should match.
b) If C.txt already exists, it should be overwritten.





Story:
I should recieve the output of a big number computation in 2 ways, one is by a print out of the answer to screen in scientific notation, (A + B = 1.87e1045, for example) the other is to an output file named "C.txt" which should hold the exact result.

Test cases:
a) Both results, from console output and file output should match.
b) If C.txt already exists, it should be overwritten.





Story:
I should be able to specify subtraction (sub) when running the program, the answer should be printed in scientific notation, and also stored in "C.txt" in exact form.

Test cases:
a) If I entered two numbers that have the same sign, subtraction should be performed, but the larger number should appear first. For example, if I specify A - B, but |B| > |A|, then -(B - A) should be performed instead.
b) If I entered two numbers that have a different sign, addition should be performed instead, and the sign of the result will be equal to the number with the higher absolute value. For example, A + -B will be computed as A - B (where A and B are both positive).



# Obsolete:


None so far
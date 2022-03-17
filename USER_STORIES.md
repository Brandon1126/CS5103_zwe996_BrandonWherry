# User Stories & Test Cases:
(top is highest priority)



# Ongoing:

Story:
I would like to load in two numbers by two file name arguments when running my program.

Test cases:
a) If the file name is not found, I must get an error telling me exactly that.
b) If I do not enter two file names, for two numbers, I must get an error telling me that.
c) I should be able to enter file names with a relative or absolute path.
d) The first file I enter will be considered 'A', and the second file should be considered 'B'
e) I should be able to verify the numbers entered by seeing "A = 1.75e107" or "B = -2.56e-200" to confirm that the numbers were correctly obtained.
f) White space between numbers should be ignored, if there are any non-numberic characters (aside from "." and "-") I should get an error message.






Story:
I should be able to specify either -add, or -sub when running the program, two perform addition or subtraction.

Test cases:
a) If I do not specify an operation, I should be asked during runtime.
b) The operations should be performed are either A + B, or A - B.
c) A and B are both allowed to be negative, by specifying a negative sign in the file.







Story:
I should recieve the output of a big number computation in 2 ways, one is by a print out of the answer to screen in scientific notation, (C = 1.87e1045, for example) the other is to an output file named "output.txt" which should hold the exact result.

Test cases:
a) Both results, from console output and file output should match.
b) If output.txt already exists, it should be overwritten.












# Completed:


None so far








# Obsolete:


None so far
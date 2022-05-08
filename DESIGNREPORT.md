## Design Report

Big Number Computation.

A string approach to big number computation. I created the Bignum class to perform string-based arithmetic on numbers with
thousands of digits. The absolute limit on the number of digits would be 2^31 digits, although one would likely run into memory issues
prior to reaching this limit. Multiplication with thousands of digits is pretty quick, but one does see a noticeable
computation time with 10k or more. 


### Meeting first and second requirements:

Initially, I wanted to include the use of decimal places for both numbers, so I knocked out both requirements
right away. I intentionally made it so that both numbers could have a decimal, or not (and one with, and one without).
To work with decimal places, I made sure that when each number is read from an input file, the decimal place would be
detected and then removed, while its index would be saved, and the actual number would be stored as a separate string. This made the design of computation easier
as I could manipulate the decimal place of a Bignum, without actually shifting it around. If no decimal place is detected, the decimal place position would
automatically be set to the last index (the length of the input file string). This functionality is taken care up by the constructor
to the Bignum class. This constructor also detects if a negative sign is at the beginning. Note, if construction fails,
a Bignum of 1.0 is created instead.

Prior to adding support for addition and subtraction, I verified that Bignum objects could correctly print out inputted numbers.
This is the motivation behind getnum() and getexpnum(). The first of these prints out the exact number, while the second
prints out the number in scientific notation. Both are needed, as it's good to be able to understand the scale of the inputted numbers
at a glance, which was the fundamental need behind seeing the number in scientific notation. Note, that because of how the decimal place, and sign are stored,
both of these methods must correctly reconstruct their actual locations in the number, when called. I later added on these methods,
making it so that they detect non-numerical digits, and informing the user of the first non-numerical digit found.

Once I was able to correctly print out the numbers at play, I began work on addition. I first created A += B functionality for
in-place addition. the motivation was sound, as it seemed memory efficient to want to add number B into A without creating
a new Bignum object in the process. I later realized that this was unnecessary, as modern memory is on the order of gigabytes, it would
be faster to just create a 3rd Bignum object when addition is called, so I scraped the A += B approach to addition. 
I worked on C = A + B instead, so that when addition is called, a new Bignum object is created to store the result,
and then returned.

One requirement that was needed for addition, was a method that could decimal-align both numbers.
The creation of this method was important, as I wanted to ensure that this decimal alignment process was efficient
and did not depend on the ordering of the numbers. For example, the result of decimal alignment does not depend on which
number is considered 'first'. The idea is simple, when decimal-aligning two Bignums, the decimal place is compared first.
The Bignum with the lower decimal place is filled with zeros to the left (making sure to increase the decimal place while filling).
Once the decimal places are equal, zeros are then added to the right, for the number that carries less decimal places.
This alignment process happens from a helper method called decimal_align(). This method also uses two more helper methods that
add zeros to the left, or zeros to the right. It's significant to mention that when zeros are filled to the left, the stored
decimal place must be adjusted. For example, if 12.34 becomes 00012.34, The decimal placed has moved from position 3, to position 6.
(index 2 to 5). If the decimal place is not adjusted, then when getnum is called, the number 00.01234 would be printed back out in stead.
Decimal alignment happens when addition or subtraction are called. once these helper methods are in place, addition becomes easier.
With both numbers decimal aligned, the addition method now takes segments from the stored number string, and converts these
segments to long long ints, and adds them, and converts the answer back into a string, piece by piece. If the result happens to be
one digit larger than both numbers, then we know a carry has happened. If the result somehow ends up being just '0000000',
then additional care was given to ensure that all zeros were accounted for it. Subtraction works in a similar way to addition. 
Decimal alignment happens at the beginning, and then subtraction is performed segment by segment.

The neat thing about the addition and subtraction methods, is that they can deal with strange sign cases. For example, let's say that we want to perform
A + B, but A is -3, and B is 5. What will happen instead, is that B - A will be performed (5 - 3). This means that addition should call
subtraction under these types of sign cases. Subtraction is called instead anytime addition is called when the signs of the two numbers are not
the same. The reverse happens with subtraction. Let's say (-5) - (3) is desired. The actual computation that will take place is
-(5 + 3). So if subtraction is called, and the signs are different, we must perform addition instead. The sign of the result will depend
on the number with the larger magnitude. This goes above the stated requirements, I took this approach simply because I wanted
all possible cases to be covered.

### Meeting third requirement - Multiplication:

I knew that multiplication would likely be the third requirement. I was also prepared for division! I'm glad division was not
included, however, because it would have been tricky. The way in which I added support for multiplication was pretty straight forward.
I started with some basic observations about multiplication in general. For example, if we're multiplying two numbers, one with 4 digits and the other with
3 digits, we know for certain that the result will not exceed 7 digits. This is true for included decimal places as well, and we
can easily know the decimal place of a result just by counting where the decimal place is on each number. I combined these two basic
facts for implementing multiplication. When multiplication is called, a resultant Bignum is created with the decimal place of the
result, and correct number of digits. Initially this Bignum is set to all 0's. I created an additional private constructor
for this purpose alone, in order to quickly create Bignum objects that were filled with only zeros. This resultant Bignum would
then store all cross-multiplications that occur when two Bignums are multiplied. A double for loop is used to perform all cross-multiplications
necessary. Depending on the compiler and system, multiplication is likely performed 8 digits at a time. This is because a long long int
value in C++ is up to 18 digits in base ten. However, Multiplication should work on any machine. The basic idea is to multiply 8 digits by 8 digits
, substring times substring, for all possible cross multiplications. This can be confusing, but here is an illustration of the process.

Suppose we want to multiply 123456789123456789 times 123456789, and
suppose 4 digits of each number will be used at a time (instead of 8 for simplicity).

The first step in this process is to create a Bignum that can hold 18 + 9 = 27 digits.
This is because we know 18 digits times 9 digits will at most have 27 digits.
(We also know where the decimal place would be, but I left out the decimals in this explanation for simplicity
but both number are allowed to have decimals).

The first multiplication would be 6789 * 6789. This result will be added to that 27 digit result Bignum
(which is initialized to be all 0s). Then the next multiplication will be 2345 * 6789, and then that will be added.
So on and so forth. Most of the code is dedicated to handling the indices of which pieces will be used.

Once the double loop is completed, the result will hold carry the product of the two Bignums.

Not much change (if any) was needed to add support for multiplication because I made sure that addition and subtract were flexible from the beginning.

No specific design pattern was used for the creation of the Bignum class. 
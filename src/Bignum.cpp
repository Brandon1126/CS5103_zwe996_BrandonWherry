/* 

The Bignum class is able to store numbers with millions of digits, 
and is able to add them while keeping complete precision.
The upper limit for the size of a Bignum is ~2 billion digits.
In a future update, this may be increased.

Author: 
Brandon W

Last Edit Date:
4/03/22

*/

#include "Bignum.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <climits>

using namespace std;

/*
Because the size of a long long int is machine dependent
The following global constant must be determined to figure out how many
digits should be included in each long long int.
*/
const int Bignum::DIGITS_PER_LL = (int)to_string(LLONG_MAX).size() - 2;
const int Bignum::MULTIPLICATION_DIGITS = (int)to_string(LLONG_MAX).size() / 2 - 1;

// How many sig figs to print out in scientific notation
const int Bignum::SIG_FIGS = 4;


//Constructors
Bignum::Bignum() {
	number = "00";
	decimal_place = 1;
}


Bignum::Bignum(string& file_string) {
	if (file_string[0] == '-') {
		// sign = 1 means the number is negative
		isNegative = true;
		file_string.erase(0, 1);
	} 
	decimal_place = file_string.find('.');
	if (decimal_place == -1) {
		decimal_place = file_string.size();
		number = file_string;
	} else {
		number = file_string.substr(0, decimal_place) + file_string.substr(decimal_place + 1);
	}
}


// Private constructor for internal use only
// This constructor creates a Bignum of zeros
Bignum::Bignum(int zero_count, int decimal_place) {
    string s(zero_count, '0');
    number = s;
    this->decimal_place = decimal_place;
}



// Returns the Bignum as a string
string Bignum::getnum() {
    this->compress();
	string return_string;
	if (isNegative) return_string.append(1, '-');
	if (decimal_place == number.size()) {
		return_string.append(number);
	} else {
		return_string.append(number.substr(0, decimal_place) + '.' + number.substr(decimal_place));
	}
	return return_string;
}


// Returns the Bignum as a string
string Bignum::getexpnum() {
    this->compress();
    if (this->getnum().compare("0.0") == 0) return "0.0e0";
    if (this->getnum().compare("-0.0") == 0) return "0.0e0";
	string return_string;
	if (isNegative) return_string.append(1, '-');
	int first_nonzero_digit_location = 0;
	// Finds most significant digit
	for (auto digit : number) {
		if (digit != '0') break;
		first_nonzero_digit_location++;
	}
	return_string.append(1, number[first_nonzero_digit_location]);
	return_string.append(1, '.');
	int digits_left = number.substr(first_nonzero_digit_location).size();
	if (digits_left >= 2) {
		return_string.append(number.substr(first_nonzero_digit_location + 1, SIG_FIGS));
	}
	else {
		return_string += '0';
	}
	int exponent = (decimal_place - 1) - (first_nonzero_digit_location);
	return_string.append(1, 'e');
	return_string.append(to_string(exponent));
	return return_string;
}


// Appends 0's to the left of the number, helper method
void Bignum::add_zeros_left(int zero_count) {
	string add_left(zero_count, '0');
	number.insert(0, add_left);
	decimal_place += zero_count;
}


// Appends 0's to the right of the number, helper method
void Bignum::add_zeros_right(int zero_count) {
	string add_right(zero_count, '0');
	number.insert(number.size(), add_right);
}


/*
Helper function, it's job is to align two numbers by decimal value.
If the numbers are already aligned, it does nothing.
For example:
If A = 134.15
and B = 3.4567

A.decimal_align(B) would transform both A and B, to be
A = 134.1500
B = 003.4567
*/
void Bignum::decimal_align(Bignum& other) {
	bool already_aligned = decimal_place == other.decimal_place and number.size() == other.number.size();
	if (already_aligned) return;
	int decimal_place_diff;
	if (decimal_place > other.decimal_place) {
		decimal_place_diff = decimal_place - other.decimal_place;
		other.add_zeros_left(decimal_place_diff);
	} else if (decimal_place < other.decimal_place) {
		decimal_place_diff = other.decimal_place - decimal_place;
		add_zeros_left(decimal_place_diff);
	}
	int size_diff;
	if (number.size() > other.number.size()) {
		size_diff = (int)(number.size() - other.number.size());
		other.add_zeros_right(size_diff);
	} else if (number.size() < other.number.size()) {
		size_diff = (int)(other.number.size() - number.size());
		add_zeros_right(size_diff);
	}
}


/**
 * Adds two Bignums
 * 
 * 
 * If sign(A) != sign(B), this method uses the following identity.
 * A + B = A -(-B)
 * 
 * 
 * Description:
 * This method converts segments of the number string into long long int,
 * and then adds them. If the result would be result in a carry, then a 1
 * must be added to the next segment. In the event that there is not another
 * segment to add to (we're at the MSB of the number), we insert a "1" to the
 * beginning of the number.
 * 
 * 
 * @param The other Bignum
 * @return A Bignum result
 * 
 * 
 */
Bignum Bignum::operator+(Bignum& other) {
	if (isNegative != other.isNegative) {
		other.isNegative = !other.isNegative;
		return *this - other;
	}

	decimal_align(other);
	bool is_carry = false;
	int end_pos = (int)number.size() - 1;
	int start_pos = end_pos - DIGITS_PER_LL;
	int pos_diff;
	int decimal_pos = decimal_place;
	string str_A, str_B, result;
	long long int num_A, num_B;

	while (true) {
		if (start_pos < 0) {start_pos = 0;}
		if (end_pos < 0) {break;}
		
		pos_diff = end_pos - start_pos + 1;
		str_A = number.substr(start_pos, pos_diff);
		str_B = other.number.substr(start_pos, pos_diff);
		num_A = stoll(str_A);
		num_B = stoll(str_B);
		num_A += num_B;
		if (is_carry) {
			num_A += 1;
			is_carry = false;
		}
		str_A = to_string(num_A);
		int size_diff = str_A.size() - str_B.size();
		if (size_diff < 0) {
			string addleft(-1 * size_diff, '0');
			str_A.insert(0, addleft);
		} else if (size_diff > 0) {
			is_carry = true;
			str_A = str_A.substr(1);
		}
		
		result.insert(0, str_A);
		if (is_carry and start_pos == 0) { 
			result.insert(0, 1, '1');
			decimal_pos += 1;
		}
		end_pos -= (DIGITS_PER_LL + 1);
		start_pos -= (DIGITS_PER_LL + 1);
	}
	Bignum C(result);
	C.decimal_place = decimal_pos;
	C.isNegative = isNegative;
	return C;
}


/**
 * Subtracts two Bignums.
 *
 * Description:
 * If |A| < |B|, then the following identity is used to ensure
 * that the first number dictates what the resulting sign will be
 *
 * A - B = -(B - A)
 *
 * If sign(A) != sign(B), then the following identity is used
 * to perform addition instead
 *
 * A - B = A + (-B)
 *
 * This method converts segments of the number string  into long long int,
 * and then subtracts them. If the result would be negative, then a borrow
 * must be performed. We assume we can always borrow, because |A| > |B|.
 * This is ensured by the above property.
 * 
 * 
 * @param Bignum to be added
 * @return a Bignum result
 * 
 */
Bignum Bignum::operator-(Bignum& other) {
	bool is_A_lt_B = *this < other;
	Bignum A = is_A_lt_B ? other : *this;
	Bignum B = is_A_lt_B ? *this : other;
	if (is_A_lt_B) {
		A.isNegative = !A.isNegative;
		B.isNegative = !B.isNegative;
	}
	if (A.isNegative != B.isNegative) {
		B.isNegative = !B.isNegative;
		return (A + B);
	}
	bool is_borrow = false;
	int end_pos = (int)number.size() - 1;
	int start_pos = end_pos - DIGITS_PER_LL;
	int pos_diff;
	int decimal_pos = A.decimal_place;
	string str_A, str_B, result;
	long long int num_A, num_B;
	while (true) {
		if (start_pos < 0) {start_pos = 0;}
		if (end_pos < 0) {break;}
		pos_diff = end_pos - start_pos + 1;
		str_A = A.number.substr(start_pos, pos_diff);
		str_B = B.number.substr(start_pos, pos_diff);
		num_A = stoll(str_A);
		num_B = stoll(str_B);
		if (is_borrow) {
			num_B += 1;
			is_borrow = false;
		}
		if (num_A < num_B) {
			num_A = stoll(str_A.insert(0, 1, '1'));
			is_borrow = true;
		}
		num_A -= num_B;
		str_A = to_string(num_A);
		int size_diff = str_A.size() - str_B.size();
		if (size_diff < 0) {
			string addleft(-1 * size_diff, '0');
			str_A.insert(0, addleft);
		} 
		result.insert(0, str_A);
		end_pos -= (DIGITS_PER_LL + 1);
		start_pos -= (DIGITS_PER_LL + 1);
	}
	Bignum C(result);
	C.decimal_place = decimal_pos;
	C.isNegative = A.isNegative;
	return C;
}



/**
 * Multiplies two Bignums.
 *
 * Description:
 * The basic idea is that a resulting Bignum is created to store all
 * Additions generated from a double for loop. This double for loop cross multiplies
 * all pieces of the two Bignums
 *
 *
 *
 * @param Bignum to be added
 * @return a Bignum result
 *
 */
Bignum Bignum::operator*(Bignum& other) {
    int size_A = (int)number.size();
    int size_B = (int)other.number.size();
    int result_size = size_A + size_B;
    int decimal_place_A = decimal_place;
    int decimal_place_B = other.decimal_place;
    int result_decimal_place = decimal_place_A + decimal_place_B;
    Bignum result_Bignum(result_size, result_decimal_place);
    Bignum temp_Bignum(result_size, result_decimal_place);
    string str_A, str_B;
    int x, y;
    long long int num_A, num_B;
    for (int i = (int)number.size(); i > 0; i -= MULTIPLICATION_DIGITS) {
        for (int j = (int)other.number.size(); j > 0; j -= MULTIPLICATION_DIGITS) {
            x = i - MULTIPLICATION_DIGITS >= 0 ? i - MULTIPLICATION_DIGITS : 0;
            y = j - MULTIPLICATION_DIGITS >= 0 ? j - MULTIPLICATION_DIGITS : 0;
            str_A = i - MULTIPLICATION_DIGITS >= 0 ?
                number.substr(x, MULTIPLICATION_DIGITS) :
                number.substr(x, i);
            str_B = j - MULTIPLICATION_DIGITS >= 0 ?
                other.number.substr(y, MULTIPLICATION_DIGITS) :
                other.number.substr(y, j);
            size_A = (int)str_A.size();
            size_B = (int)str_B.size();
            result_size = size_A + size_B;
            num_A = stoll(str_A);
            num_B = stoll(str_B);
            num_A *= num_B;
            str_A = to_string(num_A);
            if (result_size > (int)str_A.size()) {
                str_A.insert(0, result_size - (int)str_A.size(), '0');
            }
            temp_Bignum.number.replace(x + y, str_A.size(), str_A);
            result_Bignum = result_Bignum + temp_Bignum;
            temp_Bignum.number.replace(x + y, str_A.size(), str_A.size(), '0');
        }
    }
    result_Bignum.isNegative = isNegative ^ other.isNegative;
    return result_Bignum;
}


/**
 * 
 * Comparison operators go from MSB -> LSB, and compare each value one by one.
 * 
 * @param other Bignum that is compared against *This Bignum
 * @return true or false
 * 
 */
bool Bignum::operator<(Bignum& other) {
	decimal_align(other);

	for (int i = 0; i < number.size(); i++) {
		if (number[i] < other.number[i]) return true;
	}

	return false;
}
bool Bignum::operator>(Bignum& other) {
	decimal_align(other);

	for (int i = 0; i < number.size(); i++) {
		if (number[i] > other.number[i]) return true;
	}

	return false;
}


/**
 * Description:
 * Compress() removes leading 0s and trailing 0s.
 * This method is used at the end of addition or subtraction in order 
 * to remove excess 0s, should they arise.
 * 
 * @param None
 * @return None
 */
void Bignum::compress() {
	int pos = 0;
	while(true) {
		if (number[pos] == '0') {
		    if (decimal_place == 0) break;
			number.erase(pos, 1);
			decimal_place -= 1;
		}
		else {break;}
	}
	pos = number.size() - 1;
	while(true) {
		if (number[pos] == '0') {
		    if (decimal_place == pos + 1) break;
			number.erase(pos, 1);
			pos -= 1;
		}
		else {break;}
	}
	if (number.empty()) {
		number = "00";
		decimal_place = 1;
	}
}



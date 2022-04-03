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



// Returns the Bignum as a string
string Bignum::getnum() const {
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
string Bignum::getexpnum() const {
	string return_string;
	if (isNegative) return_string.append(1, '-');
	int first_nonzero_digit_location = 0;
	// Finds most signifigant digit
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
decimal_align() is also a helper function, it's job is to align two numbers by decimal value.
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



/*
adds 2 Bignums, returns a Bignum
*/
Bignum Bignum::operator+(Bignum& other) {
	// if (sign != other.sign) {
	// 	operator-=(other);
	// 	return;
	// }
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
			string addleft(size_diff, '0');
			str_A.insert(0, addleft);
		} else if (size_diff > 0) {
			is_carry = true;
			str_A = str_A.substr(1);
		}
		result.insert(0, str_A);
		if (is_carry and start_pos == 0) { 
			result.insert(0, "1");
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




/*
Subtraction member, not completed
*/
// void Bignum::operator-=(Bignum& other) {
// 	if (sign == other.sign) {
// 		operator+=(other);
// 		return;
// 	}
// 	decimal_align(Bignum);
// 	if (*this < other) {

// 	}
	
// }



/*

*/
// bool Bignum::operator>(Bignum& other) {}

// bool Bignum::operator<(Bignum& other) {}


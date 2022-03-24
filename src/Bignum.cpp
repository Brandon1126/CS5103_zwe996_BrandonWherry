/* 

Description:
Bignum class is to be able to store numbers with millions of digits, 
and is able to add them while keeping all precision.
The upper limit for the size of a Bignum is ~2 billion digits.
In a future update,
I will modify it so that it can exceed even this contraint.

Author: Brandon W
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
const int Bignum::DIGITS_PER_LL = (int)to_string(LLONG_MAX).size() - 1;


// How many sig figs to print out in scientific notation
const int Bignum::SIG_FIGS = 4;




/* 
This Constructor makes sure to extract the decimal point from the inputted string.
The decimal place is stored seperately.
If there is no decimal in the number, then the decimal place will be at the end
to make it clear
*/ 
Bignum::Bignum(string& file_string) {
	if (file_string[0] == '-') {
		// sign = 1 means the number is negative
		sign = 1;
		file_string.erase(0, 1);
	} else {
		sign = 0;
	}

	decimal_place = file_string.find('.');
	if (decimal_place == -1) {
		decimal_place = file_string.size();
		number = file_string;
	} else {
		number = file_string.substr(0, decimal_place) + file_string.substr(decimal_place + 1);
	}
}






/*
Printer function, either places a decimal at the end of the number, 
or where it should be
*/
string Bignum::print_num() const {
	string return_string;
	if (sign) return_string += '-';
	if (decimal_place == number.size()) {
		return_string += number;
	} else {
		return_string += number.substr(0, decimal_place) + '.' + number.substr(decimal_place);
	}
	return return_string;
}




/*
Scientific Notation Printer, this is to get a general sense of the size of input number
*/
void Bignum::print_scientific_notation() const {
	if (sign) cout << '-';
	int first_nonzero_digit_location = 0;
	// Finds most signifigant digit
	for (auto digit : number) {
		if (digit != '0') break;
		first_nonzero_digit_location++;
	}

	string first_signifigant_digits{number[first_nonzero_digit_location]};
	first_signifigant_digits += '.';
	int digits_left = number.substr(first_nonzero_digit_location).size();
	
	if (digits_left >= 2) {
		first_signifigant_digits += number.substr(first_nonzero_digit_location + 1, SIG_FIGS);
	}
	else {
		first_signifigant_digits += '0';
	}

	int exponent = (decimal_place - 1) - (first_nonzero_digit_location);
	cout << first_signifigant_digits << 'e' << exponent << endl;
}



// Appends 0's to the left of the number, helper function
void Bignum::add_zeros_left(int zero_count) {
	string add_left(zero_count, '0');
	number.insert(0, add_left);
	decimal_place += zero_count;
}



// Appends 0's to the right of the number, helper function
void Bignum::add_zeros_right(int zero_count) {
	string add_right(zero_count, '0');
	number.insert(number.size(), add_right);
}



// This function is to help deal with carry values
void Bignum::add_one_carry_over(int pos) {
	if (pos < 0) {
		add_zeros_left(1);
		pos = 0;
	}

	char value_to_be_increased = number[pos];
	if (value_to_be_increased == '9') {
		number[pos] = '0';
		add_zeros_left(1);
		pos = 0;
	} 
	number[pos] += 1;
}



/*
decimal_align() is also a helper function, it's job is to align two numbers by decimal value.
For example:
If A = 134.15
and B = 3.4567

A.decimal_align(B) would transform both A and B, to be
A = 134.1500
B = 003.4567
*/
void Bignum::decimal_align(Bignum& other) {
	cout << decimal_place << endl;
	cout << other.decimal_place << endl;
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
*/
void Bignum::operator+=(Bignum& other) {
	// if (sign != other.sign) {
	// 	operator-=(other);
	// 	return;
	// }
	
	combine(other);


}


/*
This is a helper member function, it is the function that actually does addition
The basic idea is that substr's of A and B are stored seperately, then stored as
long long ints. 
*/
void Bignum::combine(Bignum& other) {
	decimal_align(other);
	string temp_str_A, temp_str_B, temp_sum;
	long long int temp_num_A, temp_num_B;
	int beginning_pos;

	for (int i = number.size() - 1; i > 0; i -= DIGITS_PER_LL) {
		beginning_pos = i < DIGITS_PER_LL ? 0 : i - DIGITS_PER_LL;
		temp_str_A = number.substr(beginning_pos,DIGITS_PER_LL);
		temp_str_B = other.number.substr(beginning_pos,DIGITS_PER_LL);
		temp_num_A = stoll(temp_str_A);
		temp_num_B = stoll(temp_str_B);
		temp_num_A += temp_num_B;
		temp_sum = to_string(temp_num_A);
		if (temp_sum.size() > DIGITS_PER_LL) {
			add_one_carry_over(beginning_pos - 1);
			temp_sum = temp_sum.substr(1);
			number.replace(beginning_pos, DIGITS_PER_LL, temp_sum);
		} else if (temp_sum.size() < DIGITS_PER_LL and beginning_pos != 0) {
			int zero_count = DIGITS_PER_LL - temp_sum.size();
			string add_left(zero_count, '0');
			temp_sum.insert(0, add_left);
			number.replace(beginning_pos, DIGITS_PER_LL, temp_sum);
		} else {
			decimal_place += (temp_sum.size() - temp_str_A.size());
			number.replace(beginning_pos, DIGITS_PER_LL, temp_sum);
		}

	}
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


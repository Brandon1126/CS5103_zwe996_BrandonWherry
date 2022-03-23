/* 

Description:



 
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
const int Bignum::DIGITS_PER_ULL = (int)to_string(LLONG_MAX).size() - 1;


// How many sig figs to print out in scientific notation
const int Bignum::SIG_FIGS = 4;




// This Constructor makes sure to extract the decimal point from the inputted string
// If there is no decimal in the number, then the decimal place will be at the end
// to make it clear
Bignum::Bignum(string& file_string) {
	decimal_place = file_string.find('.');
	if (decimal_place == -1) {
		decimal_place = file_string.size();
		number = file_string;
	} else {
		number = file_string.substr(0, decimal_place) + file_string.substr(decimal_place + 1);
	}
}




void Bignum::print_num() const {
	if (decimal_place == number.size()) {
		cout << number << endl;
	} else {
		cout << number.substr(0, decimal_place) << '.' << number.substr(decimal_place) << endl;
	}
}

void Bignum::print_scientific_notation() const {
	int first_nonzero_digit_location = 0;

	// Finds first sig fig number, any non-zero value
	// This is because we could have leading zeros in our number
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
	cout << decimal_place << endl;
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
// It can also add a placevalue given a negative index position
// This would mean the original size of the number was not enough
void Bignum::add_one_carry_over(int pos) {
	if (pos < 0) {
		add_zeros_right(1);
		pos = 0;
	}

	char value_to_be_increased = number[pos];
	if (value_to_be_increased == '9') {
		number[pos] = '0';
		add_zeros_left(1);
		pos = 0;
		number[pos] += 1;
	} else {
		number[pos] += 1;
	}
}


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
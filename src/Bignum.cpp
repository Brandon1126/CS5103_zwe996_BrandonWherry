#include "Bignum.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <thread>
#include <climits>
#include <chrono>

using namespace std;

// Because the size of an unsigned long long int is machine dependent
// The following global constant must be determined to figure out how many
// digits should be included in each long long int.
// This value will most likely be 19, allowing for a little wiggle room to detect
// when we should carry

const int DIGITS_PER_ULL = (int)to_string(ULLONG_MAX).size() - 1;



Bignum::Bignum(string& file_string) {
	decimal_place = file_string.find('.');
	if (decimal_place == -1) {
		number = file_string;
	} else {
		number = file_string.substr(0, decimal_place) + file_string.substr(decimal_place + 1);
	}
}






void Bignum::print_num() {
	if (decimal_place == -1) {
		cout << number << endl;
	} else {
		cout << number.substr(0, decimal_place) << '.' << number.substr(decimal_place + 1) << endl;
	}
}

void Bignum::print_scientific_notation() {
	int first_nonzero_digit_location = 0;

	for (auto digit : number) {
		if (digit != '0') break;
		first_nonzero_digit_location++;
	}

	// cout << first_nonzero_digit_location << endl;

	string first_few_signifigant_digits{number[first_nonzero_digit_location]};

	first_few_signifigant_digits += '.';
	int digits_left = number.substr(first_nonzero_digit_location).size();
	
	if (digits_left >= 2)
		first_few_signifigant_digits += number.substr(first_nonzero_digit_location + 1, 4);
	else 
		first_few_signifigant_digits += '0';

	int exponent = (decimal_place - 1) - (first_nonzero_digit_location);

	cout << first_few_signifigant_digits << 'e' << exponent << endl;


}
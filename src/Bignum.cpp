/* 

The Bignum class is able to store numbers with millions of digits, 
and is able to add them while keeping all precision.
The upper limit for the size of a Bignum is ~2 billion digits.
In a future update, this may be increased.

Author: 
Brandon W

Last Edit Date:
3/24/22

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
Used for getting  
or where it should be
*/
string Bignum::getnum() const {
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
void Bignum::getexpnum() const {
	string return_string;
	if (sign) return_string += '-';
	int first_nonzero_digit_location = 0;
	// Finds most signifigant digit
	for (auto digit : number) {
		if (digit != '0') break;
		first_nonzero_digit_location++;
	}

	return_string += number[first_nonzero_digit_location] + '.';
	int digits_left = number.substr(first_nonzero_digit_location).size();
	if (digits_left >= 2) {
		return_string += number.substr(first_nonzero_digit_location + 1, SIG_FIGS);
	}
	else {
		return_string += '0';
	}
	int exponent = (decimal_place - 1) - (first_nonzero_digit_location);
	return_string += 'e' + tostring(exponent);
	return return_string;
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
void Bignum::add_one_carry_over(int pos, Bignum& other) {
	char value_to_be_increased = number[pos];
	if (value_to_be_increased == '9' and pos == 0) {
		number[pos] = '0';
		add_zeros_left(1);
		other.add_zeros_left(1);
		add_one_carry_over(pos, other);
	} else if (value_to_be_increased == '9' and pos != 0) {
		number[pos] = '0';
		add_one_carry_over(pos - 1, other);
	} else {
		number[pos] += 1;
	}

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
void Bignum::operator+(Bignum& other) {
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
	int end_pos = (int)number.size() - 1;
	int start_pos = end_pos - DIGITS_PER_LL;
	int current_size = (int)number.size();
	int size_change = 0;
	while (true) {
		if (start_pos < 0) {start_pos = 0;}
		if (end_pos < 0) {break;}
		substr_add_replace(start_pos, end_pos, other);
		size_change = (int)number.size() - current_size;
		if (size_change > 0) {
			end_pos += size_change;
			start_pos += size_change;
		}
		end_pos -= (DIGITS_PER_LL + 1);
		start_pos -= (DIGITS_PER_LL + 1);
	}
}

/*
Helper Function, implemented to help reduce the maount of code in combiner
it takes aa start pos and end pos
*/
void Bignum::substr_add_replace(int start_pos, int end_pos, Bignum& other) {
	int pos_diff = end_pos - start_pos + 1;
	string str_A = number.substr(start_pos, pos_diff);
	string str_B = other.number.substr(start_pos, pos_diff);
	long long int num_A = stoll(str_A);
	long long int num_B = stoll(str_B);
	num_A += num_B;
	string sum = to_string(num_A);
	int size_diff = pos_diff - sum.size(); 
	if (size_diff < 0 and start_pos == 0) {
		add_one_carry_over(start_pos, other);	
		number.replace(start_pos + 1, pos_diff, sum.substr(1));
	} else if(size_diff < 0 and start_pos != 0) {
		add_one_carry_over(start_pos, other);
		number.replace(start_pos + 1, pos_diff, sum.substr(1));
	} else if (size_diff > 0) {
		string addleft(size_diff, '0');
		sum.insert(0, addleft);
		number.replace(start_pos, pos_diff, sum);
	} else {
		number.replace(start_pos, pos_diff, sum);
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


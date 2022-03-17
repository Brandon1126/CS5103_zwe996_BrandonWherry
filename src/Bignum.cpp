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

int DIGITS_PER_ULL = (int)to_string(ULLONG_MAX).size() - 1;





Bignum::Bignum(string& file_string) {
	int digits_left = file_string.size();
	int index_counter = 0;
	string slice;
	while (digits_left > DIGITS_PER_ULL) {
		slice = file_string.substr(index_counter, DIGITS_PER_ULL);
		number.push_back(stoull(slice));
		index_counter += DIGITS_PER_ULL;
		digits_left -= DIGITS_PER_ULL;
	}
	if (digits_left > 0) {
		slice = file_string.substr(index_counter, digits_left);
		number.push_back(stoull(slice));
	}
}

void Bignum::print_num() {
	for (auto num : number) cout << num;
	cout << endl;
}
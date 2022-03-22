#include "Bignum.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <thread>
#include <climits>
#include <chrono>


using namespace std;


int driver(int argc, char const *argv[])
{
	ifstream number_a_file, number_b_file;
	string number_a_string, number_b_string;

	// string operation = argv[1];
	number_a_file.open(argv[2]);
	number_b_file.open(argv[3]);
    
    string line;
	while (getline(number_a_file, line)) {
		number_a_string += line;
	}
	number_a_file.close();

	while (getline(number_b_file, line)) {
		number_b_string += line;
	}
	number_b_file.close();
	
	Bignum number_a = Bignum(number_a_string);
	Bignum number_b = Bignum(number_b_string);


	// number_a.print_num();
	// number_b.print_num();

	number_a.print_scientific_notation();
	number_b.print_scientific_notation();

	return 0;
}


int main(int argc, char const *argv[]) {
	driver(argc, argv);
	
	

}
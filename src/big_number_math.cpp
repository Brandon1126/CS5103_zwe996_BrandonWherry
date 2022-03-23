/* 

Description:



 
Author: Brandon W


*/


#include "Bignum.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>


using namespace std;

string file_reader(string file) {
	ifstream number_file;
	number_file.open(file);
	string number_string;
	string line;
	while (getline(number_file, line)) {
		number_string.append(line);
	}
	number_file.close();
	return number_string;
}


int driver(int argc, char const *argv[]) {
	
	string file_A, file_B, operation;
	operation = argv[1];
	file_A = argv[2];
	file_B = argv[3];

    
  	string number_a_string, number_b_string;
  	number_a_string = file_reader(file_A);
  	number_b_string = file_reader(file_B);
	
	Bignum number_a = Bignum(number_a_string);
	Bignum number_b = Bignum(number_b_string);


	number_a.print_scientific_notation();
	number_b.print_scientific_notation();


	number_a.print_num();
	number_b.print_num();

	number_a.decimal_align(number_b);

	number_a.print_num();
	number_b.print_num();

	return 0;
}


int main(int argc, char const *argv[]) {
	driver(argc, argv);
	
	

}
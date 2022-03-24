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


void driver(int argc, char const *argv[]) {
	
	string file_A, file_B, operation;
	operation = argv[1];
	file_A = argv[2];
	file_B = argv[3];

    
  	string number_a_string, number_b_string;
  	number_a_string = file_reader(file_A);
  	number_b_string = file_reader(file_B);
	
	Bignum number_a = Bignum(number_a_string);
	Bignum number_b = Bignum(number_b_string);

	cout << "A = ";
	number_a.print_scientific_notation();
	cout << "B = ";
	number_b.print_scientific_notation();

	number_a += number_b;

	cout << "A + B = ";
	number_a.print_scientific_notation();

	ofstream output("C.txt");
	output << number_a.print_num() << endl;
	output.close();

	cout << "Full answer stored in C.txt" << endl;
}


int main(int argc, char const *argv[]) {
	driver(argc, argv);
	return 0;
}
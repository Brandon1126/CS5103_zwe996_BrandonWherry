/* 

Description:
Driver code for illustration of Bignum class.

Author: Brandon W

Last Edit Date:
3/24/22

*/


#include "Bignum.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>


using namespace std;

/*
Reads in file based on file name, and
returns all of the text in the file
with no escape characters.
*/
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

/*
Applies += operator with some QoL text
including scientific notation prints outs to get
a sense of how big the numbers are
*/
void adder(Bignum A, Bignum B) {
	cout << "A = ";
	A.print_scientific_notation();
	cout << "B = ";
	B.print_scientific_notation();
	A += B;
	cout << "A + B = ";
	A.print_scientific_notation();

	ofstream output("C.txt");
	output << A.print_num() << endl;
	output.close();

	cout << "Full answer stored in C.txt" << endl;
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

	adder(number_a, number_b);
}


int main(int argc, char const *argv[]) {
	driver(argc, argv);
	return 0;
}
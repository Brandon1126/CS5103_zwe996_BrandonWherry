/* 

Description:
Driver code for illustration of Bignum class.

Author: Brandon W

Last Edit Date:
4/03/22

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



void driver(int argc, char const *argv[]) {
	string file_A, file_B, operation;
	operation = argv[1];
	file_A = argv[2];
	file_B = argv[3];
    
  	string number_a_string, number_b_string;
  	number_a_string = file_reader(file_A);
  	number_b_string = file_reader(file_B);
	
	Bignum A(number_a_string);
	Bignum B(number_b_string);

	cout << "A = " << A.getnum() << endl;
	cout << "B = " << B.getnum() << endl;

	Bignum C = A + B;
	cout << "A + B = " << C.getnum() << endl;
}


int main(int argc, char const *argv[]) {
	driver(argc, argv);
	return 0;
}
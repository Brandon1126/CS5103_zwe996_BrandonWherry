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

Bignum bignum_ALU(Bignum& A, Bignum& B, string& operation) {
	if (operation == "add") {
		return A + B;
	}
	if (operation == "sub") {
		return A - B;
	}
    if (operation == "mul") {
        return A * B;
    }
	return A + B;
}

string operation_selector(string& operation) {
	if (operation == "add") {
		return "+";
	}
	if (operation == "sub") {
		return "-";
	}
	if (operation == "mul") {
        return "*";
    }

	return " (Error: unknown operation, default is addition, please state: 'add', 'sub', or 'mul') ";
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

	cout << "A = " << A.getexpnum() << endl;
	cout << "B = " << B.getexpnum() << endl;

	Bignum C = bignum_ALU(A, B, operation);
	cout << "A " << operation_selector(operation) << " B = " << C.getexpnum() << endl;

	cout << "Writing exact answer to C.txt" << endl;
	cout << endl;

    ofstream result("C.txt");
    string output_string(C.getnum());

    int characters_per_line = 100;
    for (int i = 0; i < output_string.size(); i += characters_per_line) {
        result << C.getnum().substr(i, characters_per_line);
        result << "\n";
    }

	result.close();

}

int main(int argc, char const *argv[]) {
	driver(argc, argv);
	return 0;
}
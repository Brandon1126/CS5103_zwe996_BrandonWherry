/* 

Description:
Driver code for illustration of Bignum class.

Author: Brandon W

Last Edit Date:
4/25/22

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
    // Addition is used if the operation is not recognized
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
	return "Failed to identify operator";
}

// main driver code to display the Bignum class in action
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

// this function is called if insufficient arguments are provided.
void helper_function() {
    cout << "Computation has been aborted, correct arguments not found!" << endl;
    cout << "Use one of the following:" << endl;
    cout << "./BigNumberMath add A.txt B.txt" << endl;
    cout << "./BigNumberMath sub A.txt B.txt" << endl;
    cout << "./BigNumberMath mul A.txt B.txt" << endl;
}


int main(int argc, char const *argv[]) {
    if (argc != 4) {
        helper_function();
        return -1;
    }
    string operation(argv[1]);
    bool is_operation_incorrect = operation.compare("add") != 0 and operation.compare("sub") != 0
        and operation.compare("mul") != 0;
    if (is_operation_incorrect) {
        helper_function();
        return -1;
    }

    // The driver code is executed by getting past the above checks
    // 3 commandline arguments must be given:
    // 1) the operation (add, sub, or mul)
    // 2) First input (A.txt for example)
    // 3) Second input (B.txt for example)
	driver(argc, argv);
	return 0;
}
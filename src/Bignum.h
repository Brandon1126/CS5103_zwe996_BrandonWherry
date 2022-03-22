#include <vector>
#include <string>

using namespace std;


class Bignum {
private:
	string number;
	int decimal_place;


public:
	Bignum(string&);
	void print_num();
	void print_scientific_notation();

};

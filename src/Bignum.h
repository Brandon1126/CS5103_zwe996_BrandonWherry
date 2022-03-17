#include <vector>
#include <string>

using namespace std;


class Bignum {
private:
	vector<unsigned long long int> number;


public:
	Bignum(string&);
	void print_num();

};

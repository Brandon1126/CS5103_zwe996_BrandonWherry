/* 

Description:



 
Author: Brandon W


*/


#include <vector>
#include <string>

using namespace std;


class Bignum {
public:
	Bignum(string&);
	void print_num() const;
	void print_scientific_notation() const;

	void decimal_align(Bignum&);


private:
	string number;
	int decimal_place;

	static const int DIGITS_PER_ULL;
	static const int SIG_FIGS;

	void add_zeros_left(int);
	void add_zeros_right(int);
	void add_one_carry_over(int);

};

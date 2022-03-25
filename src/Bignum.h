#include <vector>
#include <string>

using namespace std;

class Bignum {

public:
	Bignum(string&);
	string print_num() const;
	void print_scientific_notation() const;

	void operator+=(Bignum&); 
	void operator-=(Bignum&); // not implemented yet

private:
	string number;
	int decimal_place;
	bool sign;

	static const int DIGITS_PER_LL;
	static const int SIG_FIGS;

	void add_zeros_left(int);
	void add_zeros_right(int);
	void add_one_carry_over(int, Bignum&);

	void decimal_align(Bignum&);
	void substr_add_replace(int, int, Bignum&);

	void combine(Bignum&);
	void compress(Bignum&); // not implemented yet

	bool operator>(Bignum&); // not implemented yet
	bool operator<(Bignum&); // not implemented yet

};

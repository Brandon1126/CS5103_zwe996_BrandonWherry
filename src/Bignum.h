#include <vector>
#include <string>

using namespace std;

class Bignum {

public:
	//Constructors & Destructor
	Bignum();
	Bignum(string&);
	// ~Bignum();

	//Getters
	string getnum() const;
	string getexpnum() const;

	//operator overloads
	Bignum operator+(Bignum&); 
	Bignum operator-(Bignum&);
	Bignum operator*(Bignum&);

private:
	string number;
	int decimal_place;
	bool isNegative = false;

	static const int DIGITS_PER_LL;
	static const int SIG_FIGS;

	void add_zeros_left(int);
	void add_zeros_right(int);

	void decimal_align(Bignum&);
	void compress();

	bool operator<(Bignum&);
	bool operator>(Bignum&);
};

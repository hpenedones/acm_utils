#include <iostream>
#include <algorithm>
#include <vector>
#include <cassert>

using namespace std;


class BigInt
{
	public:

        BigInt(int);
	BigInt(const BigInt& n);
	BigInt(int repeat, int dig);

	BigInt operator+ (const BigInt& n);
	BigInt operator* (const BigInt & n);
        BigInt& operator= (const BigInt& n);
	bool operator== (const BigInt&);

	void print(ostream& os = cout) const;
        void read(istream& is = cin);

        BigInt mul_dig(int n) const;
        bool is_zero() const;
        void mul10exp(int n=1);

	private:

       
	BigInt();
	vector<int> digits;
        int sign;
};


BigInt::BigInt(): sign(1)
{
}

BigInt::BigInt(int repeat, int dig): sign(1), digits(repeat,dig)
{
}


BigInt::BigInt(int n)
{
	sign = 1;
    if (n == 0)
    {
	    digits.push_back(0);
	    return;
    }
    if(n < 0)
    {
	    sign = -1;
	    n = -n;
    }
    while(n > 0)
    {
     	digits.push_back(n % 10);
	n /= 10;
    }
}

BigInt::BigInt(const BigInt& n): digits(n.digits), sign(n.sign)
{

}

BigInt& BigInt::operator= (const BigInt& other)
{
    sign = other.sign;
    digits = other.digits;
    return *this;
}

void BigInt::print(ostream& os) const 
{
       	if (sign < 0)
		os << "-";
	for(vector<int>::const_reverse_iterator it = digits.rbegin(); it != digits.rend(); it++)
		os << *it;

}

void BigInt::read(istream& is)
{
        string s;
	is >> s;
	
	sign=1;

	int i=0;
	if(s[0]=='-')
	{
		sign=-1;
		i++;
	}

	digits.clear();
	for(int i=s.size()-1; i>=0;i--)
		digits.push_back(s[i]-'0');


}


BigInt BigInt::operator+ (const BigInt& other)
{
 	BigInt result;

	// ignoring signs for now...
	int i=0, carry = 0;
	int max_dig = max(digits.size(), other.digits.size());

	while(i < max_dig || carry>0) {
		
                int sum = carry;
		if(i < digits.size())
			sum += digits[i];
		if(i < other.digits.size())
			sum += other.digits[i];
		result.digits.push_back(sum % 10);
		carry = sum / 10;
		i++;
	}
	return result;

}

bool BigInt::operator== (const BigInt& other)
{
	if(sign != other.sign)
		return false;

	if(digits.size()!= other.digits.size())
		return false;
	for (int i = 0; i < digits.size(); i++) {	
		if (digits[i] != other.digits[i])
			return false;
	}
	return true;
}

BigInt BigInt::mul_dig(int n) const
{
   assert(n>=0 && n<10);

   if (n==0)
	   return BigInt(0);

   BigInt result;
   int carry = 0;
   for (int i = 0; i < digits.size(); i++) {
           int prod = n*digits[i] + carry;
	   result.digits.push_back(prod%10);
	   carry = prod / 10;
   }
   if(carry > 0)
	   result.digits.push_back(carry);
   return result;
}

void BigInt::mul10exp(int exp)
{
   if (is_zero() || exp == 0) return;

   digits.insert(digits.begin(), exp, 0);

}

BigInt BigInt::operator* (const BigInt & other)
{
        BigInt acc(0);

	for (int i = 0; i < digits.size(); i++) {
		BigInt result = other.mul_dig(digits[i]);
                result.mul10exp(i);
		acc = acc + result;
	}
        return acc;
}



bool BigInt::is_zero()  const
{
   for (int i = 0; i < digits.size(); i++) {
   	    if (digits[i] != 0)
		    return false;
   }
   return true;
}

ostream& operator<< (ostream& os, const BigInt& n)
{
	n.print(os);
	return os;
}




int main(int argc, const char *argv[])
{
        vector<BigInt> factorials;
	factorials.push_back(BigInt(1));
	
	for (int i = 1; i < 1001; i++) {
		factorials.push_back(BigInt(i)*factorials[i-1]);
	}

	int n;
	while ( cin >> n )
	{
		cout << n << "!" << endl;
		cout << factorials[n] << endl;
	}
	return 0;
}

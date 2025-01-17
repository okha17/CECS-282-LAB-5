// Osman Khan
// CECS 282-07
// Proj 5 - goldRabbits 
// 11/25/2019

#ifndef BIGINT_H
#define BIGINT_H
#include <vector>
#include <string>
using namespace std;
class BigInt
{
private:
	vector<char> storage;
public:
	BigInt();
	BigInt(string);
	BigInt(int);
	BigInt operator +(const BigInt&);
	BigInt operator ++(int);
	bool operator <= (const BigInt&);
	bool operator < (const BigInt&)const;
	bool operator == (const BigInt&);
	BigInt operator -(int);
	BigInt& operator = (const BigInt& B);
	friend ostream& operator << (ostream&, const BigInt &);
	void print();
};
#endif

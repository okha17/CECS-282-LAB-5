#include<iostream>
#include "BigInt.h"
#include <map>
using namespace std;

BigInt goldRabbits(BigInt);
void pause() { cout << "Press Enter to continue..."; getchar(); }

int main()
{
	BigInt B1("123456789123456789123456789123456789");
	BigInt B2(B1);
	BigInt MAX(INT_MAX);
	cout << "B1:" << B1 << "\nB2:" << B2 << "\nMAX:" << MAX << endl;
	pause();
	cout << "\nB1:";
	B1.print();
	cout << endl;
	pause();

	for (BigInt i = 0; i <= 3000; i++)
	{
		cout << "\ngoldrabbits(" << i << ") = " << goldRabbits(i);
	}
	pause();

	cout << "\nThis is the value of goldRabbits(3000)\n\n";
	BigInt gR3000 = goldRabbits(BigInt(BigInt(3000)));
	gR3000.print();

	pause();
	return 0;
}

BigInt goldRabbits(BigInt n)
{
	static map<BigInt, BigInt> fmap;

	fmap[0] = 1, fmap[1] = 1;

	if (fmap.find(n) == fmap.end()) 
	{
		fmap[n] = goldRabbits(n - 1) + goldRabbits(n - 2);
	}

	return fmap[n];
}

#include<iostream>
#include "BigInt.h"

// Constructor that converts int number into correct format
// for inserting int char vector
BigInt::BigInt(int num)
{
	while (num > 9)
	{
		int digit = num % 10;
		storage.push_back(digit);
		num /= 10;
	}
	storage.push_back(num);
}

// Default constructor to create storage vector
BigInt::BigInt()
{
	
}

// String constructor that formats a string and inserts it into the vector
BigInt::BigInt(string str)
{	
	string::reverse_iterator rit = str.rbegin();
	while (rit != str.rend())
	{
		storage.push_back((*rit++) - '0');
	}
}

// Print function that prints out the entire BigInt
void BigInt::print()
{
	vector<char>::reverse_iterator rit;
	for (rit = storage.rbegin(); rit != storage.rend(); rit++)
	{	
		cout << (int)* rit;
	}
	cout << endl;
}

// Overloaded friend functon for ostream that displays in
// scientific notation if the BigInt is bigger than 12 digits
ostream& operator << (ostream& os, const BigInt &B)
{
	if ((B.storage).size() > 12)
	{
		vector<char>::const_reverse_iterator rit;
		rit = (B.storage).rbegin();
		os << (int)* rit;
		os << ".";
		for (rit = (B.storage).rbegin() + 1; rit != (B.storage).rbegin() + 11; rit++)
		{
			os << (int)* rit;
		}
		os << "e" << (B.storage).size();
		return os;
	}
	else
	{
		vector<char>::const_reverse_iterator rit;
		for (rit = (B.storage).rbegin(); rit != (B.storage).rend(); rit++)
		{
			os << (int)* rit;
		}
		return os;
	}
}

// Overloaded asssignment operator that assings the calling object
// to the passed in value
BigInt& BigInt::operator=(const BigInt& B)
{
	storage.clear();
	vector<char>::const_iterator it;
	it = B.storage.begin();
	while (it != B.storage.end()) 
	{
		storage.push_back(*it++);
	}
	return *this;
}

// Overloaded operator for adding two BigInt values for the goldRabbits
// function. Compares for 3 cases between the sizes of the BigInts. 
// Order shouldn't matter if all carry outs taken care of.
BigInt BigInt::operator +(const BigInt& B)
{
	BigInt temp;
	vector<char>::const_iterator it1;
	it1 = storage.begin();
	vector<char>::const_iterator it2;
	it2 = B.storage.begin();
	int carry = 0;

	// if the size of the BigInt being added to the calling object
	// is bigger than the calling object this statment is entered
	if ((B.storage).size() > (this->storage.size()))
	{
		while (it1 != storage.end())
		{
			int sum = *it1 + *it2 + carry;
			if (sum > 9)
			{
				int digit = sum % 10;
				(temp.storage).push_back(digit);
				carry = sum / 10;
			}
			else
			{
				temp.storage.push_back(sum);
				carry = 0;
			}
			it2++;
			it1++;
		}
		while (it2 != B.storage.end())
		{
			if (carry != 0)
			{
				int sum2 = carry + *it2;
				if (sum2 > 9)
				{
					int digit = sum2 % 10;
					temp.storage.push_back(digit);
					carry = sum2 / 10;
				}
				else
				{
					temp.storage.push_back(carry + *it2);
					carry = 0;
				}
			}
			else
			{
				temp.storage.push_back(*it2);
			}
			it2++;
		}
		if (it2 == B.storage.end())
		{
			if (carry != 0)
			{
				temp.storage.push_back(carry);
				carry = 0;
			}
		}
		return temp;
	}
	// In this case the calling object is bigger than the object being added to it
	else if ((B.storage).size() < (this->storage.size()))
	{
		while (it2 != B.storage.end())
		{
			int sum = *it1 + *it2 + carry;
			if (sum > 9)
			{
				int digit = sum % 10;
				(temp.storage).push_back(digit);
				carry = sum / 10;
			}
			else
			{
				temp.storage.push_back(sum);
				carry = 0;
			}
			it2++;
			it1++;
		}
		while (it1 != storage.end())
		{
			if (carry != 0)
			{
				int sum2 = carry + *it1;
				if (sum2 > 9)
				{
					int digit = sum2 % 10;
					temp.storage.push_back(digit);
					carry = sum2 / 10;
				}
				else
				{
					temp.storage.push_back(carry + *it1);
					carry = 0;
				}
			}
			else
			{
				temp.storage.push_back(*it1);
			}
			it1++;
		}
		if (it1 == storage.end())
		{
			if (carry != 0)
			{
				temp.storage.push_back(carry);
			}
		}
		return temp;
	}
	// The final case is if the size of both objects is the same
	else 
	{
		while (it2 != B.storage.end() && it1 != storage.end())
		{
			int sum = *it1 + *it2 + carry;
			if (sum > 9)
			{
				int digit = sum % 10;
				(temp.storage).push_back(digit);
				carry = sum / 10;
			}
			else
			{
				temp.storage.push_back(sum);
				carry = 0;
			}	
			it2++;
			it1++;
		}
		if (carry != 0)
		{
			temp.storage.push_back(carry);
		}
		return temp;
	}
}

// Overloaded less than or equal to operator for the for loop in
// the call to goldRabbits. Comapres sizes then compares values
bool BigInt::operator <= (const BigInt& B)
{
	vector<char>::const_reverse_iterator rit1;
	rit1 = storage.rbegin();
	vector<char>::const_reverse_iterator rit2;
	rit2 = B.storage.rbegin();

	if (storage.size() < B.storage.size())
	{
		return true;
	}
	else if (storage.size() > B.storage.size())
	{
		return false;
	}
	else
	{
		while (rit2 != B.storage.rend() && rit1 != storage.rend())
		{
			if (*rit1 == *rit2)
			{
				rit1++;
				rit2++;
			}
			else if (*rit1 < *rit2)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
	}
	return true;

}

// Overloaded post increment operator for the for loop
// call to goldRabbits. Adds 1 to BigInt value.
BigInt BigInt::operator++(int dummy)
{
	BigInt temp(*this);
	storage.clear();
	vector<char>::const_iterator it1;
	int carry = 0;
	it1 = temp.storage.begin();

	int sum = *it1 + 1;
	if (sum > 9)
	{
		int digit = sum % 10;
		(storage).push_back(digit);
		carry = sum / 10;
	}
	else
	{
		storage.push_back(sum);
		carry = 0;
	}
	it1++;
	while (it1 != temp.storage.end())
	{
		if (carry == 0)
		{
			storage.push_back(*it1);
		}
		else 
		{
			sum = carry + *it1;
			if (sum > 9)
			{
				int digit = sum % 10;
				(storage).push_back(digit);
				carry = sum / 10;
			}
			else
			{
				storage.push_back(sum);
				carry = 0;
			}
		}
		it1++;
	}
	if (it1 == temp.storage.end())
	{
		if (carry != 0)
		{
			storage.push_back(carry);
		}
	}
	return *this;
}

//Overloaded subtract operator for the goldRabbits function
// Takes int passed in and subtracts either 1 or 2 for recrusive call
BigInt BigInt::operator -(int num)
{
	BigInt temp;
	vector<char>::const_iterator it1;
	it1 = storage.begin();
	BigInt numB(num);
	
	int value = storage.size() - numB.storage.size();

	for (int i = 0; i < value; i++)
	{
		numB.storage.push_back(0);
	}
	vector<char>::const_iterator it2;
	it2 = numB.storage.begin();

	// This case is for when the last digit in the BigInt is equal to or
	// larger than 2
	if (*it1 >= *it2) // 15 -2 = 13
	{
		while (it1 != storage.end() && it2 != numB.storage.end())
		{
			int diff = *it1 - *it2;
			temp.storage.push_back(diff);
			it1++;
			it2++;
		}
	}

	// In this case the size of the BigInt is 2
	else if (storage.size() == 2)// 11 - 2 = 9  21 - 2 = 19
	{
		int diff = 10 + *it1 - *it2;
		temp.storage.push_back(diff);
		it1++;
		if (*it1 != 1)
		{
			int diff = *it1 - 1;
			temp.storage.push_back(diff);
		}
	}

	// In this case the size of the BigInt is 3
	else if (storage.size() == 3) // 100 -2 = 98 110 - 2 = 108 / 200 -2 = 198 
	{
		int diff = 10 + *it1 - *it2;
		temp.storage.push_back(diff);
		it1++;
		if (*it1 == 0)
		{
			it1++;
			if (*it1 == 1)
			{
				temp.storage.push_back(9);
			}
			else
			{
				temp.storage.push_back(9);
				temp.storage.push_back(*it1 - 1);
			}
		}
		else if (*it1 == 1)
		{
			temp.storage.push_back(0);
			it1++;
			temp.storage.push_back(*it1);
		}
		else
		{
			temp.storage.push_back(*it1 - 1);
			it1++;
			temp.storage.push_back(*it1);
		}
	}

	// In the final case the size of the BigInt is 4
	// Since the call to goldRabbits goes up to 3000
	// the subtraction cases need to be implemented 
	else if (storage.size() == 4) // 1010 - 2 = 108
	{
		int diff = 10 + *it1 - *it2;
		temp.storage.push_back(diff);
		it1++;
		// 2nd place
		if (*it1 == 0)
		{
			it1++;
			// 3rd place
			if (*it1 == 0)
			{
				temp.storage.push_back(9);
				temp.storage.push_back(9);
				it1++;
				if (*it1 != 1)
				{
					temp.storage.push_back(*it1 - 1);
				}
			}
			// 3rd place
			else if (*it1 == 1)
			{
				temp.storage.push_back(9);
				temp.storage.push_back(0);
				it1++;
				temp.storage.push_back(*it1);				
			}
			// 3rd place
			else
			{	
				temp.storage.push_back(9);
				temp.storage.push_back(*it1 -1);
				it1++;
				temp.storage.push_back(*it1);
			}

		}
		// 2nd place 1010
		else if (*it1 == 1)
		{
			it1++;
			// 3rd place 1010 2010
			if (*it1 == 0) 
			{
				// 4th place 1010 1100
				it1++;
				if (*it1 == 1)
				{
					it1--;
					if (*it1 == 1)
					{
						//3rd place
						it1--;
						temp.storage.push_back(9);
						it1++;
					}
					//2nd place
					if (*it1 == 1)
					{
						temp.storage.push_back(0);
						it1++;
						temp.storage.push_back(*it1);
					}
					//2nd place
					else
					{	// 1010
						temp.storage.push_back(0);
						temp.storage.push_back(*it1);
						it1++;
						temp.storage.push_back(*it1);
					}
				}
				// 4th place
				else if(*it1 != 1)
				{
					it1--;
					it1--;
					temp.storage.push_back(0);
					it1++;
					temp.storage.push_back(*it1);
					it1++;
					temp.storage.push_back(*it1);
				}
				// 4th place
			}
			//1110 3rd place
			else if(*it1 == 1)
			{
				if(*it1 == 1)
				it1--;
				temp.storage.push_back(0);
				it1++;
				temp.storage.push_back(*it1);
				it1++;
				temp.storage.push_back(*it1);
			}
			// 3rd place
			else
			{
				it1--;
				temp.storage.push_back(0);
				it1++;
				temp.storage.push_back(*it1);
				it1++;
				temp.storage.push_back(*it1);
			}
		}
		// 2nd place 2020 - 2 = 2018
		else
		{
			temp.storage.push_back(*it1 - 1);
			it1++;
			temp.storage.push_back(*it1);
			it1++;
			temp.storage.push_back(*it1);
		}
	}
	return temp;
}

// Overloaded equality operator for the goldRabbits function
// Compares to BigInts to see if they have the same size and values
bool BigInt::operator == (const BigInt& B)
{
	vector<char>::const_reverse_iterator rit1;
	rit1 = storage.rbegin();
	vector<char>::const_reverse_iterator rit2;
	rit2 = B.storage.rbegin();

	if (storage.size() < B.storage.size())
	{
		return false;
	}
	else if (storage.size() > B.storage.size())
	{
		return false;
	}
	else
	{
		while (rit2 != B.storage.rend() && rit1 != storage.rend())
		{
			if (*rit1 == *rit2)
			{
				rit1++;
				rit2++;
			}
			else if (*rit1 < *rit2)
			{
				return false;
			}
			else
			{
				return false;
			}
		}
	}
	return true;
}

// The overloaded less than operator is needed for the key
// of the map. Compares BigInt values and sizes to see if calling object
// is less than passed in object. Needs to be const in order to compile
bool BigInt::operator < (const BigInt& B)const
{
	vector<char>::const_reverse_iterator rit1;
	rit1 = storage.rbegin();
	vector<char>::const_reverse_iterator rit2;
	rit2 = B.storage.rbegin();

	if (storage.size() < B.storage.size())
	{
		return true;
	}
	else if (storage.size() > B.storage.size())
	{
		return false;
	}
	else
	{
		while (rit2 != B.storage.rend() && rit1 != storage.rend())
		{
			if (*rit1 == *rit2)
			{
				rit1++;
				rit2++;
			}
			else if (*rit1 < *rit2)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
	}
	return false;
}

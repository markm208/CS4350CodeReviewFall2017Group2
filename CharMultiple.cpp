// CharMultiple.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
using namespace std;

bool multiply(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len);
int sizeOfInt(int number);
bool numberToArray(char numArray[], int number, int arrLength, int decPoint, bool isPositive);
int stripNegative(int num);

int main()
{
	char *numArray = new char[100];

	int c1 = 2;
	int n1 = 5;
	int d1 = 10;

	int c2 = 8;
	int n2 = 42;
	int d2 = 100;

	int len = 100;

	multiply(c1, n1, d1, c2, n2, d2, numArray, len);

	for (int i = 0; numArray[i] != '\0'; i++)
	{
		cout << numArray[i] << " ";
	}

	cout << endl;

	system("pause");
}
//----
bool multiply(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len)
{
	bool retVal = false;
	//check to see if number will be positive or not
	bool isPositive = true;
	if (c1 < 0 && c2 > 0 || c1 > 0 && c2 < 0)
	{
		isPositive = false;
	}

	//check if zeros to avoid doing more work than needed
	if (c1 && n1 == 0 || c2 && n2 == 0)
	{
		result[0] = 0 + '0';
		result[1] = '\0';
		retVal = true;
		return retVal;
	}

	//strip the negative off the number
	c1 = stripNegative(c1);
	c2 = stripNegative(c2);

	//multiply by decimal then add mantissa
	//this allows you to add the numbers together 
	c1 = c1 * d1;
	c1 = c1 + n1;
	c2 = c2 * d2;
	c2 = c2 + n2;

	//multiply with no floating points
	int product = c1 * c2;

	//get where the decimal point is supposed to be placed 
	int decimalLength = (sizeOfInt(d1) - 1) + (sizeOfInt(d2) - 1);

	bool retVal = numberToArray(result, product, decimalLength, len, isPositive);

	return retVal;
}
//----
bool numberToArray(char numArray[], int number, int decPoint, int arrLength, bool isPositive)
{
	bool retVal = true;
	// if the num is + then the loop should end at array index 0 if not end at 1 
	int loopEnd = 0;

	//size of the number with decimal
	int sizeOfNum = sizeOfInt(number);

	// add a - if the number is negative
	//make the loop start 1 spot farther and stop one sooner 
	if (!isPositive)
	{
		numArray[0] = '-';
		sizeOfNum++;
		loopEnd = 1;
	}

	//check to see if number fits in bounds of array +1 for \0
	if (sizeOfNum + 1 > arrLength)
	{
		retVal = false;
		return retVal;
	}

	//add the ending to the array
	numArray[sizeOfNum + 1] = '\0';

	int count = 0;
	for (int i = sizeOfNum; i >= loopEnd; i--)
	{
		if (count == decPoint)
		{
			numArray[i] = '.';
		}
		else
		{
			numArray[i] = (number % 10) + '0';
			number /= 10;
		}
		count++;
	}
	return retVal;
}
//----
int sizeOfInt(int number)
{
	// takes an int and returns how many digits are in the int
	int count = 0;
	while (number != 0)
	{
		count++;
		number /= 10;
	}
	return count;
}
//----
int stripNegative(int num)
{
	if (num < 0)
	{
		num *= (-1);
	}
	return num;
}
//----


#pragma once
#include <iostream>

using namespace std;


bool characteristic(char numString[], int& c);

//count chars 
int charsBeforeDecimal(char numString[]);

//convert chars into int and store it in c, which is passed by reference
void convertToInt(char numString[], int numOfChar, int& c);

bool characteristic(char numString[], int& c)
{
	//return value
	bool retVal = false;

	//is the array that was passed in valid
	if (numString != 0)
	{
		//int that holds retVal of charsBeforeDecimal
		int numOfChar = charsBeforeDecimal(numString);

		//convert from char to int value
		convertToInt(numString, numOfChar, c);
		
		//print the number out
		cout << "Final number: " << c << endl;

		//return true
		retVal = true;
	}

	return retVal;
}

int charsBeforeDecimal(char numString[])
{
	//this will help count the characters before decimal point
	int counter = 0;

	//checking if the array is valid
	for (int i = 0; i < numString[i] != '/0'; i++)
	{
		//if it reaches the decimal point, break
		if (numString[i] == '.')
		{
			//reached .
			break;
		}

		else if (numString[i] == '-' || numString[i] == '+')
		{
			counter++;
		}

		//if it is ' ' ... '\'
		else if (numString[i] >= 32 && numString[i] <= 47)
		{
			//invalid string
			counter = 0;
			break;
		}

		//if it is ':' ... [DEL]
		else if (numString[i] >= 58 && numString[i] <= 127)
		{
			//invalid string
			counter = 0;
			break;
		}

		//it's a number
		else
		{
			counter++;
		}
	}

	//return num of chars before .
	return counter;
}

void convertToInt(char numString[], int numOfChar, int& c)
{
	//This is how I decided to convert chars into one int
	//'1', '2', '3', '4' = 1*10^3 + 2*10^2 + 3*10^1 + 4*10^0

	//When looping through numbers before decimal,
	//will start at 0 if there are no signs if there are
	//no signs before the number
	int i = 0;

	//Boolean variable used to check if there is
	//a sign before the number, if so multiply by -1
	bool isThereANegativeSign = false;
	bool isThereAPositiveSign = false;
	//Used this number for 10^num
	numOfChar -= 1;

	//is there a negative sign before the number
	if (numString[0] == '-')
	{
		//If there is a sign that means that we 
		//have one less number
		numOfChar -= 1;

		//And that also means that we are going to start at 1
		//ex: -123
		i = 1;

		//This is true now
		isThereANegativeSign = true;
	}

	//is there a positive sign
	else if(numString[0] == '+')
	{
		//If there is a sign that means that we 
		//have one less number
		numOfChar -= 1;

		//And that also means that we are going to start at 1
		//ex: +123
		i = 1;

		isThereAPositiveSign = true;
	}

	//starting value
	int pow = 1;

	//Multiply pow by 10 for how many numbers there are
	//before the decimal
	for (int j = 0; j < numOfChar; j++)
	{
		pow *= 10;
	}

	//all cases for 0-9
	for (i;i < numString[numOfChar]; i++)
	{
		if (numString[i] == '0')
		{
			c += 0 * pow;
		}

		else if (numString[i] == '1')
		{
			c += 1* pow;
		}

		else if (numString[i] == '2')
		{
			c += 2 * pow;
		}

		else if (numString[i] == '3')
		{
			c += 3 * pow;
		}

		else if (numString[i] == '4')
		{
			c += 4 * pow;
		}

		else if (numString[i] == '5')
		{
			c += 5 * pow;
		}

		else if (numString[i] == '6')
		{
			c += 6 * pow;
		}

		else if (numString[i] == '7')
		{
			c += 7 * pow;
		}

		else if (numString[i] == '8')
		{
			c += 8 * pow;
		}

		else if (numString[i] == '9')
		{
			c += 9 * pow;
		}

		pow = pow / 10;
	}

	//if there is - before the number
	//then we multiply our final number with -1
	if (isThereANegativeSign)
	{
		c = c*(-1);
	}

	else if (isThereAPositiveSign)
	{
		c = c*(+1);
	}
}
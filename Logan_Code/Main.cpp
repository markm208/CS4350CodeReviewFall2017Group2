#include <iostream>
#include <string>

using namespace std;

bool divide(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len)
{
	//can we divide?
	bool retval = true;
	//step 1: put numbers into this form:
	//  x1   x2
	//  __ / __
	//  d1   d2
	unsigned int x1 = ((c1 * d1) + n1);
	unsigned int x2 = ((c2 * d2) + n2);
	// this translates to:
	//  x1   d2    top
	//  __ * __ = ______
	//  d1   x2   bottom
	unsigned int top = (x1 * d2);
	unsigned int bottom = (d1 * x2);
	//step 2: now we can divide.
	unsigned int divide = (top / bottom);
	string sDivide = to_string(divide);//***no string
	int remainder = (top % bottom);
	string sRemainder = to_string(remainder);//***no string

	//Step 3: enter the value to the results
	//this helps us know how many chars are in the results
	int resultCounter = 0;
	for (int i = 0; i < sDivide.length(); i++)
	{
		result[i] = sDivide[i];
		resultCounter++;
	}
	if (resultCounter >(len - 1))//***use resultcounter instead of result.size()
	{
		cout << "ERROR - not enough length in results!" << endl;
		retval = false;
	}
	else if (resultCounter == (len - 1))//***use resultcounter instead of result.size()
	{
		result[len] = '/0';
		retval = true;
	}
	else //we have more to fill
	{
		//add decimal
		result[resultCounter] = '.';
		resultCounter++;
		//loop while adding remainder
		int remainderCounter = 0;
		while (resultCounter > (len - 1))
		{
			result[resultCounter] = sRemainder[remainderCounter];
			remainderCounter++;
			resultCounter++;
		}
		result[len] = '/0';//***remainder is broken - 1/2 translates to .1 - do long division
		retval = true;//
	}
	return retval;
}

int main()
{
	int c1 = 10;
	int n1 = 1;
	int d1 = 2;

	int c2 = 5;
	int n2 = 3;
	int d2 = 10;

	char answer[100];
	if (divide(c1, n1, d1, c2, n2, d2, answer, 100))
	{
		//display string with answer
		cout << answer << endl;
	}
	else
	{
		//display error message
		cout << "Error - something went wrong, idiot!" << endl;
	}

	system("pause");
	return 0;
}
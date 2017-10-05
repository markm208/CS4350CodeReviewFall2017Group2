#include <iostream>

using namespace std;

// prototypes and variable names
// reordering of functions
bool mantissa(char numString[], int& numerator, int& denominator);
bool calculateDenominator(int& denominator, int numDenominators);
void calculateNumerator(int& numerator, int denominator, int numeratorIndex, int numDenominators, char numString[]);

int main(int argc, char* argv[])
{
    int n, d;
    char numString[] = "442.5";

    if (mantissa(numString, n, d))
    {
        cout << n << " / " << d << endl;
    }
        
    n = 0;
    d = 0;
    char numString2[] = "   -42.5934";
    if (mantissa(numString2, n, d))
    {
        cout << n << " / " << d << endl;
    }

    n = 0;
    d = 0;

    char numString3[] = "+65.3-  ";
    if (mantissa(numString3, n, d))
    {
        cout << n << " / " << d << endl;
    }
    return 0;
}

bool mantissa(char numString[], int& numerator, int& denominator)
{
    numerator = 0;
    denominator = 1;

    // Iter is the length of the cstr
    int iter = 0;
    char ch = numString[iter];

    // Numerator index is where the mantissa begins (the digits after the decimal)
    int numeratorIndex = 0;
    int numDenominators = 0;

    int numSpaces = 0;
    bool reachedDecimal = false;
    bool reachedSign = false;

    // First, check if all the characters are valid (0-9 or a decimal)
    do
    {
        // If it's outside the range, AND not the decimal, return false
        // substitute magic #'s for 0 and 9
        if ((ch < '0') || (ch > '9'))
        {
            if (ch == '.')
            {
                // Once the decimal is reached, set the number of characters counted equal to the numerator
                numeratorIndex = iter;
                reachedDecimal = true;
            }
            else if (ch == ' ')
            {
                if (reachedDecimal == true)
                {
                    numSpaces++;
                }
            }
            else if ( ((ch == '+') || (ch == '-')) && ((numString[iter - 1] == ' ') || (iter == 0)) && (reachedSign == false) )
            {
                reachedSign = true;
            }
            else
                return false;
        }

        iter++;
        ch = numString[iter];
    }
    while (ch != '\0');

    // The numString of denominators is the total number of characters, minus 1 for the decimal, minus the numerators
    numDenominators = iter - numeratorIndex - 1 - numSpaces;

    // Calculate the significant figures of the decimal by multiplying by 10
    // If there is an overflow, return false
    if (calculateDenominator(denominator, numDenominators) == false)
    {
        return false;
    }

    // Calculate the numerator's value.
    // This is done by taking the precision of the decimal and multiplying each digit by a power of 10.
    calculateNumerator(numerator, denominator, numeratorIndex, numDenominators, numString);

    return true;
}

// overflow error - return false if there is an overflow
bool calculateDenominator(int& denominator, int numDenominators)
{
    for (int i = 0; i < numDenominators; i++)
    {
        denominator *= 10;

        // If the signed int overflows, return false and break
        if (denominator < 0)
        {
            return false;
        }
    }

    return true;
}

void calculateNumerator(int& numerator, int denominator, int numeratorIndex, int numDenominators, char numString[])
{
    // get rid of array
    int denominatorVals;
    int mantissaNumerHelper = denominator / 10;

    // Start at the numString after the decimal, numeratorIndex + 1.
    for (char i = numeratorIndex + 1; i != '\0'; i++)
    {
        denominatorVals = numString[i] - '0'; // - '0'

        numerator += mantissaNumerHelper * denominatorVals;
        mantissaNumerHelper /= 10;
    }
}
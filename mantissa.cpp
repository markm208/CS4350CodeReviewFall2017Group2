#include <iostream>

using namespace std;

bool mantissa(char number[], int& mantissaNumerator, int& mantissaDenominator);
void calculateDenominator(int& mantissaDenominator, int numDenominators);
void calculateNumerator(int& mantissaNumerator, int mantissaDenominator, int numNumerators, int numDenominators, char number[]);

int main(int argc, char* argv[])
{
    int n, d;
    char number[] = "442.005";

    cout << "Validity: " << mantissa(number, n, d) << endl;
    return 0;
}

void calculateDenominator(int& mantissaDenominator, int numDenominators)
{
    for (int i = 0; i < numDenominators; i++)
    {
        mantissaDenominator *= 10;
    }
}

void calculateNumerator(int& mantissaNumerator, int mantissaDenominator, int numNumerators, int numDenominators, char number[])
{
    int denominatorVals[numDenominators];
    int mantissaNumerHelper = mantissaDenominator / 10;

    // Start at the number after the decimal, numNumerators + 1.
    for (int i = numNumerators + 1; i != '\0'; i++)
    {
        denominatorVals[i] = number[i] - 48;

        mantissaNumerator += mantissaNumerHelper * denominatorVals[i];
        mantissaNumerHelper /= 10;
    }
}

bool mantissa(char number[], int& mantissaNumerator, int& mantissaDenominator)
{
    mantissaNumerator = 0;
    mantissaDenominator = 1;

    int iter = 0;
    char ch = number[iter];

    int numNumerators = 0;
    int numDenominators = 0;

    // First, check if all the characters are valid (0-9 or a decimal)
    do
    {
        // If it's outside the range, AND not the decimal, return false
        if ((ch < 48) || (ch > 57))
        {
            if (ch == 46)
            {
                // Once the decimal is reached, set the number of characters counted equal to the numerator
                numNumerators = iter;
            }
            else
                return false;
        }

        iter++;
        ch = number[iter];
    }
    while (ch != '\0');

    // The number of denominators is the total number of characters, less 1 for the decimal, less the numerators
    numDenominators = iter - numNumerators - 1;

    // Calculate the significant figures of the decimal by multiplying by 10
    calculateDenominator(mantissaDenominator, numDenominators);

    // Calculate the numerator's value.
    // This is done by taking the precision of the decimal and multiplying each digit by a power of 10.
    calculateNumerator(mantissaNumerator, mantissaDenominator, numNumerators, numDenominators, number);

    cout << "The mantissa numerator is " << mantissaNumerator << endl;
    cout << "The mantissa denominator is " << mantissaDenominator << endl;

    return true;
}
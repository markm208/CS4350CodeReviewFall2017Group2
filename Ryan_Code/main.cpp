
#include <iostream>

using namespace std;

bool subtract(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len);
bool determineValidity(bool isNegative, int numerator, int len);
void testConditions(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len);
void longDivision(int numerator, int denominator, int current_char, char result[], int len);

int main() {

	const int size = 9;
	char result[size];

	//Yield: Positive characteristic and positive mantissa
	testConditions(60, 3, 112, 59, 2, 1010, result, size);

	//Yield: Negative characteristic and negative mantissa
	testConditions(60, 2, 1010, 61, 3, 112, result, size);

	//Yield: Equal characteristic and equal mantissa
	testConditions(60, 5, 112, 60, 5, 112, result, size);

	//Yield: Positive characteristic and negative mantissa
	testConditions(61, 3, 10, 60, 4, 10, result, size);

	//Yield: Negative characteristic and positive mantissa
	testConditions(60, 3, 112, 5999, 2, 1010, result, size);

	//Yield: Equal characteristic and negative mantissa
	testConditions(60, 3, 112, 60, 4, 112, result, size);

	//Yield: Equal characteristic and positive mantissa
	testConditions(60, 5, 112, 60, 4, 112, result, size);

	return 0;
}

//subtract: use to subtract one number from another given their sets of characteristic(s) and mantissa(s)
//c1 is the first number's characteristic, n1 is the first number's numerator, d1 is the first number's denominator
//the second set of three parameters represents the same three variables for the second number
//result is a character array that can be used after the function is called to retrieve the result of subtraction
//len is the length of result, or how much the array may hold without being overloaded (note that this number must be at least 2 due to the null terminator)
//subtract returns true if the whole characteristic can be returned in result[]. If the remainder is 123.45, but result[] only holds two chars, return false. 
bool subtract(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len) {

	//"Clear" the result array of any previous results
	for (int i = 0; i < len; i++) {
		result[i] = '\0';
	}

	//boolean value returned at the end, changed to false in the event of insufficient space in result[]
	bool validResult = true;

	//normalizing the numerators and denominators means putting them on the same denominator scale via cross multiplication
	int normalized_n1 = n1 * d2;
	int normalized_n2 = n2 * d1;

	int normalized_denominator = d1 * d2;

	//overflow has occurred or one of the numbers is negative -> this is an improper result
	if (normalized_n1 < 0
		|| normalized_n2 < 0
		|| normalized_denominator < 0) {
		validResult = false;
		return validResult;
	}

	//Combine the numerators with the whole numbers. This is done by multiplying the whole numbers by the new denominator
	//risk of overflow in the second statements
	int full_n1 = normalized_n1 + (normalized_denominator * c1);
	int full_n2 = normalized_n2 + (normalized_denominator * c2);

	//the final numerator value relative to the normalized denominator
	int final_numerator = full_n1 - full_n2;

	//keep track of if the result is negative (mostly for printing down the line)
	bool isNegativeResult = false;

	if (final_numerator < 0) {
		isNegativeResult = true;
		final_numerator *= -1;
	}

	//the final characteristic value is evaluated by determining how many parts of the final numerator fit in the normalized denominator
	int final_characteristic = final_numerator / normalized_denominator;
	final_numerator = final_numerator % normalized_denominator;

	validResult = determineValidity(isNegativeResult, final_numerator, len);

	if (validResult) {
		//add the null terminating character
		result[len - 1] = '\0';

		//the current location in the array. If this number is equal to len(gth) - 1, we cannot add any more characters
		unsigned int current_char = 0;

		char* temp_char_array = new char[len];
		int num_characteristic_digits = 0;

		int decimalCounter = 0;
		int minusCounter = 0;

		if (final_numerator > 0) {
			decimalCounter += 2;
		}

		//add the minus sign to the result array if necessary
		if (isNegativeResult) {
			result[current_char++] = '-';
			minusCounter++;
		}

		//Get the characteristic into the new array by "dividing off" each digit
		while (final_characteristic > 10) {
			temp_char_array[num_characteristic_digits++] = char(final_characteristic % 10 + '0');

			final_characteristic /= 10;
		}

		//the final digit, not caught by the loop above
		temp_char_array[num_characteristic_digits++] = char(final_characteristic + '0');

		//is there enough room to display all characters of the characteristic AND additional characters that are included?
		if (num_characteristic_digits >= len 
			|| num_characteristic_digits + minusCounter >= len
			|| num_characteristic_digits + minusCounter + decimalCounter >= len) {
			validResult = false;
		}
		else {
			//move characters from the temporary array to the result array. This is done in reverse, because they were put in in reverse
			for (--num_characteristic_digits; num_characteristic_digits >= 0; num_characteristic_digits--) {
				result[current_char] = temp_char_array[num_characteristic_digits];
				current_char++;
			}

			longDivision(final_numerator, normalized_denominator, current_char, result, len);
		}
	}

	return validResult;
}

//determine if the given data translates to a valid result using checks on the length and what we know about the product
bool determineValidity(bool isNegative, int numerator, int length) {

	bool isValid = true;

	//if you cannot add at least one integer and the null terminating character, do not proceed
	if (length < 2) {
		isValid = false;
	}

	//If our result is negative it must include the '-' character
	//if there isn't enough room for the '-', at least one number, and the null terminator, we know this will be an invalid result
	else if (isNegative && length < 3) {
		isValid = false;
	}

	//if there isn't enough room for the '.', at least one number, and the null terminator, we know this will be an invalid result
	else if (numerator > 0 && length < 4) {
		isValid = false;
	}

	//if there isn't enough room for the '-', '.', at least one number, and the null terminator, we know this will be an invalid result
	else if (isNegative && numerator > 0 && length < 5) {
		isValid = false;
	}

	return isValid;
}

void testConditions(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len) {

	if (subtract(c1, n1, d1, c2, n2, d2, result, len)) {
		cout << "The result of the subtraction is about " << result << endl;
	}
	else {
		cout << "Not enough space was made for the result of the subtraction" << endl;
	}
}

//long division is used to determine how the final fraction translates into decimals
void longDivision(int numerator, int denominator, int current_char, char result[], int len) {
	//when doing the long division below, it is important to store the previous result of the operation
	int previous_result = numerator;

	//the next digit that will go in the char array, rendered using long division
	int next_digit;

	if (previous_result > 0) {
		result[current_char++] = '.';
	}

	bool addZeroes = false;

	//Long Division to determine the decimal representation of the fraction
	for (; current_char < len - 1; previous_result *= 10) {
		//if the numbers have evenly divided
		if (previous_result == 0) {
			result[current_char + 1] = '\0';
			break;
		}

		//if the last result is more than the normalized denominator we can do some operations on it to evaluate the decimal value
		if (previous_result >= denominator) {
			next_digit = 0;
			while (((next_digit + 1) * denominator) < previous_result) {
				next_digit++;
			}
			result[current_char++] = char(next_digit + '0');
			previous_result = previous_result - (next_digit * denominator);
		}
		//add a zero otherwise, to signify that the digit is smaller
		else {
			if (addZeroes) {
				result[current_char++] = '0';
			}
			else {
				addZeroes = true;
			}
		}
	}
}

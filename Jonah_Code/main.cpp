//
//  main.cpp
//  Code Review
//
//  Created by Jonah Larson on 9/25/17.
//  Copyright © 2017 Jonah Larson. All rights reserved.
//

#include <iostream>

using namespace std;

bool add(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len);
int find_temp_denominator(int d1, int d2);
int numDigits(int number);
void calculate_fraction(int n1, int d1, int n2, int d2, int& final_n);
void calculate_fraction_overflow(int&c, int& n, int& d);
int add_character_to_array(int return_number, char result[], int len);
int add_mantissa_to_array(int n, int d, char result[], int len, int index);
char* convert_mantissa_to_char(int return_denominator, int return_numerator, int space);

int main() {
    char returnValue[15] = "";
    if(add(18, 7, 100, -2, 5, 87, returnValue, 15))
    {
        //do some math with c, n, and d
        cout << "Success" << endl;
    }
    else
    {
        //handle the error on input
        
        cout << "Failure" << endl;
    }
}

bool add(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len) {
    
    //denominators cannot be less than or equal to 0
    if(d1 <= 0 || d2 <= 0) {
        return false;
    }
    
    //numerator should be negative if c is negative
    if(c1 < 0 && n1 > 0) {
        n1 = n1 * -1;
    }
    
    if(c2 < 0 && n2 > 0) {
        n2 = n2 * -1;
    }
    
    //numerator should not be negative if c is positive
    if((c1 > 0 && n1 < 0) || (c2 > 0 && n2 < 0)){
        return false;
    }
    
    //return_number is just the two characteristics added together
    int return_number = c1 + c2;
    
    //default to zero
    int return_numerator = 0;
    
    //common base denominator
    int return_denominator = d1 * d2;
    
    //cross multiplication
    calculate_fraction(n1, d1, n2, d2, return_numerator);
    
    //if the numerator is greater than the denominator it can be reduced
    if(return_numerator >= return_denominator) {
        calculate_fraction_overflow(return_number, return_numerator, return_denominator);
    }
    
    //flip the sign if the numerator is false
    if(return_numerator < 0){
        return_number--;
        return_numerator = return_numerator + return_denominator;
    }
    //character is longer than the length of the passed in buffer + 1 (to account for ending \0)
    if(len-1 < numDigits(return_number)){
        return false;
    }
    
    //puts the character into the results buffer
    int index = add_character_to_array(return_number, result, len);
    if(return_numerator != 0){
        result[index] = '.';
        index++;
        
       
        //puts the mantissa into the results buffer
        index = add_mantissa_to_array(return_numerator, return_denominator, result, len, index);
    }
    cout << result << endl;
    return true;
}

int find_temp_denominator(int d1, int d2) {
    
    //if the first denominator is equal to or larger than the other denominator, that should be the temp denominator
    if(d1 == d2 || d1 > d2) {
        return d2;
    } else {
        return d1;
    }
}


void calculate_fraction(int n1, int d1, int n2, int d2, int& final_n){
    // Using cross multiplication to get a common base unit for both fractions
    final_n = ((n1 * d2) + (n2 * d1));
    
}

void calculate_fraction_overflow(int&c, int& n, int& d){
    //add the number of times the numerator is greater than the denominator (should be 0 if n < d)
    c += n / d;
    //reduce the numerator to less than 1 denominator
    n = n % d;
}

int numDigits(int number) {
    int digits = 0;
    //if the number is 0 then we have one digit
    if(number == 0){
        digits = 1;
    }else {
        //increase digits by 1 for less than zero to account for - symbol
        if (number < 0) {
            digits = 1;
        }
        while (number) {
            number /= 10;
            digits++;
        }
    }
    return digits;
}

int add_character_to_array(int return_number, char result[], int len){
    int index = 0;
    if(return_number < 0){
        result[0] = '-';
        return_number = return_number * -1;
        index++;
    }
    
    char temp_array[len];
    int temp_index = 0;
    while(return_number > 10){
        int temp = return_number % 10;
        temp_array[temp_index] = 48 + temp;
        return_number = return_number / 10;
        
        temp_index++;
    }
    
    result[index] = 48 + return_number;
    index++;
    for(int i = 0; i < temp_index; i++) {
        result[index] = temp_array[i];
        index++;
    }
    return index;
}

int add_mantissa_to_array(int n, int d, char result[], int len, int index){
    
    //how much space is left
    int space = len - index;
    
    //calculates the decimal
    char* decimal = convert_mantissa_to_char(n, d, space);
    
    //unsigned is an attempt to avoid overflow (not perfect)
    unsigned int offset = 1;
    for(int i = 0; i < space; i++){
        offset = offset * 10;
    }
    

    for(int temp_index = 0; temp_index < space; temp_index++){
        result[index] = decimal[temp_index];
        index++;
    }
    return index;
}


char* convert_mantissa_to_char(int return_denominator, int return_numerator, int space) {
    char * decimal_nums = (char*)malloc(space);
    for(int i = 0; i < space; i++){
        if(return_numerator != 0){
            int temp = (return_numerator* 10) / return_denominator;
            decimal_nums[i] = temp + '0';
            return_numerator  = (return_numerator* 10) % return_denominator;
        }
    }
    return decimal_nums;
}

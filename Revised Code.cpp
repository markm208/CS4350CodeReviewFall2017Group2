#include <iostream>

using namespace std;

bool divide(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len)

int main()
{
    char answer[100];
    int c1, n1, d1;
    int c2, n2, d2;

    if(divide(c1, n1, d1, c2, n2, d2, answer, 100))
    {
        for(int i=0; i<answer.size();i++)
        {
            cout << answer[i];
            if(answer[i] == '/0')
            {
                break;
            }
        }
    }
    else
    {
        cout << "something went wrong!";
    }

}
 //return false if cstring > len
bool divide(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len)
{
   
    bool retVal = true;

    //convert from mixed number to fraction 
    int x = (c1 * d1) + n1;
    int y = (c2 * d2) + n2;

    //cross multiply x/d1 * d2/y to get result in a fraction
    int numerator = x * d2;
    int denominator = d1 * y;

    //divide to get answer
    int wholeNum = numerator/denominator;
    int remains = numerator%denominator;

    //convert to strings
    string wholeNumber;
    string remainder;
    for(int i=0; i<wholeNum.length();i++)
    {
        wholeNumber[i] = wholeNum[i];

    }
    
    for(int i=0; i<remains.length();i++)
    {
        remainder[i] = remains[i];

    }
   
    //check if array is long enough for the result, if it isn't return false
    if((remainder.length() + wholeNumber.length())>len)
    {
        retVal = false;
    }
    if(retVal == true)
    {
         //fill array
   int counter;
   //Add the whole number before the '.'
   for(int i = 0; i< wholeNumber.length(); i++)
   {
       result[i] = wholeNumber[i];
       counter++;

   }
   //add the decimal 
   result[counter] = '.'; 
   counter++;
   //add the remainder after the '.'
   for(int i = counter; i < remainder.length(); i++)
   {
       result[counter] = remainder[i];
       counter++;
   }
   result[counter] = '\0';


    }
   
    
    

    return retVal;
}
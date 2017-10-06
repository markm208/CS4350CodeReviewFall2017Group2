#include <iostream>
#include "Characteristic.h"

using namespace std;

int main()
{
	int c = 0;

	//char array1[7] = { '1','2' ,'3' ,'.' ,'3', '8','2' };
	//char array2[7] = { '-','2' ,'3' ,'.' ,'3', '8','2' };
	//char array3[7] = { '+','2' ,'3' ,'2' ,'.', '8','2' };
	char array4[7] = { 'A','2' ,'3' ,'2' ,'3', '.','2' };
	//char array5[7] = { '1','2' ,'B' ,'.' ,'3', '8','2' };
	//char array6[7] = { '-','5' ,'3' ,'.' ,'A', '8','2' };

	//123
	//characteristic(array1, c);

	//-23
	//characteristic(array2, c);

	//23
	//characteristic(array3, c);

	//0
	characteristic(array4, c);

	//0
	//characteristic(array5, c);

	//-53
	//characteristic(array6, c);

	system("PAUSE");
	return 0;
}
#include <iostream>
#include "vector.h"
using namespace std;

int main(int argc, char const *argv[])
{
	Vector v1(2);
	Vector v2(3);

	Vector15 v15;
	
	cout << "V1 : " << endl;
	v1.print();

	v1 = v2;

	cout << "V1 mais égalo a V2 : " << endl;
	v1.print();

	v1.adjust_size(7);

	v1.setItem(2, 10);
	cout << v1.getItem(2) << endl;

	v1.print();

	v1.printNbAccess();

	v1[0] = 2;
	v1[1] = 3;

	cout << "v1[1] = " << v1[1] << endl;

	cout << "V1 : " << endl;
	v1.print();

	cout << "Vector15" << endl;
	
	cout << "V15 : " << endl;
	v15.print();

	

	//v15.adjust_size(5);

	return 0;
}

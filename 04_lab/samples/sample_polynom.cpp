#include "polynom.h"
#include <iostream>
using namespace std;

int main() {
	try {
		string example1;
		string example2;
		cout << "=====================" << endl;
		cout << "Enter polynom 1:";
		example1 = "- 1 + x";
		//cin >> example1;
		TPolynom polynom1(example1);
		cout << polynom1 << endl;
		cout << "=====================" << endl;
		cout << "Enter polynom 2:";
		example2 = "x-1";// x ^ 2 + y ^ 2 + z + 10";
		//cin >> example2;
		TPolynom polynom2(example2);
		cout << polynom2 << endl;
		cout << "=====================" << endl;
		cout << "Math Arithmetic:" << endl;
		cout << "+:" << polynom1 + polynom2 << endl;
		cout << "-:" << polynom1 - polynom2 << endl;
		cout << "*:" << polynom1 * polynom2 << endl;
		cout << "=====================" << endl;
		cout << "derivative Polynom 1:";
		cout << "dx:" << polynom1.dx() << "\t";
		cout << "dy:" << polynom1.dy() << "\t";
		cout << "dz:" << polynom1.dz() << endl;
		cout << "=====================" << endl;
		cout << "derivative Polynom 2:";
		cout << "dx:" << polynom2.dx() << "\t";
		cout << "dy:" << polynom2.dy() << "\t";
		cout << "dz:" << polynom2.dz() << endl;
		cout << "polynom1(1, 2, 3):" << polynom1(1, 2, 3) << endl;
		cout << "polynom2(1, 2, 3):" << polynom2(1, 2, 3) << endl;
	}

	catch (char* exp) {
		cout << exp << endl;
	}
	return 0;
}
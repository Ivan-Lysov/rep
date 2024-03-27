#ifndef _POLYNOM_H
#define _POLYNOM_H
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include "monom.h"
#include "stack.h"
#include "arithmetic.h"
#include "THeadRingList.h"
using namespace std;

class TPolynom {
private:
	string name;
	TList<TMonom>* monoms; 

	void ParseMonoms();
    void conversion();
	void sort_monoms();
public:
	TPolynom();
	TPolynom(const string& _name);
	TPolynom(const TList<TMonom>* m);
	TPolynom(const TPolynom& p);
	~TPolynom();
	TPolynom operator +(const TPolynom& p);
	TPolynom operator -(const TPolynom& p);
	TPolynom operator *(const TPolynom& p);
	const TPolynom& operator =(const TPolynom& p);
	double operator ()(double x, double y, double z);
	TPolynom dx() const;
	TPolynom dy() const;
	TPolynom dz() const;
	bool operator==(const TPolynom&p) const;
	bool operator!=(const TPolynom& p) const;
	friend ostream& operator<<(ostream& out, const TPolynom& p);
};

#endif 
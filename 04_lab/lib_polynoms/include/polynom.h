#ifndef _POLYNOM_H
#define _POLYNOM_H
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include "monom.h"
#include <algorithm>
#include "stack.h"
#include "arithmetic.h"
#include "THeadRingList.h"
using namespace std;

class TPolynom {
private:
	string name;
	THeadRingList<TMonom>* monoms;

	void ParseMonoms();
public:
	TPolynom();
	TPolynom(const string& _name);
	TPolynom(const THeadRingList<TMonom>* monom);
	TPolynom(const TPolynom& polynom);
	~TPolynom();
	TPolynom operator +(const TPolynom& polynom);
	TPolynom operator -(const TPolynom& polynom);
	TPolynom operator *(const TPolynom& polynom);
	const TPolynom& operator =(const TPolynom& polynom);
	double operator ()(double x, double y, double z);
	TPolynom dx() const;
	TPolynom dy() const;
	TPolynom dz() const;
	bool operator==(const TPolynom& polynom) const;
	bool operator!=(const TPolynom& polynom) const;
	friend ostream& operator<<(ostream& out, const TPolynom& p);
	TPolynom operator-() const;
};

#endif 
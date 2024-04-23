#ifndef _POLYNOM_H
#define _POLYNOM_H
#include <string>
#include <algorithm>
#include "monom.h"
#include "arithmetic.h"
#include "THeadRingList.h"
using namespace std;

class TPolynom {
private:
	string name;
	THeadRingList<TMonom>* monoms;

	void ParseMonoms(const string& _name);
	
	void delNULL();
	
public:
	TPolynom();
	TPolynom(const string& _name);
	TPolynom(const THeadRingList<TMonom>* list);
	TPolynom(const TPolynom& polynom);
	~TPolynom();

	TPolynom operator+(const TPolynom& p);
	TPolynom operator -(const TPolynom& polynom);
	TPolynom operator-() const;
	TPolynom operator *(const TPolynom& polynom);
	const TPolynom& operator =(const TPolynom& polynom);

	void CombineSimilarMonoms();
	TPolynom dx() const;
	TPolynom dy() const;
	TPolynom dz() const;	

	double operator()(double x, double y, double z) const;//написать

	string ToString()const;
	bool operator==(const TPolynom&polynom) const;
	bool operator!=(const TPolynom& polynom) const;

	friend ostream& operator<<(ostream& out, const TPolynom& polynom);
};

#endif 
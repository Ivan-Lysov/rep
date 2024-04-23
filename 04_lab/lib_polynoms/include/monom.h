#ifndef _MONOM_H
#define _MONOM_H
#include <iostream>
//#include "list.h"
using namespace std;

class TMonom  {
 public:
	double coeff; // private
	int degree; // private

	TMonom();
	TMonom(const TMonom& monom);
	TMonom(double _coeff, int _degree);
	TMonom& operator=(const TMonom& monom);
	bool operator ==(const TMonom& data)const;
	bool operator !=(const TMonom& data)const;
	bool operator <(const TMonom& data)const;
	bool operator <=(const TMonom& data)const;
	TMonom operator*(const TMonom& monom)const;
	TMonom operator+(const TMonom& monom)const;
};
#endif 
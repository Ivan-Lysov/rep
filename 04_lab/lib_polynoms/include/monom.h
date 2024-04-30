#ifndef _MONOM_H
#define _MONOM_H
#include <iostream>
//#include "list.h"
using namespace std;

class TMonom  {
 public:
	double coeff; // private добавить в private
	int degree; // private добавить в private

	TMonom();
	TMonom(double _coeff, int _degree);
	bool operator ==(const TMonom& data)const;
	bool operator !=(const TMonom& data)const;
	bool operator <(const TMonom& data)const;
	bool operator <=(const TMonom& data)const;
	TMonom operator*(const TMonom& monom)const;
	TMonom operator+(const TMonom& monom)const;
};
#endif 
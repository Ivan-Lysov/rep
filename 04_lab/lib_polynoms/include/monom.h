#ifndef _MONOM_H
#define _MONOM_H
#include <iostream>
//#include "list.h"
using namespace std;

class TMonom  {
 public:
	int degree;
	double coeff;

	TMonom();
	TMonom(double _coeff, int _degree);
	bool operator ==(const TMonom& data)const;
	bool operator !=(const TMonom& data)const;
	bool operator <(const TMonom& data)const;
	bool operator <=(const TMonom& data)const;
	TMonom operator*(const TMonom& monom)const;
	TMonom operator+(const TMonom& monom)const;

	int get_x_deg() const;
	int get_y_deg() const;
	int get_z_deg() const;
};
#endif 
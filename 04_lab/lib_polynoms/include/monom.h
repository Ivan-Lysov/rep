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
	double monom(double x, double y, double z) const {
		return coeff * pow(x, get_x_deg()) * pow(y, get_y_deg()) * pow(z, get_z_deg());
	}
	int get_x_deg() const;
	int get_y_deg() const;
	int get_z_deg() const;
};
#endif 
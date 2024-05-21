#include "monom.h"
#include <stdexcept>
	
TMonom::TMonom() : coeff(0.0), degree(-1) {};

TMonom::TMonom(double _coeff,  int _degree){
	if (_degree < 0 || _degree > 999) {
        throw std::exception("Degree must be from 0 to 999");
    }
	coeff = _coeff;
	degree = _degree;
}

bool TMonom::operator==(const TMonom& data) const {
	return (degree == data.degree);
}

bool TMonom::operator<(const TMonom& data) const {
	return (degree < data.degree);
}

bool TMonom::operator<=(const TMonom& data) const {
	return (degree <= data.degree);
}

bool TMonom::operator!=(const TMonom& data) const {
	return !(*this == data);
}

TMonom TMonom::operator*(const TMonom& monom) const {
	if ((degree + monom.degree) <= 999 && (degree + monom.degree) >= 0) {
		return TMonom(coeff * monom.coeff, degree + monom.degree);
	}
	else {
		throw std::exception("The degree must be between 0 and 999.");
	}
}

TMonom TMonom::operator+(const TMonom& monom) const {
	return TMonom(coeff + monom.coeff, degree);	
}

int TMonom::get_x_deg() const {
    return degree / 100;
}
int TMonom::get_y_deg() const {
    return (degree % 100) / 10;
}
int TMonom::get_z_deg() const {
    return degree % 10;
}


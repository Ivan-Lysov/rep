#include "monom.h"
	
TMonom::TMonom() : coeff(0.0), degree(-1) {};//�� ���������

TMonom::TMonom(const TMonom& monom) {
	if (&monom != nullptr) {
		coeff = monom.coeff;
		degree = monom.degree;
	}
	else {
		// ��������� ������, ����� monom �������� nullptr
		coeff = 0.0;
		degree = -1;
	}
}

TMonom::TMonom(double _coeff,  int _degree){
	if (_degree < 0 || _degree > 999) {throw ("Degree must be from 0 to 999");}
	coeff = _coeff;
	degree = _degree;
}

bool TMonom::operator==(const TMonom& data) const {
	// ���������, ��� ������ data �� �������� nullptr
	if (this == nullptr || &data == nullptr) {
		// ������ this ��� ������ data �������� nullptr, ���������� false
		return false;
	}

	// ���������� ������� �������
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
		throw ("The degree must be between 0 and 999.");
	}
}

TMonom& TMonom::operator=(const TMonom& monom) {
	if (this != &monom) { // �������� �� ����������������
		coeff = monom.coeff;
		degree = monom.degree;
	}
	return *this;
}

TMonom TMonom::operator+(const TMonom& monom) const {
	return TMonom(coeff + monom.coeff, degree);	
}

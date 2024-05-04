#include "polynom.h"
//#include "stack.h"
//#include "arithmetic.h"
#include <sstream>

TPolynom::TPolynom() {
	name = "0";
    monoms.insert_first(TMonom(0, 0));
}

TPolynom::TPolynom(const string& _name) {
	name = _name;
	ParseMonoms(_name);
    CombineSimilarMonoms();
}

TPolynom::TPolynom(const THeadRingList<TMonom>& list) {
	if (!list.IsEmpty()) {
		monoms = list;
		delNULL();
		CombineSimilarMonoms();
		monoms.Sort();
	}
	else {
		monoms.insert_first(TMonom(0, 0));
	}
}

string TPolynom::ToString() const {
	ostringstream stream;
    stream << *this;
    return stream.str();
}

void TPolynom::ParseMonoms(const string& _name) {
    istringstream stream(_name);

    int sign = 1;
    while (!stream.eof()) {
        TMonom tmp(0, 0);

        if (stream.peek() == '-') {
            sign = -1;
            stream.ignore(); // пропускаем минус
        }

        if (!(stream >> tmp.coeff)) {
            tmp.coeff = 1.0;
            stream.clear(); // снимает состояние ошибки
        }

        tmp.coeff *= sign;

        char c;
        while (stream >> c) {
            if (c == ' ' || c == '*') {
                continue;
            }
            if (c == '+' || c == '-') {
                sign = (c == '-') ? -1 : 1;
                break;
            }

            int degree_component;
            if (stream.peek() == '^') {
                stream.ignore();
                stream >> degree_component;
            } else {
                degree_component = 1;
            }

            const int components = 'z' - 'x';
            int component_index = c - 'x';
            tmp.degree += degree_component * pow(10, (components - component_index));
        }

        if (tmp.coeff != 0) {
            monoms.insert_sort(tmp);
        }
    }

	name = ToString();
}

TPolynom TPolynom::operator+(const TPolynom& polynom_)
{
	THeadRingList<TMonom> list;
	TPolynom cpolynom(polynom_);
	monoms.reset();
	cpolynom.monoms.reset();

	while (!monoms.IsEnded() && !cpolynom.monoms.IsEnded())
	{
		TMonom monom1 = monoms.GetCurrent();
		TMonom monom2 = cpolynom.monoms.GetCurrent();
		if (monom1 == monom2)
		{
			double coef1 = monom1.coeff;
			double coef2 = monom2.coeff;
			double coef_res = coef1 + coef2;
			if (coef_res != 0)
			{
				monom2.coeff = coef_res;
				list.insert_last(monom2);
			}
			monoms.next();
            cpolynom.monoms.next();
		}
		else if (monom2 < monom1)
		{
			list.insert_last(monom2);
            cpolynom.monoms.next();
		}
		else
		{
			list.insert_last(monom1);
			monoms.next();
		}
	}
	while (!monoms.IsEnded())
	{
		list.insert_last(monoms.GetCurrent());
		monoms.next();
	}
	while (!cpolynom.monoms.IsEnded())
	{
		list.insert_last(cpolynom.monoms.GetCurrent());
        cpolynom.monoms.next();
	}

	TPolynom result;
	result.monoms = list;
	result.name = result.ToString();
	return result;
}


TPolynom TPolynom::operator-(const TPolynom& polynom) {
	return (*this) + (-polynom);
}

TPolynom TPolynom::operator-() const {
	TPolynom result(*this);
	result.monoms.reset();
	while (!result.monoms.IsEnded()) {
		result.monoms.GetCurrent().coeff *= -1;
		result.monoms.next();
	}
	return result;
}

TPolynom TPolynom::operator*(const TPolynom& polynom_)
{
    TPolynom cpolynom(polynom_);
	THeadRingList<TMonom> list;
	monoms.reset();
    cpolynom.monoms.reset();
	while (!monoms.IsEnded())
	{
		TMonom m = monoms.GetCurrent();
        cpolynom.monoms.reset();
		while (!cpolynom.monoms.IsEnded())
		{
			TMonom m2 = cpolynom.monoms.GetCurrent();
			double k = m.coeff;
			double k2 = m2.coeff;
			double k3 = k * k2; // == 0 
			int d = m.degree;
			int d2 = m2.degree;
			int deg = d + d2; // > 999 можно типо выйти за границы
			TMonom mon(k3, deg);
			list.insert_last(mon);
            cpolynom.monoms.next();
		}
		monoms.next();
	}
	TPolynom result;
	result.monoms = list;
	result.name = result.ToString();
	return result;
}

TPolynom TPolynom::dx() const {
    TPolynom cp = *this;
	TPolynom result;
    cp.monoms.reset();
	while (!cp.monoms.IsEnded()) {
		TMonom& monom = cp.monoms.GetCurrent();
		if (monom.degree >= 100) {
			int new_degree = monom.degree - 100;
			double new_coeff = monom.coeff * (monom.degree / 100);
			TMonom new_monom(new_coeff, new_degree);
			result.monoms.insert_last(new_monom);
		}
        cp.monoms.next();
	}
	return result;
}

TPolynom TPolynom::dy() const {
    TPolynom cp = *this;
	TPolynom result;
    cp.monoms.reset();
	while (!cp.monoms.IsEnded()) {
		TMonom& monom = cp.monoms.GetCurrent();
		int deg = cp.monoms.GetCurrent().degree;
		int y = (deg % 100) / 10;
		if (y >= 1) {
			int new_degree = monom.degree - 10;
			double new_coeff = monom.coeff * (monom.degree / 10.);
			monom.degree = new_degree;
			monom.coeff = new_coeff;
			result.monoms.insert_last(monom);
		}
        cp.monoms.next();
	}
	return result;
}

TPolynom TPolynom::dz() const {
    TPolynom cp = *this;
	TPolynom result;
    cp.monoms.reset();
	while (!cp.monoms.IsEnded()) {
		TMonom& monom = cp.monoms.GetCurrent();
		int deg = cp.monoms.GetCurrent().degree;
		int z = deg % 10;
		if (z >= 1) {
			int new_degree = monom.degree - 1;
			double new_coeff = monom.coeff * monom.degree;
			monom.degree = new_degree;
			monom.coeff = new_coeff;
			result.monoms.insert_sort(monom);
		}
        cp.monoms.next();
	}
	return result;
}

bool TPolynom::operator==(const TPolynom& polynom) const {
    TPolynom cp = *this;
    TPolynom cp_other = polynom;

    cp.monoms.reset();
    cp_other.monoms.reset();
	while (!cp.monoms.IsEnded() && !cp_other.monoms.IsEnded()) {
		if (cp.monoms.GetCurrent() != cp_other.monoms.GetCurrent()) {
			return false;
		}
        cp.monoms.next();
        cp_other.monoms.next();
	}
	return (cp.monoms.IsEnded() && cp_other.monoms.IsEnded());
}

bool TPolynom::operator!=(const TPolynom& polynom) const {
	return !(*this == polynom);
}

ostream& operator<<(ostream& out, const TPolynom& polynom) {
    if (polynom.monoms.IsEmpty()) {
        out << "0";
        return out;
    }

    THeadRingList<TMonom> sortedMonoms(polynom.monoms);
    sortedMonoms.Sort();

    bool firstTerm = true;
    sortedMonoms.reset();

    if (sortedMonoms.GetCurrent().coeff == 0 && sortedMonoms.GetCurrent().degree == 0) {
        out << "0";
        return out;
    }

    while (!sortedMonoms.IsEnded()) {
        const TMonom& monom = sortedMonoms.GetCurrent();
        double coeff = monom.coeff;
        if (coeff != 0) {
            if (!firstTerm) {
                out << ((coeff > 0) ? "+" : "-");
            }
            else {
                if (coeff < 0) {
                    out << "-";
                }
                firstTerm = false;
            }
            if (abs(coeff) != 1 || monom.degree == 0) {
                out << (abs(coeff) == 1 ? ((coeff > 0) ? "" : "1") : std::to_string(abs(coeff)));
            }

            if (monom.degree != 0) {
                const int x = monom.get_x_deg();
                if (x != 0) out << "x" + ((x != 1) ? "^" + std::to_string(x) : "");
                //
                const int y = monom.get_y_deg();
                if (y != 0) out << "y" + ((y != 1) ? "^" + std::to_string(y) : "");
                //
                const int z = monom.get_z_deg();
                if (z != 0) out << "z" + ((z != 1) ? "^" + std::to_string(z) : "");
            }
        }
        sortedMonoms.next();
    }

	return out;
}

void TPolynom::delNULL() {
	monoms.reset(); 
	while (!monoms.IsEnded()) {
		if (monoms.GetCurrent().coeff == 0.0) {
			monoms.remove(monoms.GetCurrent());
		}
		else {
			monoms.next();
		}
	}
}

void TPolynom::CombineSimilarMonoms() {
	if (monoms.IsEmpty()) {
		return;
	}

	THeadRingList<TMonom> combinedMonoms;
	monoms.reset();
	double coeffSum = 0.0;
	int currentDegree = monoms.GetCurrent().degree;

	while (!monoms.IsEnded()) {
		if (monoms.GetCurrent().degree == currentDegree) {
			coeffSum += monoms.GetCurrent().coeff;
		}
		else {
			if (coeffSum != 0.0) {
				TMonom combinedTerm(coeffSum, currentDegree);
                combinedMonoms.insert_last(combinedTerm);
				coeffSum = 0.0;
			}
			currentDegree = monoms.GetCurrent().degree;
			coeffSum = monoms.GetCurrent().coeff;
		}
		monoms.next();
	}

	if (coeffSum != 0.0) {
		TMonom combinedTerm(coeffSum, currentDegree);
        combinedMonoms.insert_last(combinedTerm);
	}

    monoms = combinedMonoms;
}


double TPolynom::operator()(double x, double y, double z) const {
    TPolynom cp = *this;

	double result = 0.0;

    cp.monoms.reset();
    while (!cp.monoms.IsEnded()) {
        const TMonom& monom = cp.monoms.GetCurrent();
        double monomValue = monom.coeff;

        int deg = monom.degree;
        int xExp = deg / 100;
        int yExp = (deg % 100) / 10;
        int zExp = deg % 10;

        monomValue *= pow(x, xExp) * pow(y, yExp) * pow(z, zExp);

        result += monomValue;

        cp.monoms.next();
    }

    return result;
}
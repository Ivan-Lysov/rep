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
//	// Удаляем нулевые мономы
//	delNULL();
//	// Объединяем одинаковые мономы
//	CombineSimilarMonoms();
//	// Упорядочиваем список
//	monoms.Sort();
//}

string TPolynom::ToString() const {//может как-либо разбить метод на более мелкие функции чтобы этот метод был короче
	string str;
	if (monoms.IsEmpty()) {
		return "0"; 
	}

	THeadRingList<TMonom> sortedMonoms(monoms);
	sortedMonoms.Sort();

	bool firstTerm = true;
	sortedMonoms.reset();
	while (!sortedMonoms.IsEnded()) {
		int deg = sortedMonoms.GetCurrent().degree;
		double coeff = sortedMonoms.GetCurrent().coeff;
		int x = deg / 100;
		int y = (deg % 100) / 10;
		int z = deg % 10;
		if (coeff != 0) {
			if (!firstTerm) {
				str += ((coeff > 0) ? "+" : "-");
			}
			else {
				if (coeff < 0) {
					str += "-";
				}
				firstTerm = false;
			}
			if (abs(coeff) != 1 || deg == 0) {
				// Используем спецификатор формата "%.2f" для вывода с двумя знаками после запятой
				str += (abs(coeff) == 1 ? ((coeff > 0) ? "" : "1") : std::to_string(abs(coeff)));
			}
			if (x != 0) str += "x" + ((x != 1) ? "^" + std::to_string(x) : "");
			if (y != 0) str += "y" + ((y != 1) ? "^" + std::to_string(y) : "");
			if (z != 0) str += "z" + ((z != 1) ? "^" + std::to_string(z) : "");
		}
		sortedMonoms.next();
	}
	return str.empty() ? "0" : str; // Возвращаем "0", если строка пуста
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

//Старая реализация +
//TPolynom TPolynom::operator+(const TPolynom& polynom) {
//	TPolynom result(*this);
//	polynom.monoms.reset();
//	while (!polynom.monoms.IsEnded()) { // TODO: rewrite
//		TMonom current = polynom.monoms.GetCurrent();
//		result.monoms.insert_sort(current);
//		polynom.monoms.next();
//	}
//	return result;
//}

TPolynom TPolynom::operator+(const TPolynom& polynom)
{
	THeadRingList<TMonom> list;
	monoms.reset();
	polynom.monoms.reset();

	while (!monoms.IsEnded() && !polynom.monoms.IsEnded())
	{
		TMonom monom1 = monoms.GetCurrent();
		TMonom monom2 = polynom.monoms.GetCurrent();
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
			polynom.monoms.next();
		}
		else if (monom2 < monom1)
		{
			list.insert_last(monom2);
			polynom.monoms.next();
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
	while (!polynom.monoms.IsEnded())
	{
		list.insert_last(polynom.monoms.GetCurrent());
		polynom.monoms.next();
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

TPolynom TPolynom::operator*(const TPolynom& p)
{
	THeadRingList<TMonom> list;
	monoms.reset();
	p.monoms.reset();
	while (!monoms.IsEnded())
	{
		TMonom m = monoms.GetCurrent();
		p.monoms.reset();
		while (!p.monoms.IsEnded())
		{
			TMonom m2 = p.monoms.GetCurrent();
			double k = m.coeff;
			double k2 = m2.coeff;
			double k3 = k * k2; // == 0 
			int d = m.degree;
			int d2 = m2.degree;
			int deg = d + d2; // > 999 можно типо выйти за границы
			TMonom mon(k3, deg);
			list.insert_last(mon);
			p.monoms.next();
		}
		monoms.next();
	}
	//привести подобные
	// sim monoms
	TPolynom result;
	result.monoms = list;
	result.name = result.ToString();
	return result;
}

TPolynom TPolynom::dx() const {
	TPolynom result;
	monoms.reset();
	while (!monoms.IsEnded()) {
		TMonom monom = monoms.GetCurrent();
		if (monom.degree >= 100) {
			int new_degree = monom.degree - 100;
			double new_coeff = monom.coeff * (monom.degree / 100);
			TMonom new_monom(new_coeff, new_degree);
			result.monoms.insert_last(new_monom);
		}
		monoms.next();
	}
	return result;
}

TPolynom TPolynom::dy() const {
	TPolynom result;
	monoms.reset();
	while (!monoms.IsEnded()) {
		TMonom monom = monoms.GetCurrent();
		int deg = monoms.GetCurrent().degree;
		int y = (deg % 100) / 10;
		if (y >= 1) {
			int new_degree = monom.degree - 10;
			double new_coeff = monom.coeff * (monom.degree / 10);
			monom.degree = new_degree;
			monom.coeff = new_coeff;
			result.monoms.insert_last(monom);
		}
		monoms.next();
	}
	return result;
}

TPolynom TPolynom::dz() const {
	TPolynom result;
	monoms.reset();
	while (!monoms.IsEnded()) {
		TMonom monom = monoms.GetCurrent();
		int deg = monoms.GetCurrent().degree;
		int z = deg % 10;
		if (z >= 1) {
			int new_degree = monom.degree - 1;
			double new_coeff = monom.coeff * monom.degree;
			monom.degree = new_degree;
			monom.coeff = new_coeff;
			result.monoms.insert_sort(monom);
		}
		monoms.next();
	}
	return result;
}

bool TPolynom::operator==(const TPolynom& polynom) const {
	monoms.reset();
	polynom.monoms.reset();
	while (!monoms.IsEnded() && !polynom.monoms.IsEnded()) {
		if (monoms.GetCurrent() != polynom.monoms.GetCurrent()) {
			return false;
		}
		monoms.next();
		polynom.monoms.next();
	}
	return (monoms.IsEnded() && polynom.monoms.IsEnded());
}

bool TPolynom::operator!=(const TPolynom& polynom) const {
	return !(*this == polynom);
}

ostream& operator<<(ostream& out, const TPolynom& polynom) {
	cout << polynom.ToString();
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
	double result = 0.0;

    monoms.reset();
    while (!monoms.IsEnded()) {
        TMonom monom = monoms.GetCurrent();
        double monomValue = monom.coeff;

        int deg = monom.degree;
        int xExp = deg / 100;
        int yExp = (deg % 100) / 10;
        int zExp = deg % 10;

        monomValue *= pow(x, xExp) * pow(y, yExp) * pow(z, zExp);

        result += monomValue;

        monoms.next();
    }

    return result;
}
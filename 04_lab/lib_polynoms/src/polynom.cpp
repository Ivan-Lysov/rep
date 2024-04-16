#include "polynom.h"
#include "stack.h"
#include "arithmetic.h"

TPolynom::TPolynom() {
	monoms = new THeadRingList<TMonom>();
	name = "";
}

TPolynom::TPolynom(const string& _name) {
	monoms = new THeadRingList<TMonom>();
	name = _name;
	ParseMonoms();
}

TPolynom::TPolynom(const THeadRingList<TMonom>* list) {
	monoms = new THeadRingList<TMonom>(*list);
	// TODO:
	// 1. zeros
	// 2. sim
	// 3. sort
	// 4. name
}

TPolynom::TPolynom(const TPolynom& polynom) {
	name = polynom.name;
	monoms = new THeadRingList<TMonom>(*(polynom.monoms));
}

TPolynom::~TPolynom() {
	delete monoms;
}


string TPolynom::ToString() const {
	string str;
	if (monoms->IsEmpty()) {
		return "0";
	}

	THeadRingList<TMonom> sortedMonoms(*monoms);
	sortedMonoms.Sort(); 

	bool firstTerm = true;
	sortedMonoms.reset();
	while (!sortedMonoms.IsEnded()) {
		int deg = sortedMonoms.GetCurrent()->data.degree;
		double coeff = sortedMonoms.GetCurrent()->data.coeff;
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
				str += (abs(coeff) == 1 ? ((coeff>0)? "1" : "1"): to_string(abs(coeff))); 
			}
			if (x != 0) str += "x" + ((x != 1) ? "^" + to_string(x) : "");
			if (y != 0) str += "y" + ((y != 1) ? "^" + to_string(y) : "");
			if (z != 0) str += "z" + ((z != 1) ? "^" + to_string(z) : "");
		}
		sortedMonoms.next();
	}
	return str;
}

void TPolynom::ParseMonoms() {
	string str = name;
	while (!str.empty()) {
		int degree = 0;
		size_t j = str.find_first_of("+-", 1);
		string monom = str.substr(0, j);
		str.erase(0, j);

		string coefficient = monom.substr(0, monom.find_first_of("xyz"));
		double coeff = 1.0; 
		if (!coefficient.empty()) {
			coeff = (coefficient == "+" || coefficient == "-") ? stod(coefficient + "1") : stod(coefficient);
		}

		monom.erase(0, monom.find_first_of("xyz"));
		for (size_t i = 0; i < monom.size(); ++i) {
			if (isalpha(monom[i])) {
				int exp = 1;
				if (monom[i + 1] == '^') {
					size_t exp_start = i + 2;
					while (isdigit(monom[exp_start])) {
						exp_start++;
					}
					exp = stoi(monom.substr(i + 2, exp_start - i - 2));
				}
				switch (monom[i]) {
				case 'x':
					degree += exp * 100;
					break;
				case 'y':
					degree += exp * 10;
					break;
				case 'z':
					degree += exp * 1;
					break;
				default:
					throw ("Invalid monom format");
					break;
				}
			}
		}
		TMonom tmp(coeff, degree);
		if (tmp.coeff != 0) {
			monoms->insert_sort(tmp);
		}
	}
}

const TPolynom& TPolynom::operator=(const TPolynom& polynom)  {
	if (this != &polynom) {//проверка на самоприсваивание
		name = polynom.name;
		delete monoms;
		monoms = new THeadRingList<TMonom>(*(polynom.monoms));
	}
	return *this;
}

TPolynom TPolynom::operator+(const TPolynom& polynom) {
	TPolynom result(*this);
	polynom.monoms->reset();
	while (!polynom.monoms->IsEnded()) { // TODO: rewrite
		TMonom current = polynom.monoms->GetCurrent()->data;
		result.monoms->insert_sort(current);
		polynom.monoms->next();
	}
	return result;
}

TPolynom TPolynom::operator-(const TPolynom& polynom) {
	return (*this) + (-polynom);
}

TPolynom TPolynom::operator-() const {
	TPolynom result(*this);
	result.monoms->reset();
	while (!result.monoms->IsEnded()) {
		result.monoms->GetCurrent()->data.coeff *= -1;
		result.monoms->next();
	}
	return result;
}

TPolynom TPolynom::operator*(const TPolynom& polynom) {
	TPolynom result;
	monoms->reset();
	while (!monoms->IsEnded()) {
		polynom.monoms->reset();
		while (!polynom.monoms->IsEnded()) {
			TMonom m1 = monoms->GetCurrent()->data;
			TMonom m2 = polynom.monoms->GetCurrent()->data;
			TMonom m3 = m1 * m2;
			result.monoms->insert_last(m3); // sim, zeros,...
			polynom.monoms->next();
		}
		monoms->next();
	}
	return result;
}

TPolynom TPolynom::dx() const {
	TPolynom result;
	monoms->reset();
	while (!monoms->IsEnded()) {
		TMonom monom = monoms->GetCurrent()->data;
		if (monom.degree >= 100) {
			int new_degree = monom.degree - 100;
			double new_coeff = monom.coeff * (monom.degree / 100);
			TMonom new_monom(new_coeff, new_degree);
			result.monoms->insert_last(new_monom);
		}
		monoms->next();
	}
	return result;
}

TPolynom TPolynom::dy() const {
	TPolynom result;
	monoms->reset();
	while (!monoms->IsEnded()) {
		TMonom monom = monoms->GetCurrent()->data;
		int deg = monoms->GetCurrent()->data.degree;
		int y = (deg % 100) / 10;
		if (y >= 1) {
			int new_degree = monom.degree - 10;
			double new_coeff = monom.coeff * (monom.degree / 10);
			monom.degree = new_degree;
			monom.coeff = new_coeff;
			result.monoms->insert_last(monom);
		}
		monoms->next();
	}
	return result;
}

TPolynom TPolynom::dz() const {
	TPolynom result;
	monoms->reset();
	while (!monoms->IsEnded()) {
		TMonom monom = monoms->GetCurrent()->data;
		int deg = monoms->GetCurrent()->data.degree;
		int z = deg % 10;
		if (z >= 1) {
			int new_degree = monom.degree - 1;
			double new_coeff = monom.coeff * monom.degree;
			monom.degree = new_degree;
			monom.coeff = new_coeff;
			result.monoms->insert_sort(monom);
		}
		monoms->next();
	}
	return result;
}

bool TPolynom::operator==(const TPolynom& polynom) const {
	monoms->reset();
	polynom.monoms->reset();
	while (!monoms->IsEnded() && !polynom.monoms->IsEnded()) {
		if (monoms->GetCurrent()->data != polynom.monoms->GetCurrent()->data) {
			return false;
		}
		monoms->next();
		polynom.monoms->next();
	}
	return (monoms->IsEnded() && polynom.monoms->IsEnded());
}

bool TPolynom::operator!=(const TPolynom& polynom) const {
	return !(*this == polynom);
}

ostream& operator<<(ostream& out, const TPolynom& polynom) {
	cout << polynom.ToString();
	return out;
}

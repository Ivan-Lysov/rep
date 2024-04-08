#include "polynom.h"

TPolynom::TPolynom() {
	monoms = new THeadRingList<TMonom>();
	name = "";
}

TPolynom::TPolynom(const string& _name) {
	monoms = new THeadRingList<TMonom>;
	name = _name;
	ParseMonoms();
}

TPolynom::TPolynom(const THeadRingList<TMonom>* list) {
	monoms = new THeadRingList<TMonom>(*list);
	name = "";
}

TPolynom::TPolynom(const TPolynom& polynom) {
	name = polynom.name;
	if (polynom.monoms != nullptr) {
		monoms = new THeadRingList<TMonom>(*(polynom.monoms));
	}
	else {
		monoms = nullptr;
	}
}

TPolynom::~TPolynom() {
	if (monoms != nullptr) {
		delete monoms;
	}
}

void TPolynom::ParseMonoms() {
	string str = name;
	while (!str.empty()) {
		int degree = 0;
		size_t j = str.find_first_of("+-", 1);
		string monom = str.substr(0, j);
		str.erase(0, j);
		string coefficient = monom.substr(0, monom.find_first_of("xyz"));
		TMonom tmp;
		tmp.coeff = ((coefficient.empty() || coefficient == "+") ? 1 : (coefficient == "-") ? -1 : stod(coefficient));
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
		tmp.degree = degree;
		if (tmp.coeff != 0) {
			monoms->insert_sort(tmp);
		}
	}
}

double TPolynom::operator()(double x,double y,double z) {
	MathArithmetics expression(name);
	vector<double> xyz ={x,y,z};
	expression.ToPostfix();
	expression.SetValues(xyz);
	return (expression.Calculate());
}

const TPolynom& TPolynom::operator=(const TPolynom& polynom) {
	if (this != &polynom) {
		name = polynom.name;
		delete monoms;
		monoms = new THeadRingList<TMonom>(*polynom.monoms);
	}
	return *this;
}


TPolynom TPolynom::operator+(const TPolynom& polynom) {
	TPolynom result(*this);
	polynom.monoms->reset();
	while (!polynom.monoms->IsEnded()) {
		TMonom current = polynom.monoms->GetCurrent()->data;
		result.monoms->insert_sort(current);
		polynom.monoms->next();
	}
	return result;
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

TPolynom TPolynom::operator-(const TPolynom& polynom) {
	return (*this) + (-polynom);
}

TPolynom TPolynom::operator*(const TPolynom& p) {
	TPolynom result;
	monoms->reset();
	while (!monoms->IsEnded()) {
		p.monoms->reset();
		while (!p.monoms->IsEnded()) {
			TMonom m1 = monoms->GetCurrent()->data;
			TMonom m2 = p.monoms->GetCurrent()->data;
			TMonom m3 = m1 * m2;
			result.monoms->insert_sort(m3);
			p.monoms->next();
		}
		monoms->next();
	}
	return result;
}

TPolynom TPolynom::dx() const {//Спросить как лучше сделать как dx или dy
	TPolynom result;
	monoms->reset();
	while (!monoms->IsEnded()) {
		TMonom monom = monoms->GetCurrent()->data;
		if (monom.degree >= 100) {
			int new_degree = monom.degree - 100;
			double new_coeff = monom.coeff * (monom.degree / 100);
			TMonom new_monom(new_coeff, new_degree);
			result.monoms->insert_sort(new_monom);
		}
		monoms->next();
	}
	return result;
}


TPolynom TPolynom::dy() const {//Спросить как лучше сделать как dx или dy
	TPolynom result;
	THeadRingList<TMonom>* list = new THeadRingList<TMonom>();
	monoms->reset();

	while (!monoms->IsEnded()) {
		TMonom monom = monoms->GetCurrent()->data;
		int y = (monom.degree % 100) / 10;

		if (y >= 1) {
			double new_coeff = monom.coeff * y;
			int new_degree = monom.degree - 10;
			TMonom new_monom(new_coeff, new_degree);
			list->insert_sort(new_monom);
		}

		monoms->next();
	}

	result.monoms = list;
	return result;
}

TPolynom TPolynom::dz() const {//Спросить как лучше сделать как dx или dy
	TPolynom result;
	THeadRingList<TMonom>* list = new THeadRingList<TMonom>();
	monoms->reset();

	while (!monoms->IsEnded()) {
		TMonom monom = monoms->GetCurrent()->data;
		int z = monom.degree % 10;

		if (z >= 1) {
			double new_coeff = monom.coeff * z;
			int new_degree = monom.degree - 1;
			TMonom new_monom(new_coeff, new_degree);
			list->insert_sort(new_monom);
		}

		monoms->next();
	}

	result.monoms = list;
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
	THeadRingList<TMonom>* monoms = polynom.monoms;
	bool firstTerm = true;
	monoms->reset();
	while (!monoms->IsEnded()) {
		int deg = monoms->GetCurrent()->data.degree;
		int coeff = monoms->GetCurrent()->data.coeff;
		int x = deg / 100;
		int y = (deg % 100) / 10;
		int z = deg % 10;
		if (coeff != 0) {
			if (!firstTerm) {
				out << ((coeff > 0) ? " + " : " - ");
			}
			else {
				firstTerm = false;
			}
			if (abs(coeff) != 1 || deg == 0) {
				out << abs(coeff);
			}
			if (x != 0) out << "x" << ((x != 1) ? "^" + to_string(x) : "");
			if (y != 0) out << "y" << ((y != 1) ? "^" + to_string(y) : "");
			if (z != 0) out << "z" << ((z != 1) ? "^" + to_string(z) : "");
		}
		monoms->next();
	}
	if (firstTerm) out << "0";
	return out;
}
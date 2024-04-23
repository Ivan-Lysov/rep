#include "polynom.h"
//#include "stack.h"
//#include "arithmetic.h"

TPolynom::TPolynom() {
	monoms = new THeadRingList<TMonom>();
	name = "0";
	if (monoms->IsEmpty()) {
		// Вставляем нулевой моном
		monoms->insert_first(TMonom(0, 0));
	}
}

TPolynom::TPolynom(const string& _name) {
	monoms = new THeadRingList<TMonom>();
	name = _name;
	ParseMonoms(_name);
}

TPolynom::TPolynom(const THeadRingList<TMonom>* list) {
	if (list != nullptr && !list->IsEmpty()) {
		monoms = new THeadRingList<TMonom>(*list); // Копируем список
		delNULL();
		CombineSimilarMonoms();
		monoms->Sort();
	}
	else {
		monoms = new THeadRingList<TMonom>();
		monoms->insert_first(TMonom(0, 0));
	}
}
//	// Удаляем нулевые мономы
//	delNULL();
//	// Объединяем одинаковые мономы
//	CombineSimilarMonoms();
//	// Упорядочиваем список
//	monoms->Sort();
//}

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
		return "0"; // Возвращаем "0", если полином пустой
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
				// Используем спецификатор формата "%.2f" для вывода с двумя знаками после запятой
				str += (abs(coeff) == 1 ? ((coeff > 0) ? "1" : "1") : std::to_string(abs(coeff)));
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
	string str = _name;
	while (!str.empty()) {
		TMonom tmp;
		int degree = 0;
		size_t j = str.find_first_of("+-", 1);
		string monom = str.substr(0, j);
		str.erase(0, j);

		// Получаем коэффициент монома
		string coefficient = monom.substr(0, monom.find_first_of("xyz"));
		if (coefficient.empty() || coefficient == "+") {
			tmp.coeff = 1;
		}
		else if (coefficient == "-") {
			tmp.coeff = -1;
		}
		else {
			tmp.coeff = stod(coefficient);
		}

		// Удаляем из строки коэффициент монома
		monom.erase(0, monom.find_first_of("xyz"));

		// Получаем степень монома
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
					throw std::invalid_argument("Invalid monom format");
				}
			}
		}
		tmp.degree = degree;

		// Вставляем моном в полином, если его коэффициент не равен 0
		if (tmp.coeff != 0) {
			monoms->insert_sort(tmp);
		}
	}
	// Обновляем строковое представление полинома
	name = ToString();
}


const TPolynom& TPolynom::operator=(const TPolynom& polynom) {
	if (this != &polynom) {//проверка на самоприсваивание
		name = polynom.name;
		delete monoms;
		monoms = new THeadRingList<TMonom>(*(polynom.monoms));
	}
	return *this;
}
//TPolynom TPolynom::operator+(const TPolynom& polynom) {
//	TPolynom result(*this);
//	polynom.monoms->reset();
//	while (!polynom.monoms->IsEnded()) { // TODO: rewrite
//		TMonom current = polynom.monoms->GetCurrent()->data;
//		result.monoms->insert_sort(current);
//		polynom.monoms->next();
//	}
//	return result;
//}

TPolynom TPolynom::operator+(const TPolynom& polynom)
{
	//cout << "Current polynom: " << ToString() << std::endl;
	//cout << "Polynom to add: " << polynom.ToString() << std::endl;
	if (monoms->IsEmpty()) {
		return polynom;
	}
	if (polynom.monoms->IsEmpty()) {
		return *this;
	}

	THeadRingList<TMonom>* list = new THeadRingList<TMonom>();
	monoms->reset();
	polynom.monoms->reset();

	while (!monoms->IsEnded() && !polynom.monoms->IsEnded())
	{
		TMonom monom1 = monoms->GetCurrent()->data;
		TMonom monom2 = polynom.monoms->GetCurrent()->data;

		if (monom1 == monom2)
		{
			double coef1 = monom1.coeff;
			double coef2 = monom2.coeff;
			double coef_res = coef1 + coef2;

			if (coef_res != 0)
			{
				monom2.coeff = coef_res;
				list->insert_last(monom2);
			}

			monoms->next();
			polynom.monoms->next();
		}
		else if (monom2 < monom1)
		{
			list->insert_last(monom2);
			polynom.monoms->next();
		}
		else
		{
			list->insert_last(monom1);
			monoms->next();
		}
	}

	while (!monoms->IsEnded())
	{
		list->insert_last(monoms->GetCurrent()->data);
		monoms->next();
	}

	while (!polynom.monoms->IsEnded())
	{
		list->insert_last(polynom.monoms->GetCurrent()->data);
		polynom.monoms->next();
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
	result.monoms->reset();
	while (!result.monoms->IsEnded()) {
		result.monoms->GetCurrent()->data.coeff *= -1;
		result.monoms->next();
	}
	return result;
}

TPolynom TPolynom::operator*(const TPolynom& p)
{
	if (monoms->IsEmpty() || p.monoms->IsEmpty()) {
		return TPolynom(); // Возвращаем нулевой полином
	}
	THeadRingList<TMonom>* list = new THeadRingList<TMonom>();
	monoms->reset();
	p.monoms->reset();
	while (!monoms->IsEnded())
	{
		TMonom m = monoms->GetCurrent()->data;
		p.monoms->reset();
		while (!p.monoms->IsEnded())
		{
			TMonom m2 = p.monoms->GetCurrent()->data;
			double k = m.coeff;
			double k2 = m2.coeff;
			double k3 = k * k2;
			int d = m.degree;
			int d2 = m2.degree;
			int deg = d + d2;
			TMonom mon(k3, deg);
			list->insert_last(mon);
			p.monoms->next();
		}
		monoms->next();
	}
	TPolynom result;
	result.monoms = list;
	result.name = result.ToString();
	return result;
}

TPolynom TPolynom::dx() const {
	if (monoms->IsEmpty()) return TPolynom();
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
	if (monoms->IsEmpty()) return TPolynom();
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
	if (monoms->IsEmpty()) return TPolynom();
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

void TPolynom::delNULL() {
	if (monoms == nullptr || monoms->IsEmpty())
		return;

	monoms->reset(); // Reset the list to the beginning
	while (!monoms->IsEnded()) {
		if (monoms->GetCurrent()->data.coeff == 0.0) {
			// Remove the current node if coefficient is zero
			monoms->remove(monoms->GetCurrent()->data);
		}
		else {
			monoms->next(); // Move to the next node
		}
	}
}

void TPolynom::CombineSimilarMonoms() {
	if (monoms == nullptr || monoms->IsEmpty()) {
		return;
	}

	THeadRingList<TMonom>* combinedMonoms = new THeadRingList<TMonom>();
	monoms->reset();
	double coeffSum = 0.0;
	int currentDegree = monoms->GetCurrent()->data.degree;

	while (!monoms->IsEnded()) {
		if (monoms->GetCurrent()->data.degree == currentDegree) {
			coeffSum += monoms->GetCurrent()->data.coeff;
		}
		else {
			if (coeffSum != 0.0) {
				TMonom combinedTerm(coeffSum, currentDegree);
				combinedMonoms->insert_last(combinedTerm);
				coeffSum = 0.0;
			}
			currentDegree = monoms->GetCurrent()->data.degree;
			coeffSum = monoms->GetCurrent()->data.coeff;
		}
		monoms->next();
	}

	// Add the last term
	if (coeffSum != 0.0) {
		TMonom combinedTerm(coeffSum, currentDegree);
		combinedMonoms->insert_last(combinedTerm);
	}

	// Clear the original list and replace it with the combined list
	delete monoms;
	monoms = combinedMonoms;
}


double TPolynom::operator()(double x, double y, double z) const {
	if (monoms->IsEmpty()) {
		return 0.0;
	}
	double result = 0.0;

    monoms->reset();
    while (!monoms->IsEnded()) {
        TMonom monom = monoms->GetCurrent()->data;
        double monomValue = monom.coeff;

        int deg = monom.degree;
        int xExp = deg / 100;
        int yExp = (deg % 100) / 10;
        int zExp = deg % 10;

        // Вычисление значения монома для заданных значений переменных x, y и z
        monomValue *= pow(x, xExp) * pow(y, yExp) * pow(z, zExp);

        // Добавление значения монома к общему результату
        result += monomValue;

        monoms->next();
    }

    return result;
}
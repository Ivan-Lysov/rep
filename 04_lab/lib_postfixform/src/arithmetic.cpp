#include "stack.h"
#include "arithmetic.h"

TArithmeticExpression::TArithmeticExpression(const string& _infix) {
    if (_infix.empty()) {
        throw("expression is empty");
    }
    infix = _infix;
    RemoveSpaces(infix);
    if (!(isCorrectInfixExpression())) {
        throw("non-correct number of parentheses");
    }
}

map<string, int> TArithmeticExpression::priority = {
	{"^", 3},
	{"*", 3},
	{"/", 3},
	{"+", 2},
	{"-", 2},
	{"(", 1},
	{")", 1}
};

void TArithmeticExpression::RemoveSpaces(string& str) const {
	str.erase(remove(str.begin(), str.end(), ' '), str.end());
}

bool TArithmeticExpression::IsConst(const string& s) const {
	for (char c : s) {
		if (!isdigit(c) && c != '.') {
			return false;
		}
	}
	return true;
}

bool TArithmeticExpression::IsOperator(char c) const {
	return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^');
}

bool TArithmeticExpression::IsParenthesis(char c) const {
	return (c == '(' || c == ')');
}

bool TArithmeticExpression::IsDigitOrLetter(char c) const {
	return (isdigit(c) || c == '.' || isalpha(c));
}

void TArithmeticExpression::Parse()
{
	string currentElement;
	for (char c : infix) {
		if (IsOperator(c) || IsParenthesis(c) || c == ' ') {
			if (!currentElement.empty()) {
				lexems.push_back(currentElement);
				currentElement = "";
			}
			lexems.push_back(string(1, c));
		}
		else if (IsDigitOrLetter(c)) {
			currentElement += c;
		}
	}
	if (!currentElement.empty()) {
		lexems.push_back(currentElement);
	}
}

string TArithmeticExpression::ToPostfix() {
	Parse();
	TStack<string> st;
	string postfixExpression;
	for (string item : lexems) {
		if (item == "(") {
			st.Push(item);
		}
		else if (item == ")") {
			while (st.Top() != "(") {
				postfixExpression += st.Top();
				postfix.push_back(st.Top());
				st.Pop();
			}
			st.Pop();
		}
		else if (IsOperator(item[0])) {
			while (!st.IsEmpty() && priority[item] <= priority[st.Top()]) {
				postfixExpression += st.Top();
				postfix.push_back(st.Top());
				st.Pop();
			}
			st.Push(item);
		}
		else {
			double value = IsConst(item) ? stod(item) : 0.0;
			operands.insert({ item, value });
			postfix.push_back(item);
			postfixExpression += item;
		}
	}
	while (!st.IsEmpty()) {
		postfixExpression += st.Top();
		postfix.push_back(st.Top());
		st.Pop();
	}
	return postfixExpression;
}

double TArithmeticExpression::Calculate(const map<string, double>& values)
{
	for (auto& val : values) {
		try {
			operands.at(val.first) = val.second;
		}
		catch (out_of_range& e) {}
	}
	TStack<double> st;
	double leftOperand, rightOperand;
	for (string lexem : postfix) {
		if (lexem == "^") {
			rightOperand = st.Top(); st.Pop();
			leftOperand = st.Top(); st.Pop();
			st.Push(pow(leftOperand, rightOperand));
		}
		else if (lexem == "+") {
			rightOperand = st.Top(); st.Pop();
			leftOperand = st.Top(); st.Pop();
			st.Push(leftOperand + rightOperand);
		}
		else if (lexem == "-") {
			rightOperand = st.Top(); st.Pop();
			leftOperand = st.Top(); st.Pop();
			st.Push(leftOperand - rightOperand);
		}
		else if (lexem == "*") {
			rightOperand = st.Top(); st.Pop();
			leftOperand = st.Top(); st.Pop();
			st.Push(leftOperand * rightOperand);
		}
		else if (lexem == "/") {
			rightOperand = st.Top(); st.Pop();
			leftOperand = st.Top(); st.Pop();
			if (rightOperand == 0) { throw"Error"; }
			st.Push(leftOperand / rightOperand);
		}
		else {
			st.Push(operands[lexem]);
		}
	}
	return st.Top();
}

void TArithmeticExpression::SetValues(const vector<double>& values) {
	int i = 0;
	for (auto& op : operands)
	{
		if (!IsConst(op.first)) {
			operands[op.first] = values[i++];
		}
	}
}

double TArithmeticExpression::Calculate() {
    return Calculate(operands);
}

bool TArithmeticExpression::isCorrectInfixExpression()
{
    int count = 0;
    for (char c : infix)
    {
        if (c == '(') count++;
        else if (c == ')') count--;
        if (count < 0) return false;
    }
    return (count == 0);
}
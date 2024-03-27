#ifndef _ARITHMETIC_H
#define _ARITHMETIC_H
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include "stack.h"
using namespace std;

class TArithmeticExpression {
private:
	string infix;
	vector<string>  postfix;
	vector<string> lexems;
	static map<string, int> priority;
	map<string, double> operands;

	void Parse();
	bool IsConst(const string& st) const;
	bool IsOperator(char c) const;
	bool IsParenthesis(char c) const;
	bool IsDigitOrLetter(char c) const;
	double Calculate(const map<string, double>& values);
	void RemoveSpaces(string& str) const;
	bool isCorrectInfixExpression();
public:
	TArithmeticExpression(const string& _infix);
	string ToPostfix();
	string GetInfix() { return infix; }
	void SetValues();
	void SetValues(const vector<double>& values);
	double Calculate();	
};

#endif 
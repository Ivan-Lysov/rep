#include "stack.h"
#include "arithmetic.h"

MathArithmetics::MathArithmetics(const string& _infix) 
{
    if (_infix.empty())
    {
        throw("Expression contains no data");
    }
    infix = _infix;
    RemoveSpaces(infix);
    if (!(isCorrectInfixExpression()))
        throw("Wrong number of brackets");
}

map<string, int> MathArithmetics::priority = {
    {"^", 3},
    {"*", 3},
    {"/", 3},
    {"+", 2},
    {"-", 2},
    {"(", 1},
    {")", 1}
};

void MathArithmetics::RemoveSpaces(string& str) const
{
    str.erase(remove(str.begin(), str.end(), ' '), str.end());
}

bool MathArithmetics::IsConst(const string& s) const
{
    for (char symbol : s)
    {
        if (!isdigit(symbol) && symbol != '.')
            return false;
    }
    return true;
}

bool MathArithmetics::IsOperator(char symbol) const
{
    return (symbol == '+' || symbol == '-' || symbol == '*' || symbol == '/' || symbol == '^');
}

bool MathArithmetics::IsParenthesis(char symbol) const
{
    return (symbol == '(' || symbol == ')');
}

bool MathArithmetics::IsDigitOrLetter(char symbol) const
{
    return (isdigit(symbol) || symbol == '.' || isalpha(symbol));
}

void MathArithmetics::SetValues()
{
    double value;
    for (auto& op : operands)
    {
        if (!IsConst(op.first))
        {
            cout << "Enter value of " << op.first << ":";
            cin >> value;
            operands[op.first] = value;
        }
    }
}

void MathArithmetics::SetValues(const vector<double>& values)
{
    int i = 0;
    for (auto& op : operands)
    {
        if (!IsConst(op.first))
        {
            operands[op.first] = values[i++];
        }
    }
}

void MathArithmetics::Parse()
{
    string currentElement;
    for (char symbol : infix) {
        if (IsOperator(symbol) || IsParenthesis(symbol) || symbol == ' ')
        {
            if (!currentElement.empty())
            {
                lexems.push_back(currentElement);
                currentElement = "";
            }
            lexems.push_back(string(1, symbol));
        }
        else if (IsDigitOrLetter(symbol))
        {
            currentElement += symbol;
        }
    }
    if (!currentElement.empty())
    {
        lexems.push_back(currentElement);
    }
}

string MathArithmetics::ToPostfix()
{
    Parse();
    TStack<string> stack;
    string postfixExpression;
    for (string item : lexems)
    {
        if (item == "(")
            stack.Push(item);
        else if (item == ")")
        {
            while (stack.Top() != "(")
            {
                postfixExpression += stack.Top();
                postfix.push_back(stack.Top());
                stack.Pop();
            }
            stack.Pop();
        }
        else if (IsOperator(item[0]))
        {
            while (!stack.IsEmpty() && priority[item] <= priority[stack.Top()])
            {
                postfixExpression += stack.Top();
                postfix.push_back(stack.Top());
                stack.Pop();
            }
            stack.Push(item);
        }
        else
        {
            double value = IsConst(item) ? stod(item) : 0.0;
            operands.insert({ item, value });
            postfix.push_back(item);
            postfixExpression += item;
        }
    }
    while (!stack.IsEmpty())
    {
        postfixExpression += stack.Top();
        postfix.push_back(stack.Top());
        stack.Pop();
    }
    return postfixExpression;
}

double MathArithmetics::Calculate(const map<string, double>& values)
{
    for (auto& val : values)
    {
        try
        {
            operands.at(val.first) = val.second;
        }
        catch (out_of_range& e) {}
    }
    TStack<double> stack;
    double leftOperand, rightOperand;
    for (string lexem : postfix)
    {
        if (lexem == "^") {
            rightOperand = stack.Top(); stack.Pop();
            leftOperand = stack.Top(); stack.Pop();
            stack.Push(pow(leftOperand, rightOperand));
        }
        else if (lexem == "+")
        {
            rightOperand = stack.Top();
            stack.Pop();
            leftOperand = stack.Top();
            stack.Pop();
            stack.Push(leftOperand + rightOperand);
        }
        else if (lexem == "-")
        {
            rightOperand = stack.Top();
            stack.Pop();
            leftOperand = stack.Top();
            stack.Pop();
            stack.Push(leftOperand - rightOperand);
        }
        else if (lexem == "*")
        {
            rightOperand = stack.Top();
            stack.Pop();
            leftOperand = stack.Top();
            stack.Pop();
            stack.Push(leftOperand * rightOperand);
        }
        else if (lexem == "/")
        {
            rightOperand = stack.Top();
            stack.Pop();
            leftOperand = stack.Top();
            stack.Pop();
            if (rightOperand == 0)
                throw"You cant divide by zero";
            stack.Push(leftOperand / rightOperand);
        }
        else
        {
            stack.Push(operands[lexem]);
        }
    }
    return stack.Top();
}

double MathArithmetics::Calculate()
{
    return Calculate(operands);
}

bool MathArithmetics::isCorrectInfixExpression()
{
    int count = 0;
    for (char symbol : infix)
    {
        if (symbol == '(')
            count++;
        else if (symbol == ')')
            count--;
        if (count < 0)
            return false;
    }
    return (count == 0);
}
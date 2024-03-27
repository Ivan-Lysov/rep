#include "arithmetic.h"
#include <gtest.h>

TEST(TArithmeticExpression, can_create_expression) {
	string str = "A+B";
	TArithmeticExpression expression(str);
	EXPECT_EQ(str, expression.GetInfix());
}

TEST(TArithmeticExpression, cannot_create_empty_expression) {
	ASSERT_ANY_THROW(TArithmeticExpression expression(""));
}

TEST(TArithmeticExpression, throw_when_unequal_number_of_brackets1) {
	ASSERT_ANY_THROW(TArithmeticExpression expression("((a+b)"));
}

TEST(TArithmeticExpression, throw_when_unequal_number_of_brackets2) {
	ASSERT_ANY_THROW(TArithmeticExpression expression("(a+b))"));
}

TEST(TArithmeticExpression, no_throw_when_equal_number_of_brackets) {
	ASSERT_NO_THROW(TArithmeticExpression expression("(a+b)"));
}

TEST(TArithmeticExpression, no_throw_when_brackets_inside_brackets) {
	ASSERT_NO_THROW(TArithmeticExpression expression("((c*a)+b)"));
}

TEST(TArithmeticExpression, no_throw_when_one_elemet_in_brackets) {
	ASSERT_NO_THROW(TArithmeticExpression expression("a+(a)"));
}


TEST(TArithmeticExpression, can_correctly_count_when_brackets_inside_brackets) {
	TArithmeticExpression expression("((c*a)+b)");
	vector<double> example = { 1,2,3 };
	expression.ToPostfix();
	expression.SetValues(example);
	EXPECT_EQ(5, expression.Calculate());
}

TEST(TArithmeticExpression, cannot_count_if_there_are_no_values) {
	TArithmeticExpression expression("a+b");
	expression.ToPostfix();
	EXPECT_EQ(0, expression.Calculate());
}

TEST(TArithmeticExpression, can_copy_expression) {
	string str = "A+B";
	TArithmeticExpression expression1(str);
	ASSERT_NO_THROW(TArithmeticExpression expression2(expression1));
}

TEST(TArithmeticExpression, throw_when_expression_is_operator) {
	TArithmeticExpression expression("+");
	expression.ToPostfix();
	ASSERT_ANY_THROW(expression.Calculate());
}

TEST(TArithmeticExpression, throw_when_first_symbol_is_operator)
{
	TArithmeticExpression expression("/(a - b)");
	expression.ToPostfix();
	ASSERT_ANY_THROW(expression.Calculate());
}

TEST(TArithmeticExpression, throw_when_only_one_operand)
{
	TArithmeticExpression expression("a+");
	expression.ToPostfix();
	ASSERT_ANY_THROW(expression.Calculate());
}

TEST(TArithmeticExpression, can_expression_consist_of_a_complex_expression) {
	string str = "A1+B2";
	TArithmeticExpression expression(str);
	EXPECT_EQ(str, expression.GetInfix());
}

TEST(TArithmeticExpression, can_convert_to_postfix) {
	string str = "abc*+cd/e-*";
	TArithmeticExpression expression("(a+b*c)*(c/d-e)");
	EXPECT_EQ(str, expression.ToPostfix());
}

TEST(TArithmeticExpression, can_set_integer_elements) {
	TArithmeticExpression expression("(a+b*c)*(c/d-e)");
	vector<double> example = { 1,2,3,4,5 };
	expression.ToPostfix();
	expression.SetValues(example);
	EXPECT_EQ(-29.75, expression.Calculate());
}

TEST(TArithmeticExpression, can_set_double_elements) {
	TArithmeticExpression expression("a+b*c");
	vector<double> example = { 1.4,2.7,4.9 };
	expression.ToPostfix();
	expression.SetValues(example);
	ASSERT_NEAR(14.63, expression.Calculate(), 1);
}

TEST(TArithmeticExpression, can_set_equal_elements) {
	TArithmeticExpression expression("a+a+a+b+b");
	vector<double> example = { 1,2 };
	expression.ToPostfix();
	expression.SetValues(example);
	EXPECT_EQ(7, expression.Calculate());
}

TEST(TArithmeticExpression, throw_when_have_zero_division) {
	TArithmeticExpression expression("1/0");
	expression.ToPostfix();
	ASSERT_ANY_THROW(expression.Calculate());
}

TEST(TArithmeticExpression, can_get_integer_const) {
	TArithmeticExpression expression("1+2");
	expression.ToPostfix();
	EXPECT_EQ(3, expression.Calculate());
}

TEST(TArithmeticExpression, can_get_double_const) {
	TArithmeticExpression expression("2.6-1.5");
	expression.ToPostfix();
	EXPECT_EQ(1.1, expression.Calculate());
}

TEST(TArithmeticExpression, expression_with_different_order_are_not_equal_in_div) {
	vector<double> example = { 1,2 };
	TArithmeticExpression expression1(" a/b");
	TArithmeticExpression expression2(" b/a");
	expression1.ToPostfix();
	expression2.ToPostfix();
	expression1.SetValues(example);
	expression2.SetValues(example);
	EXPECT_NE(expression1.Calculate(), expression2.Calculate());
}

TEST(TArithmeticExpression, expression_with_different_order_are_not_equal_in_sub) {
	vector<double> example = { 1,2 };
	TArithmeticExpression expression1(" a-b");
	TArithmeticExpression expression2(" b-a");
	expression1.ToPostfix();
	expression2.ToPostfix();
	expression1.SetValues(example);
	expression2.SetValues(example);
	EXPECT_NE(expression1.Calculate(), expression2.Calculate());
}

TEST(TArithmeticExpression, expression_with_spaces)
{
	TArithmeticExpression expression("  ( a  +   b*   c)*(c   /  d- e ) ");
	vector<double> example = { 1,2,3,4,5 };
	expression.ToPostfix();
	expression.SetValues(example);
	EXPECT_EQ(-29.75, expression.Calculate());
}

TEST(TArithmeticExpression, expression_with_words_and_numbers)
{
	TArithmeticExpression expression("digit+4-10+word");
	vector<double> example = { 1.7,1.3 };
	expression.ToPostfix();
	expression.SetValues(example);
	EXPECT_EQ(-3, expression.Calculate());
}
//
//#include "arithmetic.h"
//#include <gtest.h>
//
//TEST(MathArithmetics, can_create_expression)
//{
//	string str = "(a+b)*(c-d)";
//	MathArithmetics expression(str);
//	EXPECT_EQ(str, expression.GetInfix());
//}
//
//TEST(MathArithmetics, cannot_create_empty_expression)
//{
//	ASSERT_ANY_THROW(MathArithmetics expression(""));
//}
//
//TEST(MathArithmetics, throw_when_unequal_number_of_left_bracket)
//{
//	ASSERT_ANY_THROW(MathArithmetics expression("((A+B)"));
//}
//
//TEST(MathArithmetics, throw_when_unequal_number_of_right_brackets)
//{
//	ASSERT_ANY_THROW(MathArithmetics expression("(A+B))"));
//}
//
//TEST(MathArithmetics, no_throw_when_equal_number_of_brackets)
//{
//	ASSERT_NO_THROW(MathArithmetics expression("(A+B)"));
//}
//
//TEST(MathArithmetics, no_throw_when_brackets_inside_brackets)
//{
//	ASSERT_NO_THROW(MathArithmetics expression("((C*A)+B)"));
//}
//
//TEST(MathArithmetics, no_throw_when_one_elemet_in_brackets)
//{
//	ASSERT_NO_THROW(MathArithmetics expression("(A+(B))"));
//}
//
//
//TEST(MathArithmetics, can_correctly_count_when_brackets_inside_brackets)
//{
//	MathArithmetics expression("((a+b)*c)");
//	vector<double> example = { 1,2,3 };
//	expression.ToPostfix();
//	expression.SetValues(example);
//	EXPECT_EQ(9, expression.Calculate());
//}
//
//TEST(MathArithmetics, cannot_count_if_there_are_no_values)
//{
//	MathArithmetics expression("A+B");
//	expression.ToPostfix();
//	EXPECT_EQ(0, expression.Calculate());
//}
//
//TEST(MathArithmetics, can_copy_expression)
//{
//	string str = "A+B";
//	MathArithmetics express(str);
//	ASSERT_NO_THROW(MathArithmetics express2(express));
//}
//
//TEST(MathArithmetics, any_throw_when_expression_is_operator)
//{
//	MathArithmetics expression("+");
//	expression.ToPostfix();
//	ASSERT_ANY_THROW(expression.Calculate());
//}
//
//TEST(MathArithmetics, throw_when_first_symbol_is_operator)
//{
//	MathArithmetics expression("+(35-a)");
//	expression.ToPostfix();
//	ASSERT_ANY_THROW(expression.Calculate());
//}
//
//TEST(MathArithmetics, throw_when_only_one_operand)
//{
//	MathArithmetics expression("F+");
//	expression.ToPostfix();
//	ASSERT_ANY_THROW(expression.Calculate());
//}
//
//TEST(MathArithmetics, can_expression_consist_of_a_complex_expression)
//{
//	string str = "A1+B2";
//	MathArithmetics expression(str);
//	EXPECT_EQ(str, expression.GetInfix());
//}
//
//TEST(MathArithmetics, can_convert_to_postfix)
//{
//	string str = "abc*+cd/e-*";
//	MathArithmetics expression("(a+b*c)*(c/d-e)");
//	EXPECT_EQ(str, expression.ToPostfix());
//}
//
//TEST(MathArithmetics, can_set_integer_elements) {
//	MathArithmetics expression("(a*b+c)*(d-c)");
//	vector<double> example = { 1,2,3,4 };
//	expression.ToPostfix();
//	expression.SetValues(example);
//	EXPECT_EQ(5, expression.Calculate());
//}
//
//TEST(MathArithmetics, can_set_double_elements)
//{
//	MathArithmetics expression("a+b*c");
//	vector<double> example = { 1.7,5.5,7.1 };
//	expression.ToPostfix();
//	expression.SetValues(example);
//	ASSERT_NEAR(40, 75, expression.Calculate(), 1);
//}
//
//TEST(MathArithmetics, can_set_equal_elements)
//{
//	MathArithmetics expression("A+B+A+B+C");
//	vector<double> example = { 1,2,3 };
//	expression.ToPostfix();
//	expression.SetValues(example);
//	EXPECT_EQ(9, expression.Calculate());
//}
//
//TEST(MathArithmetics, throw_when_have_zero_division)
//{
//	MathArithmetics expression("5/0");
//	expression.ToPostfix();
//	ASSERT_ANY_THROW(expression.Calculate());
//}
//
//
//TEST(MathArithmetics, expression_with_different_order_are_not_equal_in_sub)
//{
//	vector<double> example = { 1,2 };
//	MathArithmetics expression1(" a-b");
//	MathArithmetics expression2(" b-a");
//	expression1.ToPostfix();
//	expression2.ToPostfix();
//	expression1.SetValues(example);
//	expression2.SetValues(example);
//	EXPECT_NE(expression1.Calculate(), expression2.Calculate());
//}
//
//TEST(MathArithmetics, can_get_float_const)
//{
//	MathArithmetics expression("2.6-1.5");
//	expression.ToPostfix();
//	EXPECT_EQ(1.1, expression.Calculate());
//}
//
//TEST(MathArithmetics, expression_with_spaces)
//{
//	MathArithmetics expression("  ( a  +   b*   c) * (c   /  d - e ) ");
//	vector<double> example = { 1,2,3,4,5 };
//	expression.ToPostfix();
//	expression.SetValues(example);
//	EXPECT_EQ(-29.75, expression.Calculate());
//}
//
//TEST(MathArithmetics, expression_with_words_and_numbers)
//{
//	MathArithmetics expression("numbers+4-10+words");
//	vector<double> example = { 5.5,-3.5 };
//	expression.ToPostfix();
//	expression.SetValues(example);
//	EXPECT_EQ(-4, expression.Calculate());
//}

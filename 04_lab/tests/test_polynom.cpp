#include "polynom.h"
#include <gtest.h>
const string str="x+y+z+1";

TEST(TPolynom, create_polinom)
{
	ASSERT_NO_THROW(TPolynom polynom(str));
}

TEST(TPolynom, create_is_empty_polynom)
{
	ASSERT_NO_THROW(TPolynom polynom());
}

TEST(TPolynom, can_create_copied_polinom)
{
	TPolynom polynom1(str);
	ASSERT_NO_THROW(TPolynom polynom2(polynom1));
}

TEST(TPolynom, equality_operator_is_correct)
{
	TPolynom polynom1(str);
	TPolynom polynom2(str);
	EXPECT_EQ(polynom1, polynom2);
}

TEST(TPolynom, no_throw_when_polynom_will_be_empty) 
{
   ASSERT_NO_THROW(TPolynom polynom("x-x+y-y+z-z+1-1"));
}

TEST(TPolynom, conversation_test) {
	TPolynom polynom1("x+x-x+x+y+y+z+z+z+2-2+3+4");
	TPolynom polynom2("2x+2y+3z+7");
	EXPECT_EQ(polynom1, polynom2);
}

TEST(TPolynom, can_create_polynom_in_different_order)
{
	TPolynom polynom("x+y+z");
	TPolynom p_reordered("z+y+x");
	EXPECT_EQ(polynom, p_reordered);
}

TEST(TPolynom, can_create_polynom_with_ppozitive_coefficient)
{
	ASSERT_NO_THROW(TPolynom polynom("2z^2"));
}

TEST(TPolynom, can_create_polynom_with_equal_coefficient)
{
	ASSERT_NO_THROW(TPolynom polynom("0*y^2"));
}

TEST(TPolynom, can_create_polynom_with_negative_coefficient)
{
	ASSERT_NO_THROW(TPolynom polynom("-2x^2"));
}
TEST(TPolynom, dx_is_correct)
{
	TPolynom polynom("x^3+x^2+y+z+1");
	TPolynom tmp("3x^2+2x");
	EXPECT_EQ(polynom.dx().ToString(), tmp.ToString());
}

TEST(TPolynom, dy_is_correct)
{
	TPolynom polynom("y^3+y^2+x+z+1");
	TPolynom tmp("3y^2+2y");
	EXPECT_EQ(polynom.dy().ToString(), tmp.ToString());
}

TEST(TPolynom, dz_is_correct)
{
	TPolynom polynom("z^3+z^2+y+x+1");
	TPolynom tmp("3z^2+2z");
	EXPECT_EQ(polynom.dz().ToString(), tmp.ToString());
}

TEST(TPolynom,no_throw_when_no_monomials_to_derive_dx)
{
	TPolynom polynom("z^3+y+1");
	ASSERT_NO_THROW(polynom.dx());
}

TEST(TPolynom, dy_returns_zero_for_polynomial_without_y_terms)
{
	TPolynom polynom("z^3+x+1");
	TPolynom result = polynom.dy();
	TPolynom expected("0"); // ќжидаемый результат дл€ полинома без членов с y
	ASSERT_EQ(result, expected);
}

TEST(TPolynom, calculate_is_correct_with_string)
{
	TPolynom pol(str);
	double res = pol(1, 2, 3);
	EXPECT_EQ(7, pol(1, 2, 3));
}

TEST(TPolynom, calculate_is_correct_with_less_euqel)
{
	TPolynom pol("x^3+x^2+y+z+1");
	double res = pol(0.1, 0.2, 0.3);
	ASSERT_NEAR(1.511, res, 1);
}

TEST(TPolynom, calculate_is_correct_when_polynom_is_const_and_x_y_z_not_null)
{
	TPolynom p("5");
	EXPECT_EQ(p(0, 0, 0), 5);
}

TEST(TPolynom, calculate_is_correct_with_full_polynom)
{
	TPolynom pol("x^3+x^2+y+z+1");
	double res = pol(1, 2, 3);
	EXPECT_EQ(8, pol(1, 2, 3));
}

TEST(TPolynom, calculate_is_correct_with_not_full_polynom) {
	TPolynom polynom("x^2 + y^2");
	double result = polynom(2, 3, 0);
	EXPECT_EQ(result, 13);
}

TEST(TPolynom, calculate_is_correct_with_not_full_polynom_and_with_null) {
	TPolynom polynom("x^2 + y^2");
	double result = polynom(0, 0, 0);
	EXPECT_EQ(result, 0);
}

TEST(TPolynom, calculate_is_correct_with_null_and_x_y_z_not_null) {
	TPolynom polynom("0");
	double result = polynom(1, 1, 1);
	EXPECT_EQ(result, 0);
}

TEST(TPolynom, no_throw_when_no_monomials_to_derive_dz)
{
	TPolynom polynom("x^3+y+1");
	ASSERT_NO_THROW(polynom.dz());
}

TEST(TPolynom,summ_is_correct_work) 
{
	TPolynom polynom1("x^3+y^3+z^3+1");
	TPolynom polynom2("x^3+y^3+z^3+1");
	TPolynom polynom3("2x^3+2y^3+2z^3+2");
	EXPECT_EQ(polynom1+polynom2, polynom3);
}

TEST(TPolynom, sum_with_zero_and_xyz)
{
	TPolynom polynom1("0");
	TPolynom polynom2("x+y+z");
	TPolynom expectedResult("x+y+z");
	EXPECT_EQ(polynom1 + polynom2, expectedResult);
}

TEST(TPolynom, diff_is_correct_work)
{
	TPolynom polynom1("2x^3+y^2+10");
	TPolynom polynom2("x^3-2y^2+z");
	TPolynom polynom3("x^3+3y^2-z+10");
	EXPECT_EQ(polynom1-polynom2, polynom3);
}

TEST(TPolynom, diff_is_with_negative_coefficients)
{
	TPolynom polynom1("-3x^2-2y+5");
	TPolynom polynom2("-x^2-4y-3");
	TPolynom polynom3("-2x^2-2y+8");
	EXPECT_EQ(polynom1 - polynom2, polynom3);
}

TEST(TPolynom, mult_test1)
{
	TPolynom polynom1("x^2*x");
	TPolynom polynom2("x^3");
	EXPECT_EQ(polynom1, polynom2);
}

TEST(TPolynom, mult_with_0_results_in_empty_polynom)
{
	TPolynom polynom1("x+1");
	TPolynom polynom2("0");
	EXPECT_TRUE((polynom1 * polynom2).ToString() == "0");
}

TEST(TPolynom, mult_is_correct_with_1)
{
	TPolynom polynom1("x+1");
	TPolynom polynom2("y+1");
	TPolynom result_polynom("x*y+x+y+1");
	EXPECT_EQ(polynom1 * polynom2, result_polynom);
}

TEST(TPolynom, to_string_is_correct)
{
	TPolynom polynom1("x^3+x^2+y+z");
	string str = "x^3+x^2+y+z";
	EXPECT_EQ(polynom1.ToString(), str);
}

TEST(TPolynomConstructorTest, NonZeroMonoms) {
	THeadRingList<TMonom> monomList;
	monomList.insert_first(TMonom(1.0, 2)); // моном x^2
	monomList.insert_last(TMonom(3.0, 1)); // моном 3x
	monomList.insert_last(TMonom(4.0, 0)); // моном 4

	TPolynom poly(monomList);

	// ќжидаемый полином: x^2 + 3x + 4
	TPolynom expectedPoly(monomList);

	ASSERT_EQ(poly, expectedPoly);
}

TEST(TPolynom, parses_positive_expression_with_exponents_and_coefficients) {
	EXPECT_EQ("-3x^5z^2+x^2y^3", TPolynom("x^2*y^3 - 3*z^2*x^5").ToString());
}

TEST(TPolynom, parses_negative_expression_with_exponents_and_coefficients) {
	EXPECT_EQ("-3x^5z^2-x^2y^3", TPolynom("-x^2*y^3 - 3*z^2*x^5").ToString());
}

TEST(TPolynom, parses_expression_with_addition_operators) {
	EXPECT_EQ("-x+5", TPolynom("x + 1 - 2*x + 4").ToString());
}

TEST(TPolynom, parses_expression_with_redundant_plus_and_minus_operators) {
	EXPECT_EQ("0", TPolynom("x-x+y-y-1+1").ToString());
}

TEST(TPolynom, parses_zero_polynomial) {
	EXPECT_EQ("0", TPolynom("0").ToString());
}

TEST(TPolynom, parses_polynomial_with_zero_constant_term) {
	EXPECT_EQ("x", TPolynom("0+x").ToString());
}

TEST(TPolynom, parses_polynomial_with_zero_variable_term) {
	EXPECT_EQ("x", TPolynom("x-0").ToString());
}

TEST(TPolynom, zero_minus_null) {
	EXPECT_EQ("-x", TPolynom("0-x").ToString());
}



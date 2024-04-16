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
	ASSERT_NO_THROW(TPolynom polynom("0y^2"));
}

TEST(TPolynom, can_create_polynom_with_negative_coefficient)
{
	ASSERT_NO_THROW(TPolynom polynom("-2x^2"));
}

TEST(TPolynom, dx_is_correct) 
{
	TPolynom polynom("x^3+x^2+y+z+1");
	TPolynom tmp("3x^2+2x");
	EXPECT_EQ(polynom.dx(), tmp);
}

TEST(TPolynom, dy_is_correct) 
{
	TPolynom polynom("y^3+y^2+x+z+1");
	TPolynom tmp("3y^2+2y");
	EXPECT_EQ(polynom.dy() , tmp);
}

TEST(TPolynom, dz_is_correct) 
{
	TPolynom polynom("z^3+z^2+y+x+1");
	TPolynom tmp("3z^2+2z");
	EXPECT_EQ(polynom.dz(), tmp);
}

TEST(TPolynom,no_throw_when_no_monomials_to_derive_dx)
{
	TPolynom polynom("z^3+y+1");
	ASSERT_NO_THROW(polynom.dx());
}

TEST(TPolynom, no_throw_when_no_monomials_to_derive_dy)
{
	TPolynom polynom("z^3+x+1");
	ASSERT_NO_THROW(polynom.dy());
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

TEST(TPolynom, mult_is_correct_with_fractional_degree)
{
	TPolynom polynom1("x^2+y");
	TPolynom polynom2("x^1/2");
	TPolynom result_polynom("x^3/2+yx^1/2");
	EXPECT_EQ(polynom1 * polynom2, result_polynom);
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
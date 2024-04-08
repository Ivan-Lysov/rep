#include "polynom.h"
#include <gtest.h>
const string str="x+y+z";

TEST(TPolynom, create_empty_polinom)
{
	ASSERT_NO_THROW(TPolynom p());
}

TEST(TPolynom, create_polinom)
{
	ASSERT_NO_THROW(TPolynom p(str));
}

TEST(TPolynom, can_create_copied_polinom)
{
	TPolynom p1(str);
	ASSERT_NO_THROW(TPolynom p2(p1));
}

TEST(TPolynom, equality_operator_is_correct)
{
	TPolynom p1(str);
	TPolynom p2(str);
	EXPECT_EQ(p1, p2);
}

TEST(TPolynom, copied_polinom_is_correct)
{
	TPolynom p1(str);
	TPolynom p2(p1);
	EXPECT_EQ(p1, p2);
}

TEST(TPolynom, no_throw_when_polynom_will_be_empty) 
{
   ASSERT_NO_THROW(TPolynom p("x-x+y-y+z-z"));
}

TEST(TPolynom, conversation_test) {
	TPolynom p1("x+x-x+x+y+y+z+z+z");
	TPolynom p2("2x+2y+3z");
	EXPECT_EQ(p1, p2);
}

TEST(TPolynom, calculate_is_correct1) 
{
	TPolynom pol(str);
	double res = pol(1,2,3);
	EXPECT_EQ(6, pol(1, 2, 3));
}

TEST(TPolynom, calculate_is_correct2)
{
	TPolynom pol("x^3+x^2+y+z+1");
	double res = pol(0.1, 0.2, 0.3);
	ASSERT_NEAR(1.511, res, 1);
}

TEST(TPolynom, calculate_is_correct3)
{
	TPolynom pol("x^3+x^2+y+z+1");
	double res = pol(1, 2, 3);
	EXPECT_EQ(8, pol(1, 2, 3));
}

TEST(TPolynom, dx_is_correct) 
{
	TPolynom pol("x^3+x^2+y+z+1");
	TPolynom tmp("3x^2+2x^1");
	EXPECT_EQ(pol.dx(), tmp);
}

TEST(TPolynom, dy_is_correct) 
{
	TPolynom pol("y^3+y^2+x+z+1");
	TPolynom tmp("3y^2+2y^1");
	EXPECT_EQ(pol.dy() , tmp);
}

TEST(TPolynom, dz_is_correct) 
{
	TPolynom pol("z^3+z^2+y+x+1");
	TPolynom tmp("3z^2+2z^1");
	EXPECT_EQ(pol.dz(), tmp);
}

TEST(TPolynom,no_throw_when_no_monomials_to_derive)
{
	TPolynom pol("z^3+z^2+y+1");
	ASSERT_NO_THROW(pol.dx());
}

TEST(TPolynom,sum_is_correct ) 
{
	TPolynom pol1("x^3+y^2+y+x+1");
	TPolynom pol2("x^3+y+z+1");
	TPolynom pol3("2x^3+y^2+2y+x+2+z");
	EXPECT_EQ(pol1+pol2, pol3);
}

TEST(TPolynom, diff_is_correct) 
{
	TPolynom pol1("2x^3+y^2+y+x");
	TPolynom pol2("x^3-2y^2+z");
	TPolynom pol3("x^3+3y^2+y^1+x-z");
	EXPECT_EQ(pol1-pol2, pol3);
}

TEST(TPolynom, mult_is_correct) 
{
	TPolynom pol1("x^2+y");
	TPolynom pol2("x^3+x");
	TPolynom pol3("x^5+x^3+x^3*y+x*y");
	EXPECT_EQ(pol1*pol2, pol3);
}
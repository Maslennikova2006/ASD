// Copyright 2026 Mary Maslennikova

#include <gtest/gtest.h>
#include "../lib_polynom/polynom.h"

TEST(TestPolynomLib, can_create) {
    ASSERT_NO_THROW(Polynom m);
}
TEST(TestPolynomLib, check_default_create) {
    Polynom pol;
    Monom m;
    EXPECT_EQ(m, pol.get_monoms().head()->value);
}
TEST(TestPolynomLib, can_create_string_constructor) {
    ASSERT_NO_THROW(Polynom p("5.8x^2+8y^3z^4"));
}
TEST(TestPolynomLib, check_copy_constructor) {
    Polynom p;
    ASSERT_NO_THROW(Polynom(p));
}
TEST(TestPolynomLib, can_create_copy_constructor) {
    int powers1[3] = { 2, 3, 1 };
    int powers2[3] = { 2, 3, 5 };
    Monom m1(4.78, powers1);
    Monom m2(2.67, powers2);
    Polynom pol(m1);
    pol += m2;
    Polynom polynom(pol);
    EXPECT_EQ(m2, polynom.get_monoms().head()->value);
    EXPECT_EQ(m1, polynom.get_monoms().tail()->value);
}
TEST(TestPolynomLib, check_monom_constructor) {
    Monom m;
    ASSERT_NO_THROW(Polynom(m));
}
TEST(TestPolynomLib, can_create_monom_constructor) {
    int powers[3] = { 2, 3, 5 };
    Monom m(4.78, powers);
    Polynom pol(m);
    EXPECT_EQ(m, pol.get_monoms().head()->value);
}
TEST(TestPolynomLib, check_string_constructor) {
    ASSERT_NO_THROW(Polynom("2.3x^3y^2z+8.6x^2yz"));
}
TEST(TestPolynomLib, check_create_string_constructor) {
    Polynom pol("2.3x^3y^2z-8.6x^2yz");
    Monom m1("2.3x^3y^2z");
    Monom m2("-8.6x^2yz");
    EXPECT_EQ(m1, pol.get_monoms().head()->value);
    EXPECT_EQ(m2, pol.get_monoms().tail()->value);
}
TEST(TestPolynomLib, check_addition_polynoms) {
    Polynom p1("2.4x^3y^2+7.34y^3");
    Polynom p2("3.6x^3y^2+5.4y^3z^2");
    Polynom pol = p1 + p2;
    std::string expected = "6.000000x^3y^2+5.400000y^3z^2+7.340000y^3";
    EXPECT_EQ(pol.toString(), expected);
}
TEST(TestPolynomLib, check_addition_with_assignment) {
    Polynom p1("2.4x^3y^2+7.34y^3-4.6z^3");
    Polynom p2("3.6x^3y^2+5.4y^3z^2");
    p1 += p2;
    std::string expected = "6.000000x^3y^2+5.400000y^3z^2+7.340000y^3-4.600000z^3";
    EXPECT_EQ(p1.toString(), expected);
}
TEST(TestPolynomLib, check_subtraction_polynoms) {
    Polynom p1("2.4x^3y^2+7.34y^3");
    Polynom p2("3.6x^3y^2+5.4y^3z^2");
    Polynom pol = p1 - p2;
    std::string expected = "-1.200000x^3y^2-5.400000y^3z^2+7.340000y^3";
    EXPECT_EQ(pol.toString(), expected);
}
TEST(TestPolynomLib, check_subtraction_with_assignment) {
    Polynom p1("2.4x^3y^2+7.34y^3-4.6z^3");
    Polynom p2("3.6x^3y^2+5.4y^3z^2+2x");
    p1 -= p2;
    std::string expected = "-1.200000x^3y^2-2.000000x-5.400000y^3z^2+7.340000y^3-4.600000z^3";
    EXPECT_EQ(p1.toString(), expected);
}
TEST(TestPolynomLib, check_multiplication_polynoms) {
    Polynom p1("2.4x^3y^2-4.6z^3+z^2");
    Polynom p2("3.6x^3y^3+2x");
    Polynom pol = p1 * p2;
    std::string expected = "8.640000x^6y^5+4.800000x^4y^2-16.560000x^3y^3z^3+3.600000x^3y^3z^2-9.200000xz^3+2.000000xz^2";
    EXPECT_EQ(pol.toString(), expected);
}
TEST(TestPolynomLib, check_multiplication_with_assignment) {
    Polynom p1("2.4x^3y^2+7.3z^2");
    Polynom p2("3.6x^3y^3+2x");
    p1 *= p2;
    std::string expected = "8.640000x^6y^5+4.800000x^4y^2+26.280000x^3y^3z^2+14.600000xz^2";
    EXPECT_EQ(p1.toString(), expected);
}
TEST(TestPolynomLib, check_addition_polynoms_by_scalar) {
    Polynom p1("3.1x^2y+7.3x^2z^2");
    Polynom pol = p1 + 8.76;
    std::string expected = "3.100000x^2y+7.300000x^2z^2+8.760000";
    EXPECT_EQ(pol.toString(), expected);
}
TEST(TestPolynomLib, check_addition_with_assignment_polynoms_by_scalar) {
    Polynom p1("3.1x^2y+7.3x^2z^2-70.6");
    p1 += 67.6;
    std::string expected = "3.100000x^2y+7.300000x^2z^2-3.000000";
    EXPECT_EQ(p1.toString(), expected);
}
TEST(TestPolynomLib, check_subtraction_polynoms_by_scalar) {
    Polynom p1("3.1x^2y+7.3x^2z^2");
    Polynom pol = p1 - 8.76;
    std::string expected = "3.100000x^2y+7.300000x^2z^2-8.760000";
    EXPECT_EQ(pol.toString(), expected);
}
TEST(TestPolynomLib, check_subtraction_with_assignment_polynoms_by_scalar) {
    Polynom p1("3.1x^2y+7.3x^2z^2+70.6");
    p1 -= 67.6;
    std::string expected = "3.100000x^2y+7.300000x^2z^2+3.000000";
    EXPECT_EQ(p1.toString(), expected);
}
TEST(TestPolynomLib, check_multiplication_polynoms_by_scalar) {
    Polynom p1("3.1x^2y+7.3x^2z^2");
    Polynom pol = p1 * 8.76;
    std::string expected = "27.156000x^2y+63.948000x^2z^2";
    EXPECT_EQ(pol.toString(), expected);
}
TEST(TestPolynomLib, check_multiplication_polynoms_by_scalar2) {
    Polynom p1("3.1x^2y+7.3x^2z^2");
    Polynom pol = 8.76 * p1;
    std::string expected = "27.156000x^2y+63.948000x^2z^2";
    EXPECT_EQ(pol.toString(), expected);
}
TEST(TestPolynomLib, check_multiplication_polynoms_by_scalar3) {
    Polynom p1("3.1x^2y+7.3x^2z^2");
    Polynom pol = 0.0 * p1;
    Monom zero;
    EXPECT_EQ(pol.get_monoms().head()->value, zero);
}
TEST(TestPolynomLib, check_multiplication_by_scalar_with_assignment) {
    Polynom p1("3.1x^2y+7.3x^2z^2");
    p1 *= 3.2;
    std::string expected = "9.920000x^2y+23.360000x^2z^2";
    EXPECT_EQ(p1.toString(), expected);
}
TEST(TestPolynomLib, check_division_by_scalar_polynoms) {
    Polynom p1("4.2x^2y+8.6x^2z^2");
    Polynom pol = p1 / 2;
    std::string expected = "2.100000x^2y+4.300000x^2z^2";
    EXPECT_EQ(pol.toString(), expected);
}
TEST(TestPolynomLib, check_division_by_scalar_with_assignment) {
    Polynom p1("4.62x^2y+11.13x^2z^2");
    p1 /= 2.1;
    std::string expected = "2.200000x^2y+5.300000x^2z^2";
    EXPECT_EQ(p1.toString(), expected);
}
TEST(TestPolynomLib, check_exception_division_by_scalar_polynoms) {
    Polynom p1("4.2x^2y+8.6x^2z^2");
    ASSERT_ANY_THROW(p1 / 0.0);
}
TEST(TestPolynomLib, check_unary_minus) {
    Polynom p1("4.62x^2y+11.13x^2z^2-6.76z");
    Polynom p2 = -p1;;
    std::string expected = "-4.620000x^2y-11.130000x^2z^2+6.760000z";
    EXPECT_EQ(p2.toString(), expected);
}
TEST(TestPolynomLib, check_addition_with_a_monom) {
    Polynom p1("4.62x^2y+11.13x^2z^2-6.76z");
    Monom m("7.3y^2");
    Polynom pol = p1 + m;
    std::string expected = "4.620000x^2y+11.130000x^2z^2+7.300000y^2-6.760000z";
    EXPECT_EQ(pol.toString(), expected);
}
TEST(TestPolynomLib, check_addition_with_a_monom2) {
    Polynom p1("4.62x^2y+11.13x^2z^2-6.76z");
    Monom m("7.3y^2");
    Polynom pol = m + p1;
    std::string expected = "4.620000x^2y+11.130000x^2z^2+7.300000y^2-6.760000z";
    EXPECT_EQ(pol.toString(), expected);
}
TEST(TestPolynomLib, check_addition_with_assignment_with_a_monom) {
    Polynom p1("4.62x^2y^2+11.13x^2z^2-6.76z");
    Monom m("7.3x^2y");
    p1 += m;
    std::string expected = "4.620000x^2y^2+7.300000x^2y+11.130000x^2z^2-6.760000z";
    EXPECT_EQ(p1.toString(), expected);
}
TEST(TestPolynomLib, check_subtraction_with_a_monom) {
    Polynom p1("4.62x^2y+11.13x^2z^2-6.76z");
    Monom m("3.3x^2yz^3");
    Polynom pol = p1 - m;
    std::string expected = "-3.300000x^2yz^3+4.620000x^2y+11.130000x^2z^2-6.760000z";
    EXPECT_EQ(pol.toString(), expected);
}
TEST(TestPolynomLib, check_subtraction_with_a_monom2) {
    Polynom p1("4.62x^2y+11.13x^2z^2-6.76z");
    Monom m("3.3x^2yz^3");
    Polynom pol = m - p1;
    std::string expected = "3.300000x^2yz^3-4.620000x^2y-11.130000x^2z^2+6.760000z";
    EXPECT_EQ(pol.toString(), expected);
}
TEST(TestPolynomLib, check_subtraction_with_assignment_with_a_monom) {
    Polynom p1("4.62x^2y^2+11.13x^2z^2-6.76z");
    Monom m("-3.3x^2z^2");
    p1 -= m;
    std::string expected = "4.620000x^2y^2+14.430000x^2z^2-6.760000z";
    EXPECT_EQ(p1.toString(), expected);
}
TEST(TestPolynomLib, check_multiplication_with_a_monom) {
    Polynom p1("4.62x^2y+11.13x^2z^2-6.76z");
    Monom m("3.3x");
    Polynom pol = p1 * m;
    std::string expected = "15.246000x^3y+36.729000x^3z^2-22.308000xz";
    EXPECT_EQ(pol.toString(), expected);
}
TEST(TestPolynomLib, check_multiplication_with_a_monom2) {
    Polynom p1("4.62x^2y+11.13x^2z^2-6.76z");
    Monom m("3.3x");
    Polynom pol = m * p1;
    std::string expected = "15.246000x^3y+36.729000x^3z^2-22.308000xz";
    EXPECT_EQ(pol.toString(), expected);
}
TEST(TestPolynomLib, check_multiplication_with_a_monom3) {
    Polynom p1("4.62x^2y+11.13x^2z^2-6.76z");
    Monom zero;
    Polynom pol = zero * p1;
    EXPECT_EQ(pol.get_monoms().head()->value, zero);
}
TEST(TestPolynomLib, check_multiplication_with_assignment_with_a_monom) {
    Polynom p1("4.62x^2y^2+11.13x^2z^2-6.76z");
    Monom m("-3.3x");
    p1 *= m;
    std::string expected = "-15.246000x^3y^2-36.729000x^3z^2+22.308000xz";
    EXPECT_EQ(p1.toString(), expected);
}
TEST(TestPolynomLib, check_division_with_a_monom) {
    Polynom p1("9.0x^2y+27.0x^2z^2-6.0xz");
    Monom m("3.0x");
    Polynom pol = p1 / m;
    std::string expected = "3.000000xy+9.000000xz^2-2.000000z";
    EXPECT_EQ(pol.toString(), expected);
}
TEST(TestPolynomLib, check_division_with_assignment_with_a_monom) {
    Polynom p1("9.0x^2y+27.0x^2z^2-6.0xz");
    Monom m("-3.0x");
    p1 /= m;
    std::string expected = "-3.000000xy-9.000000xz^2+2.000000z";
    EXPECT_EQ(p1.toString(), expected);
}
TEST(TestPolynomLib, check_exception_division_with_a_monom) {
    Polynom p1("9.0x^2y+27.0x^2z^2-6.0xz");
    Monom m;
    ASSERT_ANY_THROW(p1 / m);
}
TEST(TestPolynomLib, check_equivalent_polynomials) {
    Polynom p1("2.3x^2y+2.5xy^2z^2-7.5z^3");
    Polynom p2("2.3x^2y+2.5xy^2z^2-7.5z^3");
    EXPECT_TRUE(p1 == p2);
    EXPECT_FALSE(p1 != p2);
}
TEST(TestPolynomLib, check_not_equivalent_polynomials) {
    Polynom p1("2.3x^2y+2.5xy^2z^2-7.5z^3");
    Polynom p2("2.3x^2y+2.8xy^2z^2-7.5z^3");
    EXPECT_TRUE(p1 != p2);
    EXPECT_FALSE(p1 == p2);
}
TEST(TestPolynomLib, check_the_comparison_of_polynomials) {
    Polynom p1("2.3x^2y-7.5z^3");
    Polynom p2("2.3x^2y+2.8xy^2z^2-7.5z^3");
    Polynom p3("7.75x^3y^2-8.9y^2");
    EXPECT_TRUE(p1 < p2);
    EXPECT_FALSE(p1 > p2);
    EXPECT_TRUE(p3 > p2);
    EXPECT_FALSE(p3 < p2);
}
TEST(TestPolynomLib, check_assignment) {
    Polynom p1("2.3x^2y-7.5z^3");
    Polynom p2 = p1;
    std::string expected = "2.300000x^2y-7.500000z^3";
    EXPECT_EQ(expected, p2.toString());
}
TEST(TestPolynomLib, check_calculate) {
    Polynom pol("8.45x^2y^3+5.7y^2z^2-7.8z^3");
    EXPECT_NEAR(pol .calculate(2.0, 3.0, 2.5), 1111.35, 1e-2);
}
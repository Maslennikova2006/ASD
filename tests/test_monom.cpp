// Copyright 2026 Mary Maslennikova

#include <gtest/gtest.h>
#include "../lib_monom/monom.h"

TEST(TestMonomLib, can_create) {
    ASSERT_NO_THROW(Monom m);
}
TEST(TestMonomLib, check_default_create) {
    Monom m;
    EXPECT_EQ(0.0, m.get_coeff());
    EXPECT_EQ(0, m.get_powers()[0]);
    EXPECT_EQ(0, m.get_powers()[1]);
    EXPECT_EQ(0, m.get_powers()[2]);
}
TEST(TestMonomLib, can_create_with_params) {
    int powers[3] = { 2, 3, 4 };
    ASSERT_NO_THROW(Monom m(7.8, powers));
}
TEST(TestMonomLib, check_create_with_params) {
    int powers[3] = { 2, 3, 2 };
    Monom m(8.84, powers);
    EXPECT_EQ(8.84, m.get_coeff());
    EXPECT_EQ(2, m.get_powers()[0]);
    EXPECT_EQ(3, m.get_powers()[1]);
    EXPECT_EQ(2, m.get_powers()[2]);
}
TEST(TestMonomLib, check_copy_constructor) {
    Monom m;
    ASSERT_NO_THROW(Monom(m));
}
TEST(TestMonomLib, can_create_copy_constructor) {
    int powers[3] = { 2, 3, 5 };
    Monom m(4.78, powers);
    Monom mon(m);
    EXPECT_EQ(4.78, mon.get_coeff());
    EXPECT_EQ(2, mon.get_powers()[0]);
    EXPECT_EQ(3, mon.get_powers()[1]);
    EXPECT_EQ(5, mon.get_powers()[2]);
}
TEST(TestMonomLib, check_string_constructor) {
    ASSERT_NO_THROW(Monom("2.3x^3y^2z"));
}
TEST(TestMonomLib, check_create_string_constructor) {
    Monom mon("2.3x^3y^2z");
    EXPECT_EQ(2.3, mon.get_coeff());
    EXPECT_EQ(3, mon.get_powers()[0]);
    EXPECT_EQ(2, mon.get_powers()[1]);
    EXPECT_EQ(1, mon.get_powers()[2]);
}
TEST(TestMonomLib, check_addition_monoms) {
    int powers[3] = { 2, 3, 4 };
    Monom m1(7.8, powers);
    Monom m2(6.6, powers);
    Monom m = m1 + m2;
    EXPECT_NEAR(m.get_coeff(), 14.4, 1e-10);
    for (int i = 0; i < VAR_COUNT; i++) {
        EXPECT_EQ(m.get_powers()[i], powers[i]);
    }
}
TEST(TestMonomLib, check_addition_with_assignment) {
    int powers[3] = { 2, 3, 4 };
    Monom m1(7.8, powers);
    Monom m2(87.2, powers);
    m1 += m2;
    EXPECT_NEAR(m1.get_coeff(), 95.0, 1e-10);
    for (int i = 0; i < VAR_COUNT; i++) {
        EXPECT_EQ(m1.get_powers()[i], powers[i]);
    }
}
TEST(TestMonomLib, check_exception_addition_with_assignment) {
    int powers1[3] = { 2, 3, 4 };
    int powers2[3] = { 2, 3, 5 };
    Monom m1(7.8, powers1);
    Monom m2(87.2, powers2);
    ASSERT_ANY_THROW(m1 += m2);
}
TEST(TestMonomLib, check_subtraction_monoms) {
    int powers[3] = { 2, 3, 4 };
    Monom m1(7.8, powers);
    Monom m2(6.6, powers);
    Monom m = m1 - m2;
    EXPECT_NEAR(m.get_coeff(), 1.2, 1e-10);
    for (int i = 0; i < VAR_COUNT; i++) {
        EXPECT_EQ(m.get_powers()[i], powers[i]);
    }
}
TEST(TestMonomLib, check_subtraction_with_assignment) {
    int powers[3] = { 2, 3, 4 };
    Monom m1(7.8, powers);
    Monom m2(87.2, powers);
    m1 -= m2;
    EXPECT_NEAR(m1.get_coeff(), -79.4, 1e-10);
    for (int i = 0; i < VAR_COUNT; i++) {
        EXPECT_EQ(m1.get_powers()[i], powers[i]);
    }
}
TEST(TestMonomLib, check_exception_subtraction_with_assignment) {
    int powers1[3] = { 2, 3, 4 };
    int powers2[3] = { 2, 8, 4 };
    Monom m1(7.8, powers1);
    Monom m2(87.2, powers2);
    ASSERT_ANY_THROW(m1 += m2);
}
TEST(TestMonomLib, check_multiplication_monoms) {
    int powers1[3] = { 2, 3, 4 };
    int powers2[3] = { 2, 5, 1 };
    int powers[3] = { 4, 8, 5 };
    Monom m1(7.8, powers1);
    Monom m2(6.6, powers2);
    Monom m = m1 * m2;
    EXPECT_NEAR(m.get_coeff(), 51.48, 1e-10);
    for (int i = 0; i < VAR_COUNT; i++) {
        EXPECT_EQ(m.get_powers()[i], powers[i]);
    }
}
TEST(TestMonomLib, check_multiplication_with_assignment) {
    int powers1[3] = { 2, 3, 4 };
    int powers2[3] = { 0, 2, 3 };
    int powers[3] = { 2, 5, 7 };
    Monom m1(8.3, powers1);
    Monom m2(5.5, powers2);
    m1 *= m2;
    EXPECT_NEAR(m1.get_coeff(), 45.65, 1e-10);
    for (int i = 0; i < VAR_COUNT; i++) {
        EXPECT_EQ(m1.get_powers()[i], powers[i]);
    }
}
TEST(TestMonomLib, check_division_monoms) {
    int powers1[3] = { 2, 3, 4 };
    int powers2[3] = { 2, 5, 1 };
    int powers[3] = { 0, -2, 3 };
    Monom m1(15.25, powers1);
    Monom m2(5.5, powers2);
    Monom m = m1 / m2;
    EXPECT_NEAR(m.get_coeff(), 2.77, 1e-2);
    for (int i = 0; i < VAR_COUNT; i++) {
        EXPECT_EQ(m.get_powers()[i], powers[i]);
    }
}
TEST(TestMonomLib, check_division_with_assignment) {
    int powers1[3] = { 2, 3, 4 };
    int powers2[3] = { 0, 2, 3 };
    int powers[3] = { 2, 1, 1 };
    Monom m1(42.85, powers1);
    Monom m2(3.25, powers2);
    m1 /= m2;
    EXPECT_NEAR(m1.get_coeff(), 13.18, 1e-2);
    for (int i = 0; i < VAR_COUNT; i++) {
        EXPECT_EQ(m1.get_powers()[i], powers[i]);
    }
}
TEST(TestMonomLib, check_exception_division_monoms) {
    int powers1[3] = { 2, 3, 4 };
    int powers2[3] = { 2, 5, 1 };
    Monom m1(15.25, powers1);
    Monom m2(0.0, powers2);
    EXPECT_ANY_THROW(m1 / m2);
}
TEST(TestMonomLib, check_multiplication_monoms_by_scalar) {
    int powers[3] = { 2, 3, 4 };
    Monom m1(7.8, powers);
    Monom m = m1 * 8.54;
    EXPECT_NEAR(m.get_coeff(), 66.612, 1e-10);
    for (int i = 0; i < VAR_COUNT; i++) {
        EXPECT_EQ(m.get_powers()[i], powers[i]);
    }
}
TEST(TestMonomLib, check_multiplication_monoms_by_scalar2) {
    int powers[3] = { 2, 3, 4 };
    Monom m1(7.8, powers);
    Monom m = 8.54 * m1;
    EXPECT_NEAR(m.get_coeff(), 66.612, 1e-10);
    for (int i = 0; i < VAR_COUNT; i++) {
        EXPECT_EQ(m.get_powers()[i], powers[i]);
    }
}
TEST(TestMonomLib, check_multiplication_by_scalar_with_assignment) {
    int powers[3] = { 2, 5, 7 };
    Monom m1(8.3, powers);
    m1 *= 9.6;
    EXPECT_NEAR(m1.get_coeff(), 79.68, 1e-10);
    for (int i = 0; i < VAR_COUNT; i++) {
        EXPECT_EQ(m1.get_powers()[i], powers[i]);
    }
}
TEST(TestMonomLib, check_division_by_scalar_monoms) {
    int powers[3] = { 0, 2, 3 };
    Monom m1(15.25, powers);
    Monom m = m1 / 5;
    EXPECT_NEAR(m.get_coeff(), 3.05, 1e-10);
    for (int i = 0; i < VAR_COUNT; i++) {
        EXPECT_EQ(m.get_powers()[i], powers[i]);
    }
}
TEST(TestMonomLib, check_division_by_scalar_with_assignment) {
    int powers[3] = { 2, 1, 1 };
    Monom m1(42.85, powers);
    m1 /= 7.3;
    EXPECT_NEAR(m1.get_coeff(), 5, 86, 1e-10);
    for (int i = 0; i < VAR_COUNT; i++) {
        EXPECT_EQ(m1.get_powers()[i], powers[i]);
    }
}
TEST(TestMonomLib, check_unary_minus) {
    int powers[3] = { 2, 1, 1 };
    Monom m1(42.85, powers);
    Monom m2 = -m1;
    EXPECT_NEAR(m2.get_coeff(), -42.85, 1e-10);
    for (int i = 0; i < VAR_COUNT; i++) {
        EXPECT_EQ(m2.get_powers()[i], powers[i]);
    }
}
TEST(TestMonomLib, check_similar_monomes) {
    int powers1[3] = { 2, 1, 1 };
    int powers2[3] = { 2, 1, 1 };
    Monom m1(42.85, powers1);
    Monom m2(6.87, powers2);
    EXPECT_TRUE(m1 == m2);
    EXPECT_FALSE(m1 != m2);
}
TEST(TestMonomLib, check_dissimilar_monomes) {
    int powers1[3] = { 2, 1, 1 };
    int powers2[3] = { 2, 3, 1 };
    Monom m1(42.85, powers1);
    Monom m2(6.87, powers2);
    EXPECT_TRUE(m1 != m2);
    EXPECT_FALSE(m1 == m2);
}
TEST(TestMonomLib, check_the_comparison_of_monomes) {
    int powers1[3] = { 2, 2, 1 };
    int powers2[3] = { 2, 3, 1 };
    int powers3[3] = { 2, 1, 1 };
    Monom m1(42.85, powers1);
    Monom m2(6.87, powers2);
    Monom m3(76.8, powers3);
    EXPECT_TRUE(m1 < m2);
    EXPECT_TRUE(m1 > m3);
    EXPECT_FALSE(m1 > m2);
    EXPECT_FALSE(m2 < m3);
}
TEST(TestMonomLib, check_assignment) {
    int powers1[3] = { 2, 2, 1 };
    Monom m1(42.85, powers1);
    Monom m2 = m1;
    EXPECT_NEAR(m2.get_coeff(), 42.85, 1e-10);
    for (int i = 0; i < VAR_COUNT; i++) {
        EXPECT_EQ(m2.get_powers()[i], powers1[i]);
    }
}
TEST(TestMonomLib, check_parser) {
    Monom m("34.65*x^4*y^2*z");
    int powers[3] = { 4, 2, 1 };
    EXPECT_NEAR(m.get_coeff(), 34.65, 1e-10);
    for (int i = 0; i < VAR_COUNT; i++) {
        EXPECT_EQ(m.get_powers()[i], powers[i]);
    }
}
TEST(TestMonomLib, check_parser2) {
    Monom m("-54.6765x^4*z^2");
    int powers[3] = { 4, 0, 2 };
    EXPECT_NEAR(m.get_coeff(), -54.6765, 1e-10);
    for (int i = 0; i < VAR_COUNT; i++) {
        EXPECT_EQ(m.get_powers()[i], powers[i]);
    }
}
TEST(TestMonomLib, check_calculate) {
    Monom m("8.45x^4y^3z^2");
    EXPECT_NEAR(m.calculate(8.2, 5.3, 2.1), 25082932.92, 1e-2);
}
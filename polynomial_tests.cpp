#include <gtest/gtest.h>
#include <vector>
#include "polynomial.hpp"

TEST (polynomial, empty_constructor) {
    Polynomial pol;
    ASSERT_EQ(pol.degree(), 0);
    ASSERT_EQ(pol.compute(10.213), 0);
    ASSERT_EQ(pol.GetCoefficients(), std::vector<double>());
}

TEST (polynomial, vector_constructor) {
    std::vector<double> c = {1, 2, 3};  // 3x^2 + 2x + 1
    Polynomial pol(c);
    ASSERT_EQ(pol.degree(), 2);
    ASSERT_EQ(pol.compute(1), 6.0);
    ASSERT_EQ(pol.GetCoefficients(), std::vector<double>({1,2,3}));
}

TEST (polynomial, copy_constructor) {
    std::vector<double> c = {1, 2, 3};  // 3x^2 + 2x + 1
    Polynomial pol(c);
    Polynomial pol_copy(pol);
    ASSERT_EQ(pol_copy.degree(), 2);
    ASSERT_EQ(pol_copy.compute(1), 6.0);
    ASSERT_EQ(pol_copy.GetCoefficients(), std::vector<double>({1,2,3}));
}

TEST (polynomial, coefficients_immutable) {
    std::vector<double> c = {1, 2, 3};  // 3x^2 + 2x + 1
    Polynomial pol(c);
    std::vector<double> coofs = pol.GetCoefficients();
    coofs[0] = 100;
    ASSERT_EQ(pol.GetCoefficients(), std::vector<double>({1,2,3}));
}

TEST (polynomial, addition) {
    std::vector<double> c1 = {1, 2, 3};  // 3x^2 + 2x + 1
    std::vector<double> c2 = {4, 5};     // 5x + 4
    Polynomial pol1(c1);
    Polynomial pol2(c2);
    Polynomial sum = pol1 + pol2;         // should be 3x^2 + 7x + 5
    ASSERT_EQ(sum.GetCoefficients(), std::vector<double>({5,7,3}));
    ASSERT_EQ(sum.degree(), 2);
    ASSERT_EQ(sum.compute(1), 15.0);
}

TEST (polynomial, subtraction) {
    std::vector<double> c1 = {1, 2, 3};  // 3x^2 + 2x + 1
    std::vector<double> c2 = {4, 5};     // 5x + 4
    Polynomial pol1(c1);
    Polynomial pol2(c2);
    Polynomial diff = pol1 - pol2;        // should be 3x^2 - 3x - 3
    ASSERT_EQ(diff.GetCoefficients(), std::vector<double>({-3,-3,3}));
    ASSERT_EQ(diff.degree(), 2);
    ASSERT_EQ(diff.compute(1), -3.0);
}

TEST (polynomial, multiplication1) {
    std::vector<double> c1 = {1, 2};     // 2x + 1
    std::vector<double> c2 = {3, 4};     // 4x + 3
    Polynomial pol1(c1);
    Polynomial pol2(c2);
    Polynomial product = pol1 * pol2;     // should be 8x^2 + 10x + 3
    ASSERT_EQ(product.GetCoefficients(), std::vector<double>({3,10,8}));
    ASSERT_EQ(product.degree(), 2);
    ASSERT_EQ(product.compute(1), 21.0);
}

TEST (polynomial, multiplication2) {
    std::vector<double> c1 = {1, 0, -3};  // -3x^2 + 1
    std::vector<double> c2 = {-1};      // -1
    Polynomial pol1(c1);
    Polynomial pol2(c2);
    Polynomial product = pol1 * pol2;      // should be 3x^2 - 1
    ASSERT_EQ(product.GetCoefficients(), std::vector<double>({-1,0,3}));
    ASSERT_EQ(product.degree(), 2);
    ASSERT_EQ(product.compute(1), 2.0);
}

TEST (polynomial, equality) {
    std::vector<double> c1 = {1, 2, 3};  // 3x^2 + 2x + 1
    std::vector<double> c2 = {1, 2, 3};  // 3x^2 + 2x + 1
    std::vector<double> c3 = {4, 5};     // 5x + 4
    Polynomial pol1(c1);
    Polynomial pol2(c2);
    Polynomial pol3(c3);
    ASSERT_TRUE(pol1 == pol2);
    ASSERT_FALSE(pol1 == pol3);
}

TEST (polynomial, inequality) {
    std::vector<double> c1 = {1, 2, 3};  // 3x^2 + 2x + 1
    std::vector<double> c2 = {1, 2, 3};  // 3x^2 + 2x + 1
    std::vector<double> c3 = {4, 5};     // 5x + 4
    Polynomial pol1(c1);
    Polynomial pol2(c2);
    Polynomial pol3(c3);
    ASSERT_FALSE(pol1 != pol2);
    ASSERT_TRUE(pol1 != pol3);
}

TEST (polynomial, ostream) {
    std::vector<double> c = {1, 0, -3};  // -3x^2 + 1
    Polynomial pol(c);
    std::stringstream ss;
    ss << pol;
    ASSERT_EQ(ss.str(), "-3x^2 + 1");
}

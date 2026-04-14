#include <gtest.h>
#include "Header.h"

TEST(MonomTest, Constructor) {
    Monom m;
    EXPECT_EQ(m.degrees, 0);
}
TEST(MonomTest, Constructor2) {
    Monom m(2.5, 123);
    EXPECT_DOUBLE_EQ(m.coefficient, 2.5);
}
TEST(MonomTest, Constructor3) {
    EXPECT_ANY_THROW(Monom m(1.0, 1000));
}
TEST(MonomTest, Constructor4) {
    EXPECT_ANY_THROW(Monom m(1.0, -1));
}
TEST(PolinomTest, Constructor5) {
    Polinom p;
    EXPECT_FALSE(p.NotEmpty());
}

TEST(PolinomTest, AddNewMonom) {
    Polinom p;
    p.add_new_monom(Monom(5.0, 123));
    EXPECT_TRUE(p.NotEmpty());
}
TEST(PolinomTest, AdditionOperator) {
    Polinom p1, p2;
    p1.add_new_monom(Monom(4.0, 123));
    p1.add_new_monom(Monom(3.0, 12));

    p2.add_new_monom(Monom(7.0, 123));
    p2.add_new_monom(Monom(4.0, 12));
    Polinom result = p1 + p2;
    EXPECT_TRUE(result.NotEmpty());
}
TEST(PolinomTest, AdditionOperator2) {
    Polinom empty_p = Polinom();
    Polinom result;
    EXPECT_ANY_THROW(result = result + empty_p);
}

TEST(PolinomTest, SubtractionOperator) {
    Polinom p1, p2;
    p1.add_new_monom(Monom(4.0, 123));
    p1.add_new_monom(Monom(3.0, 12));

    p2.add_new_monom(Monom(7.0, 123));
    p2.add_new_monom(Monom(4.0, 12));
    Polinom result = p1 - p2;
    EXPECT_TRUE(result.NotEmpty());
}
TEST(PolinomTest, SubtractionOperator2) {
    Polinom empty_p = Polinom();
    EXPECT_ANY_THROW(Polinom result = result - empty_p);
}
TEST(PolinomTest, SubtractionOperator3) {
    Polinom p1, p2;
    p1.add_new_monom(Monom(4.0, 123));
    p1.add_new_monom(Monom(3.0, 12));

    p2.add_new_monom(Monom(7.0, 123));
    p2.add_new_monom(Monom(4.0, 12));
    Polinom result = p1 * p2;
    EXPECT_TRUE(result.NotEmpty());
}
TEST(PolinomTest, SubtractionOperator4) {
    Polinom empty_p = Polinom();
    EXPECT_ANY_THROW(Polinom result = result * empty_p);
}

TEST(PolinomTest, SubtractionOperator5) {
    Polinom p1, p2;
    p1.add_new_monom(Monom(1.0, 999));
    p2.add_new_monom(Monom(1.0, 1));
    EXPECT_ANY_THROW(Polinom result = p1 * p2);
}
TEST(MonomTest, ConstructorWithNanInf) {
    EXPECT_ANY_THROW(Monom m(NAN, 123));
}
TEST(MonomTest, ConstructorWithInf2) {
    EXPECT_ANY_THROW(Monom m(INFINITY, 123));

}
TEST(MonomTest, CopyMonom) {
    Monom m1(2.5, 123);
    Monom m2 = m1; 
    EXPECT_EQ(m2.degrees, 123);
}
TEST(MonomTest, CopyMonom2) {
    Monom m1(2.5, 123);
    Monom m2 = m1;
    EXPECT_DOUBLE_EQ(m2.coefficient, 2.5);
}
TEST(PolinomTest, AddMonomCancelOut) {
    Polinom p;
    p.add_new_monom(Monom(5.0, 123));
    p.add_new_monom(Monom(-5.0, 123));
    EXPECT_FALSE(p.NotEmpty()); 
}
TEST(PolinomTest, AdditionOperatorResultEmpty) {
    Polinom p1, p2;
    p1.add_new_monom(Monom(5.0, 123));
    p2.add_new_monom(Monom(-5.0, 123));
    Polinom result = p1 + p2;
    EXPECT_FALSE(result.NotEmpty());
}
TEST(PolinomTest, SubtractionOperatorWithCancellation) {
    Polinom p1, p2;
    p1.add_new_monom(Monom(5.0, 123));
    p1.add_new_monom(Monom(3.0, 12));
    p2.add_new_monom(Monom(5.0, 123));
    p2.add_new_monom(Monom(2.0, 12));
    Polinom result = p1 - p2;
    EXPECT_TRUE(result.NotEmpty());

}
TEST(PolinomTest, MultiplicationByZero) {
    Polinom p1, p2;
    p1.add_new_monom(Monom(2.0, 123));
    EXPECT_ANY_THROW(Polinom result = p1 * p2);
}
TEST(PolinomTest, MyEngIsVeryBad) {
    Polinom p1;
    p1.add_new_monom(Monom(2.0, 123));
    p1.add_new_monom(Monom(3.0, 12));
    p1 = p1; 
    EXPECT_TRUE(p1.NotEmpty()); 
}
TEST(PolinomTest, MaxDegree) {
    Polinom p1, p2;
    p1.add_new_monom(Monom(1.0, 999));
    p2.add_new_monom(Monom(1.0, 999));
    EXPECT_ANY_THROW(Polinom result = p1 * p2); 
}
TEST(PolinomTest, ManyMonomials) {
    Polinom p;
    for (int i = 0; i < 50; i++) {
        p.add_new_monom(Monom(1.0, i));
    }
    EXPECT_TRUE(p.NotEmpty());
}
TEST(PolinomTest, SubtractSelf) {
    Polinom p;
    p.add_new_monom(Monom(2.0, 123));
    Polinom result = p - p;
    EXPECT_FALSE(result.NotEmpty());
}
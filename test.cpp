#include "../polinoms.main/Header.h"
#include "pch.h"
TEST(MonomTest, Constructor) {
  Monom m;
  EXPECT_EQ(m.degrees, 0);
}
TEST(MonomTest, Constructor2) {
  Monom m(2.5, 123);
  EXPECT_DOUBLE_EQ(m.coefficient, 2.5);
}
TEST(MonomTest, Constructor3) { EXPECT_ANY_THROW(Monom m(1.0, 1000)); }
TEST(MonomTest, Constructor4) { EXPECT_ANY_THROW(Monom m(1.0, -1)); }
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
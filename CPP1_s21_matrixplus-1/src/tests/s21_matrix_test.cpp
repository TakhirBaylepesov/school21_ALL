#include <gtest/gtest.h>
#include "../headers/s21_matrix_oop.h"

TEST(S21MatrixTest, DefaultConstructor) {
  S21Matrix m;
  EXPECT_EQ(m(0, 0), 0);
}

TEST(S21MatrixTest, ParameterizedConstructor) {
  S21Matrix m(2, 3);
  EXPECT_EQ(m(1, 2), 0);
}

TEST(S21MatrixTest, CopyConstructor) {
  S21Matrix m1(2, 3);
  m1(1, 2) = 5;
  S21Matrix m2(m1);
  EXPECT_EQ(m2(1, 2), 5);
  EXPECT_EQ(m1, m2);
}

TEST(S21MatrixTest, MoveConstructor) {
  S21Matrix m1(2, 3);
  m1(1, 2) = 5;
  S21Matrix m2(std::move(m1));
  EXPECT_EQ(m2(1, 2), 5);
}

TEST(S21MatrixTest, MoveAssignmentOperator) {
  S21Matrix m1(2, 2);
  m1(0, 0) = 1;
  m1(0, 1) = 2;
  m1(1, 0) = 3;
  m1(1, 1) = 4;

  S21Matrix m2 = std::move(m1);
  EXPECT_EQ(m2(0, 0), 1);
  EXPECT_EQ(m2(0, 1), 2);
  EXPECT_EQ(m2(1, 0), 3);
  EXPECT_EQ(m2(1, 1), 4);
}

TEST(S21MatrixTest, EqualityOperator) {
  S21Matrix m1(2, 2);
  m1(0, 0) = 1;
  m1(0, 1) = 2;
  m1(1, 0) = 3;
  m1(1, 1) = 4;

  S21Matrix m2(2, 2);
  m2(0, 0) = 1;
  m2(0, 1) = 2;
  m2(1, 0) = 3;
  m2(1, 1) = 4;

  EXPECT_EQ(m1, m2);
  m2(1, 1) = 5;
  EXPECT_NE(m1, m2);
}

TEST(S21MatrixTest, Addition) {
  S21Matrix m1(2, 2);
  m1(0, 0) = 1;
  m1(0, 1) = 2;
  m1(1, 0) = 3;
  m1(1, 1) = 4;

  S21Matrix m2(2, 2);
  m2(0, 0) = 5;
  m2(0, 1) = 6;
  m2(1, 0) = 7;
  m2(1, 1) = 8;

  S21Matrix result = m1 + m2;
  EXPECT_EQ(result(0, 0), 6);
  EXPECT_EQ(result(0, 1), 8);
  EXPECT_EQ(result(1, 0), 10);
  EXPECT_EQ(result(1, 1), 12);
}

TEST(S21MatrixTest, Subtraction) {
  S21Matrix m1(2, 2);
  m1(0, 0) = 1;
  m1(0, 1) = 2;
  m1(1, 0) = 3;
  m1(1, 1) = 4;

  S21Matrix m2(2, 2);
  m2(0, 0) = 5;
  m2(0, 1) = 6;
  m2(1, 0) = 7;
  m2(1, 1) = 8;

  S21Matrix result = m1 - m2;
  EXPECT_EQ(result(0, 0), -4);
  EXPECT_EQ(result(0, 1), -4);
  EXPECT_EQ(result(1, 0), -4);
  EXPECT_EQ(result(1, 1), -4);
}

TEST(S21MatrixTest, MultiplyByNumber) {
  S21Matrix m1(2, 2);
  m1(0, 0) = 1;
  m1(0, 1) = 2;
  m1(1, 0) = 3;
  m1(1, 1) = 4;

  S21Matrix result = m1 * 2.0;
  EXPECT_EQ(result(0, 0), 2);
  EXPECT_EQ(result(0, 1), 4);
  EXPECT_EQ(result(1, 0), 6);
  EXPECT_EQ(result(1, 1), 8);
}

TEST(S21MatrixTest, MatrixMultiplication) {
  S21Matrix m1(2, 2);
  m1(0, 0) = 1;
  m1(0, 1) = 2;
  m1(1, 0) = 3;
  m1(1, 1) = 4;

  S21Matrix m2(2, 2);
  m2(0, 0) = 5;
  m2(0, 1) = 6;
  m2(1, 0) = 7;
  m2(1, 1) = 8;

  S21Matrix result = m1 * m2;
  EXPECT_EQ(result(0, 0), 19);
  EXPECT_EQ(result(0, 1), 22);
  EXPECT_EQ(result(1, 0), 43);
  EXPECT_EQ(result(1, 1), 50);
}

TEST(S21MatrixTest, Transpose) {
  S21Matrix m1(2, 3);
  m1(0, 0) = 1;
  m1(0, 1) = 2;
  m1(0, 2) = 3;
  m1(1, 0) = 4;
  m1(1, 1) = 5;
  m1(1, 2) = 6;

  S21Matrix result = m1.Transpose();
  EXPECT_EQ(result(0, 0), 1);
  EXPECT_EQ(result(1, 0), 2);
  EXPECT_EQ(result(2, 0), 3);
  EXPECT_EQ(result(0, 1), 4);
  EXPECT_EQ(result(1, 1), 5);
  EXPECT_EQ(result(2, 1), 6);
}

TEST(S21MatrixTest, Determinant) {
  S21Matrix m1(2, 2);
  m1(0, 0) = 1;
  m1(0, 1) = 2;
  m1(1, 0) = 3;
  m1(1, 1) = 4;
  EXPECT_EQ(m1.Determinant(), -2);

  S21Matrix m2(3, 3);
  m2(0, 0) = 6;
  m2(0, 1) = 1;
  m2(0, 2) = 1;
  m2(1, 0) = 4;
  m2(1, 1) = -2;
  m2(1, 2) = 5;
  m2(2, 0) = 2;
  m2(2, 1) = 8;
  m2(2, 2) = 7;
  EXPECT_EQ(m2.Determinant(), -306);
}

TEST(S21MatrixTest, InverseMatrix) {
  S21Matrix m1(2, 2);
  m1(0, 0) = 4;
  m1(0, 1) = 7;
  m1(1, 0) = 2;
  m1(1, 1) = 6;

  S21Matrix inv = m1.InverseMatrix();
  EXPECT_DOUBLE_EQ(inv(0, 0), 0.6);
  EXPECT_DOUBLE_EQ(inv(0, 1), -0.7);
  EXPECT_DOUBLE_EQ(inv(1, 0), -0.2);
  EXPECT_DOUBLE_EQ(inv(1, 1), 0.4);
}

TEST(S21MatrixTest, OperatorPlusEqual) {
  S21Matrix m1(2, 2);
  m1(0, 0) = 1;
  m1(0, 1) = 2;
  m1(1, 0) = 3;
  m1(1, 1) = 4;

  S21Matrix m2(2, 2);
  m2(0, 0) = 5;
  m2(0, 1) = 6;
  m2(1, 0) = 7;
  m2(1, 1) = 8;

  m1 += m2;
  EXPECT_EQ(m1(0, 0), 6);
  EXPECT_EQ(m1(0, 1), 8);
  EXPECT_EQ(m1(1, 0), 10);
  EXPECT_EQ(m1(1, 1), 12);
}

TEST(S21MatrixTest, OperatorMinusEqual) {
  S21Matrix m1(2, 2);
  m1(0, 0) = 1;
  m1(0, 1) = 2;
  m1(1, 0) = 3;
  m1(1, 1) = 4;

  S21Matrix m2(2, 2);
  m2(0, 0) = 5;
  m2(0, 1) = 6;
  m2(1, 0) = 7;
  m2(1, 1) = 8;

  m1 -= m2;
  EXPECT_EQ(m1(0, 0), -4);
  EXPECT_EQ(m1(0, 1), -4);
  EXPECT_EQ(m1(1, 0), -4);
  EXPECT_EQ(m1(1, 1), -4);
}

TEST(S21MatrixTest, OperatorMultiplyEqualMatrix) {
  S21Matrix m1(2, 2);
  m1(0, 0) = 1;
  m1(0, 1) = 2;
  m1(1, 0) = 3;
  m1(1, 1) = 4;

  S21Matrix m2(2, 2);
  m2(0, 0) = 5;
  m2(0, 1) = 6;
  m2(1, 0) = 7;
  m2(1, 1) = 8;

  m1 *= m2;
  EXPECT_EQ(m1(0, 0), 19);
  EXPECT_EQ(m1(0, 1), 22);
  EXPECT_EQ(m1(1, 0), 43);
  EXPECT_EQ(m1(1, 1), 50);
}

TEST(S21MatrixTest, OperatorMultiplyEqualScalar) {
  S21Matrix m1(2, 2);
  m1(0, 0) = 1;
  m1(0, 1) = 2;
  m1(1, 0) = 3;
  m1(1, 1) = 4;

  double scalar = 2.0;
  m1 *= scalar;
  EXPECT_EQ(m1(0, 0), 2);
  EXPECT_EQ(m1(0, 1), 4);
  EXPECT_EQ(m1(1, 0), 6);
  EXPECT_EQ(m1(1, 1), 8);
}

TEST(S21MatrixTest, NonConstOutOfRange) {
  S21Matrix m(2, 2);
  try {
    m(2, 2);
    FAIL() << "Expected std::out_of_range exception";
  } catch (const std::out_of_range& e) {
    SUCCEED();
  } catch (...) {
    FAIL() << "Expected std::out_of_range exception, but caught different "
              "exception";
  }
}

TEST(S21MatrixTest, ConstOutOfRange) {
  const S21Matrix m(2, 2);
  try {
    m(2, 2);
    FAIL() << "Expected std::out_of_range exception";
  } catch (const std::out_of_range& e) {
    SUCCEED();
  } catch (...) {
    FAIL() << "Expected std::out_of_range exception, but caught different "
              "exception";
  }
}

TEST(S21MatrixTest, NonConstOperatorAccess) {
  S21Matrix m(3, 3);
  m(0, 0) = 1.0;
  EXPECT_EQ(m(0, 0), 1.0);
}

TEST(S21MatrixTest, ConstOperatorAccess) {
  const S21Matrix m(3, 3);
  EXPECT_EQ(m(0, 0), 0.0);
}

TEST(S21MatrixTest, NonConstOperatorOutOfRange) {
  S21Matrix m(2, 2);
  try {
    m(2, 2);
    FAIL() << "Expected std::out_of_range exception";
  } catch (const std::out_of_range& e) {
    SUCCEED();
  } catch (...) {
    FAIL() << "Expected std::out_of_range exception, but caught different "
              "exception";
  }
}

TEST(S21MatrixTest, ConstOperatorOutOfRange) {
  const S21Matrix m(2, 2);
  try {
    m(2, 2);
    FAIL() << "Expected std::out_of_range exception";
  } catch (const std::out_of_range& e) {
    SUCCEED();
  } catch (...) {
    FAIL() << "Expected std::out_of_range exception, but caught different "
              "exception";
  }
}

TEST(S21MatrixTest, InverseMatrixSingular) {
  S21Matrix m(2, 2);
  m(0, 0) = 1;
  m(0, 1) = 2;
  m(1, 0) = 2;
  m(1, 1) = 4;

  try {
    m.InverseMatrix();
    FAIL() << "Expected std::invalid_argument exception";
  } catch (const std::invalid_argument& e) {
    EXPECT_EQ(std::string(e.what()),
              "Matrix is singular and cannot be inverted");
  } catch (...) {
    FAIL() << "Expected std::invalid_argument exception, but caught different "
              "exception";
  }
}

TEST(S21MatrixTest, CalcComplementsNonSquare) {
  S21Matrix m(2, 3);

  try {
    m.CalcComplements();
    FAIL() << "Expected std::invalid_argument exception";
  } catch (const std::invalid_argument& e) {
    EXPECT_EQ(std::string(e.what()), "Matrix must be square");
  } catch (...) {
    FAIL() << "Expected std::invalid_argument exception, but caught different "
              "exception";
  }
}

TEST(S21MatrixTest, DeterminantNonSquare) {
  S21Matrix m(2, 3);

  try {
    m.Determinant();
    FAIL() << "Expected std::invalid_argument exception";
  } catch (const std::invalid_argument& e) {
    EXPECT_EQ(std::string(e.what()), "Matrix must be square");
  } catch (...) {
    FAIL() << "Expected std::invalid_argument exception, but caught different "
              "exception";
  }
}

TEST(S21MatrixTest, SumMatrixInvalidArgument) {
  S21Matrix m1(2, 3);
  S21Matrix m2(3, 2); 

  try {
    m1.SumMatrix(m2);
    FAIL() << "Expected std::invalid_argument exception";
  } catch (const std::invalid_argument& e) {
    EXPECT_EQ(std::string(e.what()), "Matrices dimensions must be equal");
  } catch (...) {
    FAIL() << "Expected std::invalid_argument exception, but caught different "
              "exception";
  }
}

TEST(S21MatrixTest, SubMatrixInvalidArgument) {
  S21Matrix m1(2, 3);
  S21Matrix m2(3, 2);

  try {
    m1.SubMatrix(m2);
    FAIL() << "Expected std::invalid_argument exception";
  } catch (const std::invalid_argument& e) {
    EXPECT_EQ(std::string(e.what()), "Matrices dimensions must be equal");
  } catch (...) {
    FAIL() << "Expected std::invalid_argument exception, but caught different "
              "exception";
  }
}

TEST(S21MatrixTest, MulMatrixInvalidArgument) {
  S21Matrix m1(2, 3);
  S21Matrix m2(4, 2);

  try {
    m1.MulMatrix(m2);
    FAIL() << "Expected std::invalid_argument exception";
  } catch (const std::invalid_argument& e) {
    EXPECT_EQ(std::string(e.what()),
              "First matrix columns must be equal to second matrix rows");
  } catch (...) {
    FAIL() << "Expected std::invalid_argument exception, but caught different "
              "exception";
  }
}

TEST(S21MatrixTest, AllocateMatrixInvalidArgument) {
  try {
    S21Matrix m(-1, 3);
    FAIL() << "Expected std::invalid_argument exception";
  } catch (const std::invalid_argument& e) {
    EXPECT_EQ(std::string(e.what()),
              "Number of rows and columns must be positive");
  } catch (...) {
    FAIL() << "Expected std::invalid_argument exception, but caught different "
              "exception";
  }

  try {
    S21Matrix m(3, -1);
    FAIL() << "Expected std::invalid_argument exception";
  } catch (const std::invalid_argument& e) {
    EXPECT_EQ(std::string(e.what()),
              "Number of rows and columns must be positive");
  } catch (...) {
    FAIL() << "Expected std::invalid_argument exception, but caught different "
              "exception";
  }
}

TEST(S21MatrixTest, DeallocateMatrixNoException) {
  try {
    S21Matrix m(2, 3);
    m.deallocateMatrix();
  } catch (...) {
    FAIL() << "Expected no exception, but caught an exception";
  }
}

TEST(S21MatrixTest, DestructorDeallocateMatrixNoException) {
  try {
    S21Matrix* m = new S21Matrix(2, 3);
    delete m;
  } catch (...) {
    FAIL() << "Expected no exception, but caught an exception";
  }
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
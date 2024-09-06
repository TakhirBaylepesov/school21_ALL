#ifndef S21_MATRIX_OOP_H
#define S21_MATRIX_OOP_H

#include <stdlib.h>

#include <cmath>
#include <cstring>
#include <iostream>

class S21Matrix {
 private:
  int cols_, rows_;
  double** matrix_;

 public:
  void allocateMatrix();
  void deallocateMatrix();

 public:
  S21Matrix();
  S21Matrix(int rows, int cols);
  S21Matrix(const S21Matrix& other);
  S21Matrix(S21Matrix&& other) noexcept;
  ~S21Matrix();
  S21Matrix& operator=(S21Matrix&& other) noexcept;

  bool EqMatrix(const S21Matrix& other) const;
  void SumMatrix(const S21Matrix& other);
  void SubMatrix(const S21Matrix& other);
  void MulNumber(const double num);
  void MulMatrix(const S21Matrix& other);
  S21Matrix Transpose() const;
  double Determinant() const;
  S21Matrix Minor(int row, int col) const;
  S21Matrix CalcComplements() const;
  S21Matrix InverseMatrix() const;

  S21Matrix& operator+=(const S21Matrix& rhs);
  S21Matrix& operator-=(const S21Matrix& rhs);
  S21Matrix& operator*=(const S21Matrix& rhs);
  S21Matrix& operator*=(double rhs);
  S21Matrix operator+(const S21Matrix& rhs) const;
  S21Matrix operator-(const S21Matrix& rhs) const;
  S21Matrix operator*(const S21Matrix& rhs) const;
  S21Matrix operator*(double rhs) const;
  bool operator==(const S21Matrix& rhs) const;
  bool operator!=(const S21Matrix& rhs) const;
  double& operator()(int i, int j);
  const double& operator()(int i, int j) const;
};

#endif

#include "../headers/s21_matrix_oop.h"

void S21Matrix::allocateMatrix() {
  if (rows_ <= 0 || cols_ <= 0) {
    throw std::invalid_argument("Number of rows and columns must be positive");
  }
  matrix_ = new double*[rows_];
  for (int i = 0; i < rows_; ++i) {
    matrix_[i] = new double[cols_]{};
  }
}

void S21Matrix::deallocateMatrix() {
  if (matrix_ != nullptr) {
    for (int i = 0; i < rows_; ++i) {
      delete[] matrix_[i];
    }
    delete[] matrix_;
    matrix_ = nullptr;
  }
}

S21Matrix::~S21Matrix() { deallocateMatrix(); }

S21Matrix::S21Matrix() : cols_(1), rows_(1) { allocateMatrix(); }

S21Matrix::S21Matrix(int rows, int cols) : cols_(cols), rows_(rows) {
  allocateMatrix();
}

S21Matrix::S21Matrix(const S21Matrix& other)
    : cols_(other.cols_), rows_(other.rows_) {
  allocateMatrix();
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] = other.matrix_[i][j];
    }
  }
}

S21Matrix::S21Matrix(S21Matrix&& other) noexcept
    : cols_(other.cols_), rows_(other.rows_), matrix_(other.matrix_) {
  other.cols_ = 0;
  other.rows_ = 0;
  other.matrix_ = nullptr;
}

S21Matrix& S21Matrix::operator=(S21Matrix&& other) noexcept {
  if (this != &other) {
    deallocateMatrix();
    cols_ = other.cols_;
    rows_ = other.rows_;
    matrix_ = other.matrix_;
    other.cols_ = 0;
    other.rows_ = 0;
    other.matrix_ = nullptr;
  }
  return *this;
}

bool S21Matrix::EqMatrix(const S21Matrix& other) const {
  if (cols_ != other.cols_ || rows_ != other.rows_) {
    return false;
  }
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      if (matrix_[i][j] != other.matrix_[i][j]) {
        return false;
      }
    }
  }
  return true;
}

void S21Matrix::SumMatrix(const S21Matrix& other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::invalid_argument("Matrices dimensions must be equal");
  }
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] += other.matrix_[i][j];
    }
  }
}

void S21Matrix::SubMatrix(const S21Matrix& other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::invalid_argument("Matrices dimensions must be equal");
  }
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] -= other.matrix_[i][j];
    }
  }
}

void S21Matrix::MulNumber(const double num) {
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] *= num;
    }
  }
}

void S21Matrix::MulMatrix(const S21Matrix& other) {
  if (cols_ != other.rows_) {
    throw std::invalid_argument(
        "First matrix columns must be equal to second matrix rows");
  }
  S21Matrix result(rows_, other.cols_);
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < other.cols_; ++j) {
      for (int k = 0; k < cols_; ++k) {
        result.matrix_[i][j] += matrix_[i][k] * other.matrix_[k][j];
      }
    }
  }
  *this = std::move(result);
}

S21Matrix S21Matrix::Transpose() const {
  S21Matrix result(cols_, rows_);
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      result.matrix_[j][i] = matrix_[i][j];
    }
  }
  return result;
}

double S21Matrix::Determinant() const {
  if (cols_ != rows_) {
    throw std::invalid_argument("Matrix must be square");
  }
  if (rows_ == 2) {
    return (matrix_[0][0] * matrix_[1][1] - matrix_[1][0] * matrix_[0][1]);
  }
  if (rows_ == 1) {
    return matrix_[0][0];
  }
  double det = 0.0;
  for (int i = 0; i < rows_; ++i) {
    S21Matrix minor = Minor(0, i);
    det += (i % 2 == 0 ? 1 : -1) * matrix_[0][i] * minor.Determinant();
  }
  return det;
}

S21Matrix S21Matrix::Minor(int row, int col) const {
  S21Matrix minor(rows_ - 1, cols_ - 1);
  for (int i = 0, mi = 0; i < rows_; ++i) {
    if (i == row) continue;
    for (int j = 0, mj = 0; j < cols_; ++j) {
      if (j == col) continue;
      minor.matrix_[mi][mj] = matrix_[i][j];
      ++mj;
    }
    ++mi;
  }
  return minor;
}

S21Matrix S21Matrix::CalcComplements() const {
  if (cols_ != rows_) {
    throw std::invalid_argument("Matrix must be square");
  }
  S21Matrix complement(rows_, cols_);
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      S21Matrix minor = Minor(i, j);
      complement.matrix_[i][j] =
          ((i + j) % 2 == 0 ? 1 : -1) * minor.Determinant();
    }
  }
  return complement;
}

S21Matrix S21Matrix::InverseMatrix() const {
  double det = Determinant();
  if (det == 0) {
    throw std::invalid_argument("Matrix is singular and cannot be inverted");
  }
  S21Matrix inverse = CalcComplements().Transpose();
  inverse.MulNumber(1.0 / det);
  return inverse;
}

S21Matrix& S21Matrix::operator+=(const S21Matrix& rhs) {
  SumMatrix(rhs);
  return *this;
}

S21Matrix& S21Matrix::operator-=(const S21Matrix& rhs) {
  SubMatrix(rhs);
  return *this;
}

S21Matrix& S21Matrix::operator*=(const S21Matrix& rhs) {
  MulMatrix(rhs);
  return *this;
}

S21Matrix& S21Matrix::operator*=(double rhs) {
  MulNumber(rhs);
  return *this;
}

S21Matrix S21Matrix::operator+(const S21Matrix& rhs) const {
  S21Matrix result(*this);
  result += rhs;
  return result;
}

S21Matrix S21Matrix::operator-(const S21Matrix& rhs) const {
  S21Matrix result(*this);
  result -= rhs;
  return result;
}

S21Matrix S21Matrix::operator*(const S21Matrix& rhs) const {
  S21Matrix result(*this);
  result *= rhs;
  return result;
}

S21Matrix S21Matrix::operator*(double rhs) const {
  S21Matrix result(*this);
  result *= rhs;
  return result;
}

bool S21Matrix::operator==(const S21Matrix& rhs) const { return EqMatrix(rhs); }

bool S21Matrix::operator!=(const S21Matrix& rhs) const {
  return !EqMatrix(rhs);
}

double& S21Matrix::operator()(int i, int j) {
  if (i < 0 || i >= rows_ || j < 0 || j >= cols_) {
    throw std::out_of_range("Matrix index out of range");
  }
  return matrix_[i][j];
}

const double& S21Matrix::operator()(int i, int j) const {
  if (i < 0 || i >= rows_ || j < 0 || j >= cols_) {
    throw std::out_of_range("Matrix index out of range");
  }
  return matrix_[i][j];
}
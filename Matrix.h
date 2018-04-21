#pragma once

#include <iomanip>
#include <iostream>
#include <ostream>
#include <vector>

template <class T>
class Matrix {
protected:
	std::vector<std::vector<T>> v;
public:
	Matrix();
	Matrix(const size_t& rows, const size_t& columns);
	Matrix(const std::vector<std::vector<T>>& v);

	size_t rows() const;
	size_t columns() const;

	std::vector<T> row(const size_t& which) const;
	std::vector<T> column(const size_t& which) const;

	T get(const size_t& row, const size_t& column) const;
	void set(const size_t& row, const size_t& column, const T& value);

	void multiplyBy(const T& value);
	void multiplyBy(const Matrix& matrix);

	Matrix operator*(const T& value) const;
	Matrix operator*(const Matrix& matrix) const;

	friend std::ostream& operator<<(std::ostream& stream, const Matrix& matrix);
};
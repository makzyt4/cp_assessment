#include "Matrix.h"

template<class T>
Matrix<T>::Matrix() 
	: Matrix(0, 0) {}

template<class T>
Matrix<T>::Matrix(const size_t & rows, const size_t & columns) {
	for (size_t i = 0; i < rows; i++) {
		std::vector<T> tmp;
		for (size_t j = 0; j < columns; j++) {
			tmp.push_back(T(0));
		}
		v.push_back(tmp);
	}
}

template<class T>
Matrix<T>::Matrix(const std::vector<std::vector<T>>& v) {
	this->v = v;
}

template<class T>
size_t Matrix<T>::rows() const {
	return v.size();
}

template<class T>
size_t Matrix<T>::columns() const {
	return v.at(0).size();
}

template<class T>
std::vector<T> Matrix<T>::row(const size_t & which) const {
	return v.at(which);
}

template<class T>
std::vector<T> Matrix<T>::column(const size_t & which) const {
	std::vector<T> v2;

	for (size_t i = 0; i < rows(); i++) {
		v2.push_back(v.at(i).at(which));
	}

	return v2;
}

template<class T>
T Matrix<T>::get(const size_t & row, const size_t & column) const {
	return v.at(row).at(column);
}

template<class T>
void Matrix<T>::set(const size_t & row, const size_t & column, const T & value) {
	v.at(row).at(column) = value;
}

template<class T>
void Matrix<T>::multiplyBy(const T & value) {
#pragma omp parallel for default(none)
	for (int i = 0; i < rows(); i++) {
#pragma omp parallel for default(none)
		for (int j = 0; j < columns(); j++) {
			v.at(i).at(j) *= value;
		}
	}
}

template<class T>
void Matrix<T>::multiplyBy(const Matrix & matrix) {
	if (columns() != matrix.rows()) {
		throw std::invalid_argument("The second dimention of matrix A is not equal to the first dimention of matrix B.");
	}

	Matrix mat(rows(), matrix.columns());
#pragma omp parallel for default(none)
	for (int i = 0; i < mat.rows(); i++) {
#pragma omp parallel for default(none)
		for (int j = 0; j < mat.columns(); j++) {
			T sum = T(0);

#pragma omp parallel for default(none) reduction(+:sum)
			for (int k = 0; k < columns(); k++) {
				sum += get(i, k) * matrix.get(k, j);
			}

			mat.set(i, j, sum);
		}
	}

	this->v = mat.v;
}

template<class T>
Matrix Matrix<T>::operator*(const T & value) const {
	Matrix mat(this->v);
	mat.multiplyBy(value);
	return mat;
}

template<class T>
Matrix Matrix<T>::operator*(const Matrix& matrix) const {
	Matrix mat(this->v);
	mat.multiplyBy(matrix);
	return mat;
}

template<class T>
std::ostream & operator<<(std::ostream & stream, const Matrix & matrix) {
	for (size_t i = 0; i < matrix.rows(); i++) {
		for (size_t j = 0; j < matrix.columns(); j++) {
			stream << std::left << std::setw(10) << matrix.v.at(i).at(j);
		}
		stream << std::endl;
	}
	return stream;
}

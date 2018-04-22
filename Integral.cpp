#include "Integral.h"

Integral::Integral(std::function<double(double x, int k)> f, double x1, double x2, double e) {
	this->f = f;
	this->x1 = x1;
	this->x2 = x2;
	this->e = e;
}

double Integral::calc(int k) {
	double result = 0.0;
	const int N = abs(x2 - x1) / e;

#pragma omp parallel for default(none) reduction(+:result)
	for (int i = 1; i <= N; i++) {
		double x = i * e;
		result += f(x, k) * e;
	}

	return result;
}
#include "DoubleIntegral.h"

DoubleIntegral::DoubleIntegral(std::function<double(double x, double y)> f, double x1, double x2, double y1, double y2, double e) {
	this->f = f;
	this->x1 = x1;
	this->x2 = x2;
	this->y1 = y1;
	this->y2 = y2;
	this->e = e;
}

double DoubleIntegral::calc() {
	double result = 0.0;
	const int N1 = abs(x2 - x1) / e;
	const int N2 = abs(y2 - y1) / e;

#pragma omp parallel for default(none) shared(N1, N2)
	for (int i = 1; i <= N1; i++) {
		double x = i * e;

#pragma omp parallel for default(none) reduction(+:result)
		for (int j = 1; j < N2; j++) {
			double y = j * e;

			result += f(x, y) * e;
		}
	}

	return result * e;
}
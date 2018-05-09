#pragma once
#include <cmath>
#include <omp.h>
#include <sstream>
#include <iostream>
#include <functional>

#define M_PI 3.14159265358979323846
#define M_E  2.71828182845904523536

class Integral {
private:
	double x1, x2;
	double e;

protected:
	std::function<double(double x, double y)> f;

public:
	Integral(std::function<double(double x, int k)> f, double x1, double x2, double e);

	double calcN(int k);
	double calcC(int k);
};
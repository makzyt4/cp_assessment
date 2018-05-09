#pragma once

#include <functional>

class DoubleIntegral {
private:
	double x1, x2;
	double y1, y2;
	double e;

protected:
	std::function<double(double x, double y)> f;

public:
	DoubleIntegral(std::function<double(double x, double y)> f, double x1, double x2, double y1, double y2, double e);

	double calcN();
	double calcC();
};

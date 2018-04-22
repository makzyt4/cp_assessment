#include "Matrix.h"
#include "Integral.h"
#include "DoubleIntegral.h"
#include <conio.h>
#include <sstream>

#define K_START 1
#define K_END   100

void task1() {
	for (int k = K_START; k <= K_END; k++) {
		std::stringstream ss;
		Integral integ([](double x, int k) -> double {
			return cos(0.01 * k * x) / (k + x);
		}, 0, 2 * M_PI, 0.0001);
		ss << "calka(" << k << ") = " << integ.calc(k) << std::endl;
		std::cout << ss.str();
	}
}

void task2() {
	DoubleIntegral in([](double x, double y) -> double {
		return log(1 + pow(M_E, -(pow(x, 2) + pow(y, 2))));
	}, 0, 2, 0, 2, 0.001);
	std::cout << in.calc() << std::endl;
}

int main() {
	//task1();
	task2();

	_getch();
	return 0;
}
#include "Matrix.h"
#include "Integral.h"
#include <conio.h>
#include <sstream>

#define K_START 1
#define K_END   100

int main() {
	for (int k = K_START; k <= K_END; k++) {
		std::stringstream ss;
		Integral integ([](double x, int k) -> double {
			return cos(0.01 * k * x) / (k + x);
		}, 0, 2 * M_PI, 0.0001);
		ss << "calka(" << k << ") = " << integ.calc(k) << std::endl;
		std::cout << ss.str();
	}

	_getch();
	return 0;
}
#include "Matrix.h"
#include <conio.h>

int main() {
	Matrix<int> m({
		{5, 2 ,1},
		{1, 2, 3},
		{0, 2, 8}
	});

	std::cout << m * 5 << std::endl;

	_getch();
	return 0;
}
#include "Matrix.h"
#include "Integral.h"
#include "DoubleIntegral.h"
#include <conio.h>
#include <sstream>

#define K_START 1
#define K_END   100
#define MATRIX_SIZE 750

void task1() {
	clock_t measured;
	
	measured = clock();

//#pragma omp parallel for default(none)
	for (int k = K_START; k <= K_END; k++) {
		std::stringstream ss;
		Integral integ([](double x, int k) -> double {
			return cos(0.01 * k * x) / (k + x);
		}, 0, 2 * M_PI, 0.0001);
		ss << "calka(" << k << ") = " << integ.calcC(k) << std::endl;
		//std::cout << ss.str();
	}

	std::cout << "W :: Calka pojedyncza dla k = <1,100>: " << (double)(clock() - measured) / CLOCKS_PER_SEC << " s" << std::endl;

	measured = clock();

	for (int k = K_START; k <= K_END; k++) {
		std::stringstream ss;
		Integral integ([](double x, int k) -> double {
			return cos(0.01 * k * x) / (k + x);
		}, 0, 2 * M_PI, 0.0001);
		ss << "calka(" << k << ") = " << integ.calcN(k) << std::endl;
		//std::cout << ss.str();
	}

	std::cout << "S :: Calka pojedyncza dla k = <1,100>: " << (double)(clock() - measured) / CLOCKS_PER_SEC << " s" << std::endl;
}

void task2() {
	clock_t measured;

	measured = clock();

	DoubleIntegral in([](double x, double y) -> double {
		return log(1 + pow(M_E, -(pow(x, 2) + pow(y, 2))));
	}, 0, 2, 0, 2, 0.001);
	in.calcC();

	std::cout << "W :: Calka podwojna: " << (double)(clock() - measured) / CLOCKS_PER_SEC << " s" << std::endl;

	measured = clock();

	DoubleIntegral in2([](double x, double y) -> double {
		return log(1 + pow(M_E, -(pow(x, 2) + pow(y, 2))));
	}, 0, 2, 0, 2, 0.001);
	in2.calcN();

	std::cout << "S :: Calka podwojna: " << (double)(clock() - measured) / CLOCKS_PER_SEC << " s" << std::endl;
}

void task3() {
	clock_t measured;

	omp_set_nested(64);
	srand(time(NULL));

	std::vector<std::vector<int>> v1, v2;

	std::cout << "Generowanie macierzy...";

	for (int i = 0; i < MATRIX_SIZE; i++) {
		std::vector<int> tmp1, tmp2;

		for (int j = 0; j < MATRIX_SIZE; j++) {
			tmp1.push_back(rand() % 5);
			tmp2.push_back(rand() % 5);
		}

		v1.push_back(tmp1);
		v2.push_back(tmp2);
	}

	Matrix<int> mat1A(v1);
	Matrix<int> mat2A(v2);

	Matrix<int> mat1B(v1);
	Matrix<int> mat2B(v2);

	std::cout << " zakonczono.\n";

	measured = clock();
	mat1A.multiplyByC(mat2A);
	std::cout << "W :: Mnozenie macierzy przez macierz: " << (double)(clock() - measured) / CLOCKS_PER_SEC << " s" << std::endl;

	measured = clock();
	mat1A.multiplyByC(5);
	std::cout << "W :: Mnozenie macierzy przez wektor: " << (double)(clock() - measured) / CLOCKS_PER_SEC << " s" << std::endl;

	measured = clock();
	mat1B.multiplyByN(mat2B);
	std::cout << "S :: Mnozenie macierzy przez macierz: " << (double)(clock() - measured) / CLOCKS_PER_SEC << " s" << std::endl;

	measured = clock();
	mat1B.multiplyByN(5);
	std::cout << "S :: Mnozenie macierzy przez wektor: " << (double)(clock() - measured) / CLOCKS_PER_SEC << " s" << std::endl;
}

int main() {
	std::cout << "((ZADANIE 1))" << std::endl;
	task1();

	std::cout << "((ZADANIE 2))" << std::endl;
	task2();

	std::cout << "((ZADANIE 3))" << std::endl;
	task3();

	std::cout << "\nKoniec. Nacisnij dowolny przycisk by wyjsc z programu..." << std::endl;
	_getch();
	
	return 0;
}
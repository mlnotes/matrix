#include <iostream>
#include "matrix.h"
#include <stdlib.h>
#include <time.h>

void mvector_test(){
	mvector m1(2);
	m1[0] = 1.0;
	m1[1] = 0.0;

	mvector m2 = m1;
	m2[1] = 1;

	mvector m = m1 +  m2;
	mvector mm = m1 - m2;

	std::cout << m1 << '\n';
	std::cout << m2 << '\n';
	std::cout << m << '\n';
	std::cout << mm << '\n';
	std::cout << cos(m1,m2) << '\n';
}

void matrix_test(){
	matrix m(3, 4);
	for(uint i = 0; i < 3; ++i)
		for(uint j = 0; j < 4; ++j)
			m[i][j] = (i+1) * (j+1);

	matrix m1(4, 7);
	for(uint i = 0; i < 4; ++i)
		for(uint j = 0; j < 7; ++j)
			m1[i][j] = (i+1) * (j+1);

	matrix mr = m * m1;
	matrix *pm = new matrix[2];
	pm[0] = matrix(12, 3);
	pm[1] = matrix(12, 3);

	std::cout << m << '\n';
	std::cout << m1 << '\n';
	std::cout << pm[0] << '\n';
	std::cout << pm[1] << '\n';

}

void matrix_det(){
	uint n = 3;
	matrix m(n, n);
	for(uint i = 0; i < n; ++i){
		for(uint j = 0; j < n; ++j){
			m[i][j] = (rand() % 10) * (rand() % 10);
		}
	}
	std::cout << m << '\n';

//	matrix mm = m.minor(0, 1);
//	std::cout << mm << '\n';
	std::cout << m.det() << '\n';
}

int main(){
	srand(time(0));
//	matrix_test();
	matrix_det();
}

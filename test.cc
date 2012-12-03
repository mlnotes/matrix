#include <iostream>
#include "matrix.h"


int main(){
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

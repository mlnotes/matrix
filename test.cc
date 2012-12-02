#include <iostream>
#include "matrix.h"


int main(){
    matrix m(12, 13);
	uint rows = m.get_rows_num();
	uint cols = m.get_cols_num();

	std::cout << rows << ' ' << cols << '\n';

	mvector& v = m[2];
	v[8] = 12.99;
	m[2][8] = 13;
	std::cout << v.size() << ' ' 
				<< v[8] << ' ' 
				<< m[2][8] << '\n';

	mvector col = m.get_col(8);
	std::cout << col[2] << '\n';
}

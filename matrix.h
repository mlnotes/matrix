#ifndef MATRIX_H
#define MATRIX_H

#include "mvector.h"

class matrix{
public:
	matrix(uint rows, uint cols);
	matrix(matrix &);
	~matrix();

	uint get_rows_num();
	uint get_cols_num();
	mvector get_row(uint index);
	mvector get_col(uint index);

	mvector& operator[](const uint &index);
private:
	uint rows;
	uint cols;
	mvector *data;
};
#endif

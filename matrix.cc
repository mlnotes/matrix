#include "matrix.h"

matrix::
matrix(uint rows, uint cols){
    this->rows = rows;
    this->cols = cols;
    this->data = new mvector[rows];
    for(uint i = 0; i < rows; ++i)
        this->data[i] = mvector(cols);
}

matrix::
~matrix(){
    delete [] this->data;
}

uint matrix::
get_rows_num(){
    return this->rows;
}


uint matrix::
get_cols_num(){
    return this->cols;
}

mvector matrix::
get_row(uint index){
	return this->data[index];
}

mvector matrix::
get_col(uint index){
	mvector v(this->rows);
	for(uint i = 0; i < this->rows; ++i)
		v[i] = this->data[i][index];

	return v;
}

mvector& matrix::
operator[] (const uint &index){
	return this->data[index];
}



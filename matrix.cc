#include "matrix.h"
#include <iostream>

matrix::
matrix(uint rows, uint cols){
    this->_rows = rows;
    this->_cols = cols;
    this->_data = new mvector[rows];
    for(uint i = 0; i < rows; ++i){
        this->_data[i] = mvector(cols);
	}
}

matrix::
matrix(const matrix &that){
	copy(that);
}

matrix::
~matrix(){
    delete [] this->_data;
}

matrix& matrix::
operator= (const matrix &that){
	copy(that);
	return *this;
}

void matrix::
copy(const matrix &that){
	this->_rows = that._rows;
	this->_cols = that._cols;
	this->_data = new mvector[this->_rows];
	for(uint i = 0; i < this->_rows; ++i){
		this->_data[i] = mvector(this->_cols);
		for(uint j = 0; j < this->_cols; ++j){
			this->_data[i][j] = that._data[i][j];
		}
	}
}

uint matrix::
row_count() const{
    return this->_rows;
}


uint matrix::
col_count() const{
    return this->_cols;
}

mvector matrix::
get_row(uint index) const{
	return this->_data[index];
}

mvector matrix::
get_col(uint index) const{
	mvector v(this->_rows);
	for(uint i = 0; i < this->_rows; ++i)
		v[i] = this->_data[i][index];

	return v;
}

mvector& matrix::
operator[] (const uint &index) const{
	return this->_data[index];
}

ostream&
operator<< (ostream &out, const matrix &obj){
	out << "[\n";
	for(uint i = 0; i < obj.row_count(); ++i)
		out << obj[i] << '\n';
	out << "]";
	return out;
}

matrix
operator* (const matrix &left, const matrix &right){
	if(left.col_count() != right.row_count())
		throw "can not perfrom dot product";

	matrix result(left.row_count(), right.col_count());
	for(uint i = 0; i < left.row_count(); ++i){
		for(uint j = 0; j < right.col_count(); ++j){
			result[i][j] = left.get_row(i) * right.get_col(j);
		}
	}
	return result;
}

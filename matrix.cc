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

matrix
operator* (const float &k, const matrix &m){
	matrix result(m.row_count(), m.col_count());
	for(uint i = 0; i < m.row_count(); ++i){
		for(uint j = 0; j < m.col_count(); ++j){
			result[i][j] = m[i][j] * k;
		}
	}
	return result;
}

matrix
operator+ (const matrix &left, const matrix &right){
	if((left.row_count() != right.row_count()) ||
		(left.col_count() != right.col_count()))
			throw "can not perfrom add";

	matrix result(left.row_count(), left.col_count());
	for(uint i = 0; i < result.row_count(); ++i){
		for(uint j = 0; j < result.col_count(); ++j){
			result[i][j] = left[i][j] + right[i][j];
		}
	}
	return result;
}

matrix
operator- (const matrix &left, const matrix &right){
	if((left.row_count() != right.row_count()) ||
		(left.col_count() != right.col_count()))
			throw "can not perfrom minus";

	matrix result(left.row_count(), left.col_count());
	for(uint i = 0; i < result.row_count(); ++i){
		for(uint j = 0; j < result.col_count(); ++j){
			result[i][j] = left[i][j] - right[i][j];
		}
	}
	return result;
}

matrix matrix::
transpose() const{
	matrix result(this->col_count(), this->row_count());
	for(uint i = 0; i < result.row_count(); ++i){
		for(uint j = 0; j < result.col_count(); ++j){
			result[i][j] = this->_data[j][i];
		}
	}
	return result;
}

matrix matrix::
inverse() const{
	// TODO
	throw "NOT IMPLEMENTED";
}

matrix matrix::
minor(uint m, uint n) const{
	matrix result(this->row_count()-1,
				this->col_count()-1);

	uint ni = 0;
	uint nj = 0;
	for(uint i = 0; i < this->row_count(); ++i){
		if(i == m) continue;
		nj = 0;
		for(uint j = 0; j < this->col_count(); ++j){
			if(j == n) continue;
			result[ni][nj] = this->_data[i][j];
			nj += 1;
		}
		ni += 1;
	}
	return result;
}

float matrix::
det() const{	//TODO there should be some optimizing methods
	if(this->row_count() != this->col_count())
		throw "Only n*n matrix has determinant";

	uint n = this->row_count();
	if(n == 1)
		return this->_data[0][0];
	else if(n == 2)
		return this->_data[0][0] * this->_data[1][1] -
				this->_data[0][1] * this->_data[1][0];

	float result = 0.0;
	// applying Laplace expansion on row 0
	for(uint i = 0; i < n; ++i){
		float minor_det = this->_data[0][i] * this->minor(0, i).det();
//		std::cout << "minor: " << n << ' ' << i << ' ' << minor_det << '\n';
		if(i % 2)
			result -= minor_det;
		else
			result += minor_det;
	}
	return result;
}

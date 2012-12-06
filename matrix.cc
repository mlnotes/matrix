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

void matrix::
reset(uint rows, uint cols){
	if(this->_data){
		delete [] this->_data;
		this->_data = NULL;
	}

    this->_rows = rows;
    this->_cols = cols;
    this->_data = new mvector[rows];
    for(uint i = 0; i < rows; ++i){
        this->_data[i] = mvector(cols);
	}
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
	float d = this->det();
	if(d == 0)
		throw "do not have an inverse matrix: determinant is 0";

	return (1.0/d) * this->cofactor();
}

matrix matrix::
mminor(uint m, uint n) const{
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

matrix matrix::
mminor(uint rstart, uint rend, uint cstart, uint cend, matrix &sub) const{
	if(rstart < 0 || rend > this->row_count()-1 || rend < rstart)
		throw "invalid row range";
	if(cstart < 0 || cend > this->col_count()-1 || cend < cstart)
		throw "invalid col range";

	sub.reset(rend-rstart+1, cend-cstart+1);
	matrix result(this->row_count()-sub.row_count(),
					this->col_count()-sub.col_count());

	uint mi = 0, mj = 0;
	uint si = 0, sj = 0;
	for(uint i = 0; i < this->row_count(); ++i){
		if(i >= rstart && i <= rend){
			sj = 0;
			for(uint j = cstart; j <= cend; ++j){
				sub[si][sj] = this->_data[i][j];
				sj += 1;
			}
			si += 1;
		}else{
			mj = 0;
			for(uint j = 0; j < this->col_count(); ++j){
				if(j < cstart || j > cend){
					result[mi][mj] = this->_data[i][j];
					mj += 1;
				}
			}
			mi += 1;
		}
	}
	return result;
}

// using Laplace expansion to calculat
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
	else if(n == 3)
		return this->_data[0][0] * this->_data[1][1] * this->_data[2][2] +
				this->_data[1][0] * this->_data[2][1] * this->_data[0][2] +
				this->_data[2][0] * this->_data[0][1] * this->_data[1][2] -
				this->_data[2][0] * this->_data[1][1] * this->_data[0][2] -
				this->_data[1][0] * this->_data[0][1] * this->_data[2][2] -
				this->_data[0][0] * this->_data[2][1] * this->_data[1][2];

	float result = 0.0;
	// applying Laplace expansion on row 0
	for(uint i = 0; i < n; ++i){
		if(this->_data[0][i] == 0) continue;
		float mminor_det = this->_data[0][i] * this->mminor(0, i).det();
		if(i % 2)
			result -= mminor_det;
		else
			result += mminor_det;
	}
	return result;
}

// using the defination of determinant to calculate
float matrix::
fast_det() const{
	if(this->row_count() != this->col_count())
		throw "Only n*n matrix has determinant";

	uint n = this->row_count();
	uint *range = new uint[n];
	for(uint i = 0; i < n; ++i)
		range[i] = i;

	float result = det_help(range, n, 0, 1);
	delete [] range;
	return result;
}

float matrix::
det_help(uint *range, uint size, uint cur, int sgn) const{
	if(cur == size){
		float result = 1;
		for(uint i = 0; i < size; ++i){
			result *= this->_data[i][range[i]];
		}
		return (sgn==1)?result:-result;
	}

	float result = det_help(range, size, cur+1, sgn);
	for(uint i = cur+1; i < size; ++i){
		int t = range[i];
		range[i] = range[cur];
		range[cur] = t;
		
		result += det_help(range, size, cur+1, -sgn);
		
		t = range[i];
		range[i] = range[cur];
		range[cur] = t;
	}
	return result;
}

matrix matrix::
cofactor() const{
	matrix result(this->row_count(), this->col_count());

	for(uint i = 0; i < this->row_count(); ++i){
		for(uint j = 0; j < this->col_count(); ++j){
			if((i+j) % 2)
				result[i][j] = - this->mminor(j,i).det();
			else
				result[i][j] = this->mminor(j,i).det();
		}
	}
	return result;
}

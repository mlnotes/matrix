#ifndef MATRIX_H
#define MATRIX_H

#include "mvector.h"

class matrix{
public:
	matrix(uint rows=0, uint cols=0);
	matrix(const matrix &);
	~matrix();

	uint row_count() const;
	uint col_count() const;
	mvector get_row(uint index) const;
	mvector get_col(uint index) const;

	mvector& operator[](const uint &index) const;
	matrix& operator= (const matrix &that);
	friend ostream& operator<< (ostream &, const matrix &obj);
	friend matrix operator* (const matrix &, const matrix &);
private:
	uint _rows;
	uint _cols;
	mvector *_data;

	void copy(const matrix &);
};
#endif

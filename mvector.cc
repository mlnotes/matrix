#include "mvector.h"
#include <math.h>

mvector::
mvector(uint size){
	this->_size = size;
	this->_data = new float[size];
}

mvector::
mvector(const float *array, uint size){
	this->_size = size;
	this->_data = new float[size];
	for(uint i = 0; i < size; ++i)
		this->_data[i] = array[i];
}

mvector::
mvector(const mvector &that){
	copy(that);
}

mvector::
~mvector(){
	delete [] this->_data;
}

uint mvector::
size() const{
	return this->_size;
}

float mvector::
module() const{
	float total = 0.0;
	for(uint i = 0; i < this->_size; ++i)
		total += this->_data[i] * this->_data[i];

	return sqrt(total);
}

float& mvector::
operator[] (const uint &index) const{
	return this->_data[index];
}

mvector& mvector::
operator= (const mvector &that){
	copy(that);
	return *this;
}

void mvector::
copy(const mvector &that){
	this->_size = that._size;
	this->_data = new float[this->_size];
	for(uint i = 0; i < this->_size; ++i)
		this->_data[i] = that._data[i];
}

mvector
operator+ (const mvector &left, const mvector &right){
	if(left.size() != right.size())
		throw "size not equal";
	mvector v(left.size());
	for(uint i = 0; i < v.size(); ++i)
		v[i] = left[i] + right[i];	
	return v;
}

mvector
operator- (const mvector &left, const mvector &right){
	if(left.size() != right.size())
		throw "size not equal";
	mvector v(left.size());
	for(uint i = 0; i < v.size(); ++i)
		v[i] = left[i] - right[i];	
	return v;
}

float
operator* (const mvector &left, const mvector &right){
	if(left.size() != right.size())
		throw "size not equal";
	float result = 0.0;
	for(uint i = 0; i < left.size(); ++i)
		result += left[i] * right[i];
	
	return result;
}

mvector
operator* (const float &k, const mvector &m){
	mvector result(m.size());
	for(uint i = 0; i < m.size(); ++i)
		result[i] = m[i] * k;

	return result;
}

ostream&
operator<< (ostream &out, mvector &obj){
	out << '[';
	for(uint i = 0; i < obj.size()-1; ++i)
		out << obj[i] << ',';
	if(obj.size() > 0)
		out << obj[obj.size()-1];

	out << ']';
	return out;
}

float
cos(const mvector &left, const mvector &right){
	if(left.size() == 0 || right.size() == 0)
		return 0;

	float lm = left.module();
	float rm = right.module();
	if(lm == 0 || rm == 0)
		return 0;

	return (left * right)/(lm * rm);
}

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
	this->_size = that._size;
	this->_data = new float[this->_size];
	for(uint i = 0; i < this->_size; ++i)
		this->_data[i] = that._data[i];
}

mvector& mvector::
operator= (const mvector &that){
	this->_size = that._size;
	this->_data = new float[this->_size];
	for(uint i = 0; i < this->_size; ++i)
		this->_data[i] = that._data[i];

	return *(this);
}

uint mvector::
size(){
	return this->_size;
}

mvector::
~mvector(){
	delete [] this->_data;
}

float& mvector::
operator[] (const uint &index){
	return this->_data[index];
}

mvector mvector::
operator+ (const mvector &that){
	mvector v(this->_size);
	for(uint i = 0; i < this->_size; ++i)
		v[i] = this->_data[i] + that._data[i];
	
	return v;
}

mvector mvector::
operator- (const mvector &that){
	mvector v(this->_size);
	for(uint i = 0; i < this->_size; ++i)
		v[i] = this->_data[i] - that._data[i];
	
	return v;
}

float mvector::
operator* (const mvector &that){
	float result = 0.0;
	for(uint i = 0; i < this->_size; ++i)
		result += this->_data[i] * that._data[i];
	
	return result;
}


float mvector::
module(){
	float total = 0.0;
	for(uint i = 0; i < this->_size; ++i)
		total += this->_data[i] * this->_data[i];

	return sqrt(total);
}


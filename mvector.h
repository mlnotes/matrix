#ifndef MVECTOR_H
#define MVECTOR_H

#include <ostream>
using std::ostream;

typedef unsigned int uint;

class mvector{
public:
	mvector(uint size = 0);
	mvector(const float *array, uint size);
	mvector(const mvector &);
	~mvector();

	uint size() const;
	float module() const;
	
	float& operator[](const uint &index) const;
	mvector& operator= (const mvector &);
	friend mvector operator+(const mvector &, const mvector &);
	friend mvector operator-(const mvector &, const mvector &);
	friend float operator* (const mvector &, const mvector &);
	friend ostream& operator<< (ostream &, mvector &);
	friend float cos(const mvector &, const mvector &);

private:
	uint _size;
	float* _data;
	
	void copy(const mvector &);
};

#endif

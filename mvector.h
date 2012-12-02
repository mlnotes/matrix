#ifndef MVECTOR_H
#define MVECTOR_H

typedef unsigned int uint;

class mvector{
public:
	mvector(uint size = 0);
	mvector(const float *array, uint size);
	mvector(const mvector &);
	~mvector();

	uint size();
	float& operator[](const uint &index);
	mvector& operator=(const mvector &);
	mvector operator+(const mvector &);
	mvector operator-(const mvector &);
	float operator* (const mvector &);

	float module();
private:
	uint _size;
	float* _data;
};

#endif

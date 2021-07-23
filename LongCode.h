#ifndef LONGCODE_H
#define LONGCODE_H

#include <math.h>
#include <stdint.h>

class LongCode
{
public:
	LongCode();
	~LongCode();

	uint64_t computeState(uint64_t shift);
private:
	static const int n = 3;
	static const uint64_t len = pow(2, n) -1;
	bool*** b;

private:
	void fillFirstMatrix();
	void mult(bool** m1, bool** m2, bool** m3);
	void mult(bool* b1, bool** b2, bool* b3);
	void print(bool** ptr);
	void print(bool* ptr);
	void deleteArr(bool* ptr);
	void deleteArr(bool** ptr);
	void deleteArr(bool*** ptr);
};
#endif // LONGCODE_H

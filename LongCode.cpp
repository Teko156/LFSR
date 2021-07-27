#include "LongCode.h"
#include <QString>
#include <QDebug>

LongCode::LongCode()
{
	//--------------------------------------------------------------------------
	b = new bool**[n];
	for(int i = 0; i < n; ++i)
	{
		b[i] = new bool*[n];
		for(int j = 0; j < n; ++j)
		{
			b[i][j] = new bool[n];
			for(int k = 0; k < n; ++k)
				b[i][j][k] = false;
		}
	}
	//--------------------------------------------------------------------------
	mIn = new bool*[n];
	for(int i = 0; i < n; ++i)
	{
		mIn[i] = new bool[n];
		for(int j = 0; j < n; ++j)
			mIn[i][j] = false;
	}
	//--------------------------------------------------------------------------
	mOut = new bool*[n];
	for(int i = 0; i < n; ++i)
	{
		mOut[i] = new bool[n];
		for(int j = 0; j < n; ++j)
			mOut[i][j] = false;
	}
	//--------------------------------------------------------------------------
	fillFirstMatrix();
	for(int i = 1; i < n; ++i)
	{
		mult(b[i-1], b[i-1], b[i]);
	}
	//--------------------------------------------------------------------------
}

LongCode::~LongCode()
{
	deleteArr(b);
	deleteArr(mIn);
	deleteArr(mOut);
}


void LongCode::fillFirstMatrix()
{

	for(int i = 1; i < n; ++i)
		b[0][i-1][i] = true;

//	b[0][1][n-1] = true;
//	b[0][0][n-1] = true;


	b[0][n-1][35] = true;
	b[0][n-1][33] = true;
	b[0][n-1][31] = true;
	b[0][n-1][27] = true;
	b[0][n-1][26] = true;
	b[0][n-1][25] = true;
	b[0][n-1][22] = true;
	b[0][n-1][21] = true;
	b[0][n-1][19] = true;
	b[0][n-1][18] = true;
	b[0][n-1][17] = true;
	b[0][n-1][16] = true;
	b[0][n-1][10] = true;
	b[0][n-1][ 7] = true;
	b[0][n-1][ 6] = true;
	b[0][n-1][ 5] = true;
	b[0][n-1][ 3] = true;
	b[0][n-1][ 2] = true;
	b[0][n-1][ 1] = true;
	b[0][n-1][ 0] = true;



}

void LongCode::mult(bool **m1, bool **m2, bool** m3)
{
	for(int i = 0; i < n; ++i)
		for(int j = 0; j < n; ++j)
			for(int k = 0; k < n; ++k)
				m3[i][j] ^= m1[i][k]&&m2[k][j];
}

void LongCode::mult(bool *b1, bool **b2, bool *b3)
{
	for(int i = 0; i < n; ++i)
		for(int j = 0; j < n; ++j)
			b3[i] ^= b1[j]&&b2[j][i];
}

void LongCode::print(bool **ptr)
{
	qDebug()<< "------------";
	QString s = "";
	for(int i = 0; i < n; ++i)
	{
		s = "";
		for(int j = 0; j < n; ++j)
		{
			s+= QString("%1 ").arg(int(ptr[i][j]));
		}
		qDebug()<< s;
	}
}

void LongCode::print(bool *ptr)
{
	qDebug()<< "------------";
	QString s = "";
	for(int i = 0; i < n; ++i)
	{
		s+= QString("%1 ").arg(int(ptr[i]));
	}
	qDebug()<< s;
}

void LongCode::deleteArr(bool* ptr)
{
	if(!ptr) return;
	delete[] ptr;
	ptr = nullptr;
}

void LongCode::deleteArr(bool** ptr)
{
	if(!ptr) return;
	for(int i = 0; i < n; ++i)
		deleteArr(ptr[i]);
	deleteArr(ptr);
}

void LongCode::deleteArr(bool*** ptr)
{
	if(!ptr) return;
	for(int i = 0; i < n; ++i)
	{
		deleteArr(ptr[i]);
	}
	deleteArr(ptr);

}

uint64_t LongCode::rfsr42(uint64_t shift)
{
	shift += 41;
	for(int i = 0; i < n; ++i)
		mOut[i][i] = true;

	bool** mCalc;

	shift &= mask;

	int cnt = 0;
	while (shift > 0)
	{
		if(shift%2 == 0)
		{
			shift >>= 1;
			++cnt;
			continue;
		}

		for(int i = 0; i < n; ++i)
			for(int j = 0; j < n; ++j)
			{
				mIn[i][j] = mOut[i][j];
				mOut[i][j] = false;
			}

		mCalc = b[cnt];
		mult(mIn,mCalc,mOut);

		shift >>= 1;
		++cnt;
	}

	bool* initStatePtr = new bool[n];
	for(int i = 0; i < n; ++i)
		initStatePtr[i] = false;
	initStatePtr[0] = true;

	bool* shiftedStatePtr = new bool[n];
	for(int i = 0; i < n; ++i)
		shiftedStatePtr[i] = false;

	mult(initStatePtr, mOut, shiftedStatePtr);

	uint64_t state = 0;
	for(int i = 0; i < n; ++i)
	{
		state += uint64_t(shiftedStatePtr[i]) << i;
	}
	state &= mask;
	return state;
}

#include "LongCode.h"
#include <QString>
#include <QDebug>

LongCode::LongCode()
{

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


	for(int i = 0; i < n; ++i)
		for(int j = 0; j < n; ++j)
			for(int k = 0; k < n; ++k)
				b[i][j][k] = false;

	fillFirstMatrix();
	for(int i = 1; i < n; ++i)
	{
		mult(b[i-1], b[i-1], b[i]);
	}
}

LongCode::~LongCode()
{
	deleteArr(b);
}


void LongCode::fillFirstMatrix()
{
//	for(int i = 0; i < n; ++i)
//		for(int j = 0; j < n; ++j)
//			b[0][i][j] = false;

	for(int i = 1; i < n; ++i)
		b[0][i][i-1] = true;

	b[0][1][n-1] = true;
	b[0][0][n-1] = true;

//	b[0][42-1][n-1] = true;
//	b[0][35-1][n-1] = true;
//	b[0][33-1][n-1] = true;
//	b[0][31-1][n-1] = true;
//	b[0][27-1][n-1] = true;
//	b[0][26-1][n-1] = true;
//	b[0][25-1][n-1] = true;
//	b[0][22-1][n-1] = true;
//	b[0][21-1][n-1] = true;
//	b[0][19-1][n-1] = true;
//	b[0][18-1][n-1] = true;
//	b[0][17-1][n-1] = true;
//	b[0][16-1][n-1] = true;
//	b[0][10-1][n-1] = true;
//	b[0][ 7-1][n-1] = true;
//	b[0][ 6-1][n-1] = true;
//	b[0][ 5-1][n-1] = true;
//	b[0][ 3-1][n-1] = true;
//	b[0][ 2-1][n-1] = true;
//	b[0][ 1-1][n-1] = true;


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
	ptr = 0;
}

void LongCode::deleteArr(bool** ptr)
{
	if(!ptr) return;
	for(int i = 0; i < n; ++i)
		delete[] ptr[i];
	delete[] ptr;
	ptr = nullptr;
}

void LongCode::deleteArr(bool*** ptr)
{
	if(!ptr) return;
	for(int i = 0; i < n; ++i)
	{
//		for(int j = 0; j < n; ++j)
//			delete[] ptr[i][j];
//		delete[] ptr[i];
		deleteArr(ptr[i]);
	}
	delete[] ptr;
	ptr = nullptr;

}

uint64_t LongCode::computeState(uint64_t shift)
{

	//--------------------------------------------------------------------------
	bool** mTemp = new bool*[n];
	for(int i = 0; i < n; ++i)
	{
		mTemp[i] = new bool[n];
		for(int j = 0; j < n; ++j)
			mTemp[i][j] = false;
	}

	//--------------------------------------------------------------------------
	bool** m = new bool*[n];
	for(int i = 0; i < n; ++i)
	{
		m[i] = new bool[n];
		for(int j = 0; j < n; ++j)
			m[i][j] = false;
	}
	for(int i = 0; i < n; ++i)
		m[i][i] = true;
	//--------------------------------------------------------------------------
	bool** mCalc;


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
				mTemp[i][j] = m[i][j];
				m[i][j] = false;
			}

		mCalc = b[cnt];
//		print(mTemp);
//		print(mCalc);

		mult(mTemp,mCalc,m);

//		print(m);

		shift >>= 1;
		++cnt;
	}

//	print(m);

	bool* initStatePtr = new bool[n];
	for(int i = 0; i < n; ++i)
		initStatePtr[i] = false;
	initStatePtr[0] = true;



	bool* shiftedStatePtr = new bool[n];
	for(int i = 0; i < n; ++i)
		shiftedStatePtr[i] = false;

	mult(initStatePtr, m, shiftedStatePtr);

//	print(initStatePtr);
//	print(shiftedStatePtr);

	uint64_t state = 0;
	for(int i = 0; i < n; ++i)
	{
		state += uint64_t(shiftedStatePtr[i]) << i;
	}

	deleteArr(mTemp);
	deleteArr(m);
//	delete mCalc;

	return state;
}

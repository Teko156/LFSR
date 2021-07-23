#include <QCoreApplication>
#include "LongCode.h"
#include <QDebug>
#include <stdint.h>
#include <QElapsedTimer>

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);

	LongCode lc;
	uint64_t shift = 663125524836;

	for(uint64_t i = 0; i < 6; ++i)
	{
		uint64_t state = lc.computeState(i);
		qDebug()<< i << state;
	}

//	QElapsedTimer t;
//	t.start();
//	uint64_t state = lc.computeState(shift);
//	uint64_t elapsed = t.nsecsElapsed();
//	qDebug()<< hex <<  state << dec << elapsed/1e6;

//	uint64_t ref = 0x34430A91286;
	return a.exec();
}

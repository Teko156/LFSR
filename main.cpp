#include <QCoreApplication>
#include "LongCode.h"
#include <QDebug>
#include <stdint.h>
#include <QElapsedTimer>

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);

	LongCode lc;

//	uint64_t i = (uint64_t(1)<<42) + 1 + 41;
	uint64_t i = 663125524836;
	QElapsedTimer t;
	t.start();
	uint64_t state = lc.rfsr42(i);
	uint64_t elapsed = t.nsecsElapsed();
	qDebug()<< "state =" << dec << state << dec << "elapsed " << elapsed/1e6 << "ms";
	qDebug()<< "shift ="<< i << "bin state =" << bin << state;
	return a.exec();
}

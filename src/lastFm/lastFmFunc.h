#ifndef LAST_FM_FUNC_H
#define LAST_FM_FUNC_H
#include <QString>
#include"imageSize.h"

namespace lastFm
{
	void init();

	QString key();
	
	int sizeFromString(const QString &s);
};
#endif
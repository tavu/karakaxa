#include"lastFmFunc.h"

#include<QDebug>
#include<ws.h>
#include<string>
void lastFm::init()
{
	lastfm::ws::ApiKey ="bc60ca5af733c62b5e405fa6253e1b38";
	qDebug()<<"init";
}

QString lastFm::key()
{
	return QString("bc60ca5af733c62b5e405fa6253e1b38");
}

int lastFm::sizeFromString(const QString& s)
{
	if(s.compare("small",Qt::CaseInsensitive)==0)
	{
		return SMALL;
	}
	if(s.compare("medium",Qt::CaseInsensitive)==0)
	{
		return MEDIUM;
	}
	if(s.compare("large",Qt::CaseInsensitive)==0)
	{
		return LARGE;
	}
	if(s.compare("extralarge",Qt::CaseInsensitive)==0 )
	{
		return EXTRA;
	}
	if(s.compare("mega",Qt::CaseInsensitive)==0)
	{
		return MEGA;
	}
	
	return -1;
}

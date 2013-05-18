#include"status.h"
#include<QDebug>

Basic::status::status()
{

}


void Basic::status::error(const QString& s)
{
    emit errorMessage(s);
}

void Basic::status::logErr(const QString& s)
{
    qDebug()<<"[ERR] "<<s;
}

void Basic::status::info(const QString& s)
{
    emit infoMessage(s);
}

void Basic::status::logInfo(const QString& s)
{
      qDebug()<<"[INF] "<<s;
}

void Basic::status::init()
{
    if(_instance==0)
    {
        _instance=new status();
    }
}

Basic::status* Basic::status::instance()
{
    return _instance;
}


Basic::status* Basic::status::_instance=0;

Basic::status* Basic::msg()
{
    return status::instance();
}

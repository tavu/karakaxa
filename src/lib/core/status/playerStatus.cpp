#include"playerStatus.h"
#include<QDebug>

core::playetStatus::playetStatus()
{

}


void core::playetStatus::addError(const QString& s)
{
    emit errorMessage(s);
}

void core::playetStatus::addErrorP(const QString& s)
{
    qDebug()<<"[ERR] "<<s;
}

void core::playetStatus::addInfo(const QString& s)
{
    emit infoMessage(s);
}

void core::playetStatus::addInfoP(const QString& s)
{
      qDebug()<<"[INF] "<<s;
}

namespace core
{
    playetStatus *status;
}
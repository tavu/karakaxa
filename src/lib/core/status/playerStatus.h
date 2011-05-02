#ifndef PLAYERSTATUS_H
#define PLAYERSTATUS_H
#include<QString>
#include<QObject>
#include "../config/config.h"
namespace core
{
  
class playetStatus :public QObject
{
    Q_OBJECT
    public:
	playetStatus();
	
	void addError(const QString &s);
	void addInfo(const QString &s);
	
	void addErrorP(const QString &s);
	void addInfoP(const QString &s);
    signals:
	void errorMessage(const QString &s);
	void infoMessage(const QString &s);
};


    extern playetStatus *status;
};
#endif
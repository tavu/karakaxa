#ifndef STATUS_H
#define STATUS_H
#include<QString>
#include<QObject>

namespace Basic
{
  
class status :public QObject
{
    Q_OBJECT
    public:
        static void init();
        static status* instance();
        
        status();

        void error(const QString &s);
        void info(const QString &s);

        void logErr(const QString &s);
        void logInfo(const QString &s);
    
    signals:
        void errorMessage(const QString &s);
        void infoMessage(const QString &s);
                
    private:
        static status *_instance;
        
};

status *msg();


};
#endif
#include "database.h"
#include<QThread>
namespace core
{

class databaseScanner :public QThread
{
    public:
        friend class database;
        databaseScanner(database::dbState t,QObject *parent=0) :QThread(parent)
        {
            _type=t;
        }

        database::dbState type()
        {
            return _type;
        }

        void scan()
        {
            db->scan(this);
        }
        //void stop()=0;

        virtual QWidget *widget()
        {
            return 0;
        }

    protected:
        //give the posibility to make some initialization befora start the thread
        virtual void startScan()
        {
            start();
        }

        
    private:
        database::dbState _type;
};

}


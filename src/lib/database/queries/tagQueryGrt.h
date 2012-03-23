#ifndef TAGQUERYGRT_H
#define TAGQUERYGRT_H
#include"queryGeneration.h"
namespace database
{
    
class tagQueryGrt :public queryGrt
{
    Q_OBJECT
    public:
        tagQueryGrt(QObject *parent=0) :queryGrt(parent),tag_(0)
        {
        }

        QString queryString() const;
        void setTag(int t)
        {
            tag_=t;
            _needUpdate=true;
        }

        int tag()
        {
            return tag_;
        }

        bool select();
        QStringList result()
        {
            return list;
        }

    private slots:
        void setNeedUpdate(const audioFiles::audioFile f);

    private:
        int tag_;
        QStringList list;
};

}
#endif
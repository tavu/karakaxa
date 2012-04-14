#ifndef M3UP_H
#define M3UP_H

#include <QFile>
#include <kurl.h>
#include<QString>
#include<iostream>
#include"filePlaylist.h"
// #include<playerNamespace.h>
#include"../../files/audioFile.h"
using namespace audioFiles;
namespace core
{
class m3uPlaylist :public filePlaylist
{
    Q_OBJECT
    public:
        m3uPlaylist(const QString s,QObject *parent=0);

    public slots:
        void insertUrl(int pos,QString u);

        bool load();
        bool save();

    public:
        QStringList urls() const;

    protected:
        bool createFile();
};
};
#endif

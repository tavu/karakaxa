#ifndef M3UP_H
#define M3UP_H

#include <QFile>
#include <kurl.h>
#include<QString>
#include<iostream>
#include"abstractPlaylist.h"
// #include<playerNamespace.h>
#include"../../files/audioFile.h"
using namespace audioFiles;
namespace core
{
class m3uPlaylist :public abstractPlaylist
{
    
    public:
	m3uPlaylist(const QString s);
	
	void insert(int row,QString u);
	void remove(int row);
	void move( int from, int to );

	QString item(int pos) const;	
	QStringList urls() const;
	
	int size() const;

	QString path() const
	{
	    return _path;
	}
	
	bool load();
	bool save();
	
	int error() const;
	
    private:

	
	void toFullPath(QString &s);
	QString _path;
	QFile file;
	int	err;
	
	QStringList list;

};
};
#endif

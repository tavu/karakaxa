#ifndef TRACKMODEL_H
#define TRACKMODEL_H
#include <qobject.h>
#include"../../core/standardModel/standardModel.h"
#include"../../core/database/queryGeneration.h"
#include"../../files/audioFiles.h"
#include"../views.h"
namespace views
{

class trackItem :public standardItem
{    
    public:
	trackItem(audioFiles::audioFile f);
	virtual int columnCount() const
	{
	    return audioFiles::FRAME_NUM;
	}
       
	virtual bool setData (const QVariant &value,int column, int role );
	virtual QVariant data (int column, int role = Qt::UserRole + 1 ) const;	
    protected:
	audioFiles::audioFile file;
};
  
  
class trackModelItem :public standardItem
{
    Q_OBJECT
    public:
	trackModelItem();
	
	virtual int columnCount() const
	{
	    return audioFiles::FRAME_NUM;
	}
       
	virtual QVariant headerData ( int section, Qt::Orientation orientation, int role = Qt::DisplayRole ) const;
	virtual QVariant data (int column, int role = Qt::UserRole + 1 ) const
	{
	    if(column>0)
	    {
		return QVariant();
	    }
	    if(role==Qt::DisplayRole)
	    {
		return QString("Album");
	    }
	    if(role==Qt::DecorationRole)
	    {
// 	      pix[i].scaled(imageSize, Qt::IgnoreAspectRatio,  Qt::SmoothTransformation);
		 return decor->albumPic().scaled(QSize(40,40), Qt::IgnoreAspectRatio,  Qt::SmoothTransformation);
	    }
	    if(role==Qt::SizeHintRole)
	    {
		return QSize(40,40);
	    }
	    return QVariant();
	}
	
	core::queryGrt* queryG()
	{
	    return q;
	}
	
	void setQueryG(core::queryGrt *qe);
	
    public slots:
	void addItem(audioFile f, int pos);
	void addItems();
	void removeItem(audioFiles::audioFile ,int pos);
	
    protected:

	//this function returns a trackItem pointer.
	//is usefull if u want to use a subclass of trackItem.
	virtual standardItem* getItem(audioFiles::audioFile &f);
	core::queryGrt *q;  
	
};

};
#endif
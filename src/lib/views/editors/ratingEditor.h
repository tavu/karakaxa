#ifndef RATINGEDITOR_H
#define RATINGEDITOR_H

#include"../ratingWidget/ratingWidget.h"
#include "tagEditor.h"
#include <QHBoxLayout>
#include"../../files/audioFiles.h"
namespace views
{

class ratingEditor :public tagEditor
{
  Q_OBJECT
    
    public:
	ratingEditor(QWidget *parent=0)
	:tagEditor(audioFiles::RATING,parent)
	{
	    stars=new ratingWidget(this);
	    QHBoxLayout *l=new QHBoxLayout(this);
	    l->setContentsMargins(0,0,0,0);
	    l->addWidget(stars);
	    
	    connect(stars,SIGNAL(ratingChanged(int)),this,SLOT(valueChanger(int )) );
	}
	
	void setValue(const QVariant &v)
	{
	    stars->setRating(v.toInt() );
	}
	
	QVariant value()
	{
	    return QVariant( stars->rating() );
	}
	
	ratingWidget* ratingW()
	{
	    return stars;
	}
	
    private:
      
	ratingWidget *stars;

    private slots:
	
	void valueChanger(int k)
	{
	    emit valueChanged(QVariant(k) );
	}
      
    
};

};
#endif
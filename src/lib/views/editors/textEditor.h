#ifndef TEXTEDITOR_H
#define TEXTEDITOR_H

#include <QLineEdit>
#include <QHBoxLayout>
#include <QVariant>
#include"../../core/core.h"

#include <QStringListModel>
#include<database.h>
#include<queries/tagQuery.h>
#include<queries/tagQueryGrt.h>

namespace views
{

class textEditor :public QLineEdit
{
   Q_OBJECT
   //Q_PROPERTY(QString value READ value WRITE setValue USER true)
    
    public:
        textEditor(int tag,QWidget *parent=0);
        
    private:
      
        database::tagQueryGrt  *q;
        database::tagQuery tagQ;

        QCompleter *comp;

        QStringListModel completerM;
    
};

QWidget* getEditor(int tag,QWidget *parent);

    
};
#endif
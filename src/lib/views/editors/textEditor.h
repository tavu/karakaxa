#ifndef TEXTEDITOR_H
#define TEXTEDITOR_H

#include <QLineEdit>
#include <QHBoxLayout>
#include <QVariant>
#include"../../core/core.h"
#include <QStringListModel>
namespace views
{

class textEditor :public QLineEdit
{
   Q_OBJECT
   //Q_PROPERTY(QString value READ value WRITE setValue USER true)
    
    public:
        textEditor(int tag,QWidget *parent=0);
        
    private:
      
        core::tagQueryGrt  *q;
        core::queryGrt::tagQuery tagQ;

        QCompleter *comp;

        QStringListModel completerM;
    
};

QWidget* getEditor(int tag,QWidget *parent);

    
};
#endif
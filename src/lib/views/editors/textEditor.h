#ifndef TEXTEDITOR_H
#define TEXTEDITOR_H

#include <QLineEdit>
#include "tagEditor.h"
#include <QHBoxLayout>
#include <QVariant>
#include"../core.h"
#include <QStringListModel>
namespace views
{

class textEditor :public QWidget
{
   Q_OBJECT
   Q_PROPERTY(QString value READ value WRITE setValue USER true)
    
    public:
        textEditor(int tag,QWidget *parent=0);

        void setValue(const QString s)
        {
            edit->setText(s);
        }

        QString value()
        {
            return  edit->text();
        }
        
    private:
      
        QLineEdit *edit;
        core::tagQueryGrt  *q;
        core::queryGrt::tagQuery tagQ;

        QCompleter *comp;

        QStringListModel completerM;
    
};

};
#endif
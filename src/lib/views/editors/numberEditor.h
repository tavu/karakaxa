#ifndef NUMBEREDITOR_H
#define NUMBEREDITOR_H

#include <QSpinBox>
#include "tagEditor.h"
#include <QHBoxLayout>
#include <QVariant>

namespace views
{

class numberEditor :public QWidget
{
   Q_OBJECT
   Q_PROPERTY(int value READ value WRITE setValue USER true)
       
    public:
        numberEditor(int tag,QWidget *parent=0)
        :QWidget(parent)
        {
            edit=new QSpinBox(this);
            edit->setMaximum(3000);
            edit->setMinimum(0);
            QHBoxLayout *l=new QHBoxLayout(this);

            l->addWidget(edit);
            l->setContentsMargins(0,0,0,0);

//             connect(edit,SIGNAL(valueChanged(int)),this,SLOT(valueChanger()) );
        }

        void setValue(const int n)
        {
            edit->setValue(n);
        }

        int value()
        {
            return  edit->value();
        }
	
    private:
      
        QSpinBox *edit;

    private slots:
	      
    
};

};
#endif
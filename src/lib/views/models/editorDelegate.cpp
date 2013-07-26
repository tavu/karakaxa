#include"editorDelegate.h"
#include<views/models/urlRole.h>
#include<views/editors/textEditor.h>
#include<database/editMultFiles.h>
#include<QAbstractItemView>
Q_DECLARE_METATYPE(QModelIndexList)

views::editorDelegate::editorDelegate(QAbstractItemView* parent): QStyledItemDelegate(parent)
{

}


QWidget* views::editorDelegate::createEditor(QWidget *parent,const QStyleOptionViewItem &option,const QModelIndex &index) const
{
    bool b;
    int tag=index.data(TAG_ROLE).toInt(&b);

    if(!b)
    {
        return QStyledItemDelegate::createEditor(parent,option,index);
    }

    QWidget *w = views::getEditor(tag,parent);
    if(w!=0)
    {
        w->setProperty("tag",tag);
        //TODO take the signal name by the QMetaObject
        connect(w,SIGNAL(ratingChanged(int) ),this, SLOT(commitEditor()));
    }
//     w->setAutoFillBackground(true);


    return w;
}

void views::editorDelegate::setEditorData(QWidget *editor,const QModelIndex &index) const
{
    QStyledItemDelegate::setEditorData(editor,index);
}

void views::editorDelegate::setModelData(QWidget *editor,QAbstractItemModel *model,const QModelIndex &index) const
{
    QModelIndexList list=qvariant_cast<QModelIndexList>(property("modelList") );

    if(list.isEmpty() )
    {
        QStyledItemDelegate::setModelData(editor,model,index);
        return ;
    }

    bool b;
    int tag=index.data(TAG_ROLE).toInt(&b);

    if(!b)
    {
        QStyledItemDelegate::setModelData(editor,model,index);
        return ;
    }

    QList<audioFiles::audioFile> l;
    int column=index.column();
    foreach(QModelIndex i,list)
    {
        if (i.column()==column )
        {
            l<<audioFiles::audioFile(i.data(URL_ROLE).toUrl() );
        }
    }

    //we dont need a new thread to edit just one item
    if(l.size()==1)
    {
        QStyledItemDelegate::setModelData(editor,model,index);
        return ;
    }

    database::editMultFiles::editFiles *thr=new database::editMultFiles::editFiles();
    thr->setFiles(l);
    thr->setTag(tag );

    QByteArray n = editor->metaObject()->userProperty().name();

    //QAbstractItemView *v
    thr->setValue( editor->property(n) );
    QAbstractItemView *view=static_cast<QAbstractItemView*>(parent() );
    connect(thr,SIGNAL(finished()),view,SLOT(reset()));
    thr->start();
}



void views::editorDelegate::commitEditor()
{
    QWidget *editor = qobject_cast<QWidget *>(sender());
    emit commitData(editor);
}


void views::editorDelegate::updateEditorGeometry(QWidget *editor,const QStyleOptionViewItem &option, const QModelIndex &index ) const
{
    QStyledItemDelegate::updateEditorGeometry(editor,option,index);
    editor->setGeometry(option.rect);
#if 0
    QSize s=sizeHint(option,index);
    QRect r=option.rect;
    r.setSize(s);
    editor->setFixedSize(s);
#endif
}
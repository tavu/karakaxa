#include"editTrackContent.h"
#include <QHBoxLayout>
#include<QPushButton>
#include<QPainter>
#include<QFormLayout>
//#include<cstdlib>
#include<QMetaProperty>
using namespace core;
using namespace views;
#define SIZE 150 ,170

editTrackContent::editTrackContent(QString url,QWidget *parent)
        :abstractContent(parent)
{
    file=new audioFile(url);
    file->load(audioFile::LOAD_FILE);

    cw=new coverWidget(this);
    cw->setSize(decor->coverSize());
    cw->setCover(file->cover());

    infoInit();
    tagInit();
    buttons=new QDialogButtonBox(QDialogButtonBox::Ok|QDialogButtonBox::Apply|QDialogButtonBox::Cancel,Qt::Horizontal,this);
    
    QVBoxLayout *vLayout=new QVBoxLayout();
    QGridLayout *gr=new QGridLayout();

    editors[RATING]->setFixedSize(140,30);

    gr->addWidget(cw,0,0,2,1);
    gr->addWidget(editors[RATING],0,1,Qt::AlignLeft);
    gr->addWidget(infoW,1,1);
    gr->addItem(new QSpacerItem(1,1,QSizePolicy::Ignored,QSizePolicy::Ignored),2,1);
    vLayout->addLayout(gr);

    vLayout->addWidget(tagW);
    vLayout->addWidget(editors[PATH]);
    vLayout->addWidget(buttons,Qt::AlignLeft);
    vLayout->addStretch();
    
    setLayout(vLayout);

    connect(buttons, SIGNAL(clicked(QAbstractButton* ) ), this, SLOT(clicked(QAbstractButton*) ));

}

QString editTrackContent::name() const
{
    return tr("Edit track");
}

editTrackContent::~editTrackContent()
{

   delete file;
}

void editTrackContent::tagInit()
{

    for(int i=0;i<FRAME_NUM;i++)
    {
	   if(i==COMMENT)
	   {
		  editors[i]=0;
		  continue;
	   }
	   
	   editors[i]=views::getEditor(i,this);
	   if(editors[i]==0)
	   {
            continue;
	   }

	   QVariant v=file->tag(i,audioFile::ONCACHE & ~audioFile::TITLEFP);
       QByteArray n = editors[i]->metaObject()->userProperty().name();
	   editors[i]->setProperty(n, v);
    }
  
    commentL=new QTextEdit(this);
    commentL->setPlainText(file->tag(COMMENT,audioFile::ONCACHE).toString());
        
    tagW=new QWidget(this);
    QFormLayout *form = new QFormLayout();
    form->setLabelAlignment(Qt::AlignLeft);

    year.setText(tr("Year:") );

    QHBoxLayout *hLayout=new QHBoxLayout();
    hLayout->addWidget(editors[TRACK] );
    hLayout->addWidget(&year);
    hLayout->addWidget(editors[YEAR]);

    form->addRow(tr("Title: "),editors[TITLE]);
    form->addRow(tr("Album: "),editors[ALBUM]);    
    form->addRow(tr("Artist: "),editors[ARTIST]);
    form->addRow(tr("Lead Artist: "),editors[LEAD_ARTIST]);
    form->addRow(tr("Genre:"),editors[GENRE]);
    form->addRow(tr("Composer: "),editors[COMPOSER]);
    form->addRow(tr("Track:"),hLayout);
    form->addRow(tr("Comment "),commentL);

    tagW->setLayout(form);    
}

void editTrackContent::infoInit()
{
    infoW=new QWidget(this);       
    
    QFormLayout *form = new QFormLayout();
    form->setLabelAlignment(Qt::AlignLeft);
    
    lengthF.setText("<b>"+prettyLength(file->tag(LENGTH).toInt() )+"</b>" );
    form->addRow(tr("length: "),&lengthF);

    bitRateF.setText("<b>"+file->tag(BITRATE).toString()+"</b>" );
    form->addRow(tr("Bit rate: "),&bitRateF);

    sizeF.setText("<b>"+prettySize(file->size() )+"</b>" );
    form->addRow(tr("Size: "),&sizeF);

    formatF.setText("<b>"+file->format()+"</b>" );
    form->addRow(tr("Format: "),&formatF);

    infoW->setLayout(form);
}

void editTrackContent::save()
{
	 QList<int> tags;
	 QList<QVariant> values;
      
     for(int i=0;i<FRAME_NUM;i++)
	 {
		if(editors[i]==0)
		{
		  continue;
		}
		QByteArray n = editors[i]->metaObject()->userProperty().name();
        QVariant v=editors[i]->property(n);
		if(v != file->tag(i,audioFile::ONCACHE | ~audioFile::TITLEFP ) )
		{	
		    qDebug()<<"editing "<<views::tagName(i);
		    tags<<i;
		    values<<v;
		}
	 }
	 
	
	if (commentL->toPlainText() != file->tag(COMMENT,audioFile::ONCACHE ).toString() )
	{
        qDebug()<<"editing comment";
	   tags<<COMMENT;
	   values<<QVariant(commentL->toPlainText() );        
	}
        
	file->setTags(tags,values);
}

void editTrackContent::clicked(QAbstractButton * button)
{
    if (buttons->buttonRole(button)==QDialogButtonBox::AcceptRole)
    {
        save();
        unload();
    }
    if (buttons->buttonRole(button)==QDialogButtonBox::ApplyRole)
    {
        save();
    }
    if (buttons->buttonRole(button)==QDialogButtonBox::RejectRole)
    {
        unload();

    }
}

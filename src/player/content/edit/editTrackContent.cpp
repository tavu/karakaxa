#include"editTrackContent.h"
#include <QHBoxLayout>
#include<QPushButton>
#include<QPainter>
#include<QFormLayout>

using namespace core;
using namespace views;
#define SIZE 150 ,170

editTrackContent::editTrackContent(QString url,QWidget *parent)
        :abstractContent(parent)
{
    file=new audioFile(url);
    file->load(audioFile::LOAD_FILE);

    path=new QLineEdit(file->path(),this);
    path->setContextMenuPolicy(Qt::NoContextMenu);

    cw=new coverWidget(this);
    cw->setSize(decor->coverSize());
    cw->setCover(file->cover());

    infoInit();
    tagInit();
    buttons=new QDialogButtonBox(QDialogButtonBox::Ok|QDialogButtonBox::Apply|QDialogButtonBox::Cancel,Qt::Horizontal,this);
    stars=new views::ratingWidget(this);
    stars->setRating(file->tag(RATING,audioFile::ONCACHE).toInt() );
    
    QVBoxLayout *vLayout=new QVBoxLayout();
    QGridLayout *gr=new QGridLayout();

    stars->setFixedSize(140,30);
//     stars->setFixedHeight(30);
    gr->addWidget(cw,0,0,2,1);
    gr->addWidget(stars,0,1,Qt::AlignLeft);
    gr->addWidget(infoW,1,1);
    gr->addItem(new QSpacerItem(1,1,QSizePolicy::Ignored,QSizePolicy::Ignored),2,1);
    vLayout->addLayout(gr);

    vLayout->addWidget(tagW);
    vLayout->addWidget(path);
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
    
    tagW=new QWidget(this);
    QFormLayout *form = new QFormLayout();
    form->setLabelAlignment(Qt::AlignLeft);

    titleL=new QLineEdit(file->tag(TITLE,audioFile::ONCACHE & ~audioFile::TITLEFP).toString(),this );
    albumL=new QLineEdit(file->tag(ALBUM,audioFile::ONCACHE).toString(),this );
    artistL=new QLineEdit(file->tag(ARTIST,audioFile::ONCACHE).toString(),this );
    leadArtistL=new QLineEdit(file->tag(LEAD_ARTIST,audioFile::ONCACHE).toString(),this );
    commentL=new QTextEdit(this );
    commentL->setPlainText(file->tag(COMMENT,audioFile::ONCACHE).toString());
    composerL=new QLineEdit(file->tag(COMPOSER,audioFile::ONCACHE).toString(),this );
    genreL=new QLineEdit(file->tag(GENRE,audioFile::ONCACHE).toString(),this );
    yearL=new QSpinBox(this );
    trackL=new QSpinBox(this );

    yearL->setValue(file->tag(YEAR,audioFile::ONCACHE).toInt() );
    trackL->setValue(file->tag(TRACK,audioFile::ONCACHE).toInt() );

    year.setText(tr("Year:") );

    QHBoxLayout *hLayout=new QHBoxLayout();
    hLayout->addWidget(trackL);
    hLayout->addWidget(&year);
    hLayout->addWidget(yearL);
    hLayout->addWidget(yearL);

    form->addRow(tr("Title: "),titleL);
    form->addRow(tr("Album: "),albumL);    
    form->addRow(tr("Artist: "),artistL);
    form->addRow(tr("Lead Artist: "),leadArtistL);
    form->addRow(tr("Genre:"),genreL);
    form->addRow(tr("Composer: "),composerL);
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
  
    if (titleL->text()!=file->tag(TITLE,audioFile::ONCACHE | ~audioFile::TITLEFP ).toString() )
    {
        qDebug()<<"edit title";
	   tags<<TITLE;
	   values<<QVariant(titleL->text() );
    }

    if (albumL->text()!=file->tag(ALBUM,audioFile::ONCACHE ).toString() )
    {
        qDebug()<<"edit album";
	   tags<<ALBUM;
	   values<<QVariant(albumL->text() );
    }

    if (artistL->text()!=file->tag(ARTIST,audioFile::ONCACHE ).toString() )
    {
        qDebug()<<"edit artist";
	   tags<<ARTIST;
	   values<<QVariant(artistL->text() ); 
    }
    
    
    if (leadArtistL->text()!=file->tag(LEAD_ARTIST,audioFile::ONCACHE ).toString() )
    {
        qDebug()<<"edit leadArtist ";
	   qDebug()<<"S "<<file->tag(LEAD_ARTIST).toString();
	   qDebug()<<"S "<<leadArtistL->text() ;
	   tags<<LEAD_ARTIST;
	   values<<QVariant(leadArtistL->text() );        
    }


    if (composerL->text()!=file->tag(COMPOSER,audioFile::ONCACHE ).toString() )
    {
        qDebug()<<"edit composer";
	   tags<<COMPOSER;
	   values<<QVariant(composerL->text() );        
    }
    
    if (genreL->text() != file->tag(GENRE,audioFile::ONCACHE ).toString() )
    {
        qDebug()<<"edit genre";
	   tags<<GENRE;
	   values<<QVariant(genreL->text() );        
    }

    if (commentL->toPlainText() != file->tag(COMMENT,audioFile::ONCACHE ).toString() )
    {
        qDebug()<<"edit comment";
	   tags<<COMMENT;
	   values<<QVariant(commentL->toPlainText() );        
    }
    
    if(yearL->value() != file->tag(YEAR,audioFile::ONCACHE ).toInt() )
    {
	 qDebug()<<"edit year";
	 tags<<YEAR;
	 values<<QVariant(yearL->value() );
    }
    
    if(trackL->value() != file->tag(TRACK,audioFile::ONCACHE ).toInt() )
    {
	   qDebug()<<"edit track";
	   tags<<TRACK;
	   values<<QVariant(trackL->value() );	
    }
    
    if(stars->rating() != file->tag(RATING,audioFile::ONCACHE ).toInt() )
    {
	   qDebug()<<"edit rating";
	   qDebug()<<"R "<<file->tag(RATING,audioFile::ONCACHE ).toInt();
	   qDebug()<<"R "<<stars->rating();
	   tags<<RATING;
	   values<<QVariant(stars->rating() );	   
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

#include"editTrackContent.h"
#include <QHBoxLayout>
#include<QPushButton>
#include<QPainter>
#include<QFormLayout>

using namespace player;
#define SIZE 150 ,170

editTrackContent::editTrackContent(QString url,QWidget *parent)
        :abstractContent(parent)
{
    file=new audioFile(url);

    path=new QLineEdit(file->path(),this);
    path->setContextMenuPolicy(Qt::NoContextMenu);

    cw=new player::coverWidget(this);
    cw->setSize(decor.coverSize());
    cw->setCover(file->cover());

    infoInit();
    tagInit();
    buttons=new QDialogButtonBox(QDialogButtonBox::Ok|QDialogButtonBox::Apply|QDialogButtonBox::Cancel,Qt::Horizontal,this);
    QHBoxLayout *hLayout=new QHBoxLayout();
    QVBoxLayout *vLayout=new QVBoxLayout();
    
    hLayout->addWidget(cw);
    hLayout->addWidget(infoW);
    hLayout->addStretch();

    vLayout->addLayout(hLayout);

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

    int flag=audioFile::ONCACHE|audioFile::LOAD_FILE;
    
    titleL=new QLineEdit(file->tag(TITLE,flag).toString().trimmed(),this );
    albumL=new QLineEdit(file->tag(ALBUM,flag).toString().trimmed(),this );
    artistL=new QLineEdit(file->tag(ARTIST,flag).toString().trimmed(),this );
    leadArtistL=new QLineEdit(file->tag(LEAD_ARTIST,flag).toString().trimmed(),this );
    commentL=new QTextEdit(file->tag(COMMENT,flag).toString().trimmed(),this );
    composerL=new QLineEdit(file->tag(COMPOSER,flag).toString().trimmed(),this );
    genreL=new QLineEdit(file->tag(GENRE,flag).toString().trimmed(),this );
    yearL=new QSpinBox(this );
    trackL=new QSpinBox(this );

    //the value would be valid until the next milenioum
    yearL->setMaximum(3000);
    yearL->setValue(file->tag(YEAR,flag).toInt() );
    trackL->setValue(file->tag(TRACK,flag).toInt() );

    year.setText(tr("Year:") );

    QHBoxLayout *hLayout=new QHBoxLayout();
    hLayout->addWidget(trackL);
//      hLayout->addStretch();
    hLayout->addWidget(&year);
    hLayout->addWidget(yearL);
    hLayout->addWidget(yearL);

    form->addRow(tr("Title: "),titleL);
    form->addRow(tr("Album: "),albumL);
    form->addRow(tr("Genre "),genreL);
    form->addRow(tr("Artist: "),artistL);
    form->addRow(tr("Lead Artist: "),leadArtistL);
    form->addRow(tr("Composer: "),composerL);
    form->addRow(tr("Track:"),hLayout);
    form->addRow(tr("Comment "),commentL);

    tagW->setLayout(form);
    
    connect(rating,SIGNAL(ratingChanged(int) ),rating,SLOT(setRating(int) ) );
}

void editTrackContent::infoInit()
{
    infoW=new QWidget(this);
    QFormLayout *form = new QFormLayout();
    
    form->setLabelAlignment(Qt::AlignLeft);
    
    int flag=audioFile::ONCACHE|audioFile::LOAD_FILE;
    rating=new player::starWidget(this);
    rating->setRating(file->tag(RATING,flag).toInt());
    form->addRow(rating);
    
    lengthF.setText("<b>"+prettyLength(file->tag(LENGTH).toInt() )+"</b>" );
    form->addRow(tr("length: "),&lengthF);

    bitRateF.setText("<b>"+file->tag(BITRATE).toString().trimmed()+"</b>" );
    form->addRow(tr("Bit rate: "),&bitRateF);
    sizeF.setText("<b>"+prettySize(file->size() )+"</b>" );
    form->addRow(tr("Size: "),&sizeF);
    formatF.setText("<b>"+file->format()+"</b>" );
    form->addRow(tr("Format: "),&formatF);
    infoW->setLayout(form);
}

void editTrackContent::save()
{
    using namespace player;    

    QList<int> tags;
    QList<QVariant>values;
    QString s;
    int f=audioFile::DEFAULTF|~audioFile::TITLEFP;  
    
    s=titleL->text().trimmed();
    if (s.compare(file->tag(TITLE,f).toString().trimmed() )!=0 )
    {
        qDebug()<<"edit title";
	tags<<TITLE;
	values<<QVariant(s);
    }

    s=albumL->text().trimmed();
    if ( s.compare(file->tag(ALBUM,f).toString().trimmed() )!=0 )
    {
        qDebug()<<"edit album "<<s;
	tags<<ALBUM;
	values<<QVariant(s);
    }
    
    s=artistL->text().trimmed();
    if (s.compare(file->tag(ARTIST,f).toString().trimmed() )!=0)
    {
        qDebug()<<"edit artist";
	tags<<ARTIST;
	values<<QVariant(s);

    }
    
    s=leadArtistL->text().trimmed();
    if (s.compare(file->tag(LEAD_ARTIST,f).toString().trimmed() )!=0)
    {
        qDebug()<<"edit leadArtist";
 	qDebug()<<leadArtistL->text().trimmed();
 	qDebug()<<file->tag(LEAD_ARTIST).toString().trimmed();
	tags<<LEAD_ARTIST;
	values<<QVariant(s);

    }

    s=composerL->text().trimmed();
    if (s.compare(file->tag(COMPOSER,f).toString().trimmed() )!=0)
    {
        qDebug()<<"edit composer";
	qDebug()<<"val "<<s;
	qDebug()<<"comp "<<file->tag(COMPOSER,f).toString().trimmed();
	tags<<COMPOSER;
	values<<QVariant(s);

    }
    
    s=genreL->text().trimmed();
    if (s.compare(file->tag(GENRE,f).toString().trimmed() )!=0 )
    {
        qDebug()<<"edit genre";
	tags<<GENRE;
	values<<QVariant(s);

    }

    s=commentL->toPlainText().trimmed();
    if (s.compare(file->tag(COMMENT,f).toString().trimmed())!=0 )
    {
        qDebug()<<"edit comment";
	tags<<COMMENT;
	values<<QVariant(s);
    }
    
    int num=yearL->value();
    if (num != file->tag(YEAR,f).toInt() )
    {
        qDebug()<<"edit year";
	tags<<YEAR;
	values<<QVariant(num);
    }

    num=trackL->value();
    if (num != file->tag(TRACK,f).toInt() )
    {
        qDebug()<<"edit track";
	tags<<TRACK;
	values<<QVariant(num);
    }
    
    num=rating->rating();
    if (num != file->tag(RATING,f).toInt() )
    {
        qDebug()<<"edit track";
	tags<<RATING;
	values<<QVariant(num);
    }    
    
    file->setTags(tags,values);
}

void editTrackContent::clicked(QAbstractButton * button)
{
    if (buttons->buttonRole(button)==QDialogButtonBox::AcceptRole)
    {
        save();
        contentHandlr.removeContent(this);
    }
    if (buttons->buttonRole(button)==QDialogButtonBox::ApplyRole)
    {
        save();
    }
    if (buttons->buttonRole(button)==QDialogButtonBox::RejectRole)
    {
        contentHandlr.removeContent(this);

    }
}

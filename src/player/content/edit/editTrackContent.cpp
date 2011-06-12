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

    titleL=new QLineEdit(file->tag(TITLE,audioFile::ONCACHE & ~audioFile::TITLEFP).toString(),this );
    albumL=new QLineEdit(file->tag(ALBUM,audioFile::ONCACHE).toString(),this );
    artistL=new QLineEdit(file->tag(ARTIST,audioFile::ONCACHE).toString(),this );
    leadArtistL=new QLineEdit(file->tag(LEAD_ARTIST,audioFile::ONCACHE).toString(),this );
    commentL=new QTextEdit(file->tag(COMMENT,audioFile::ONCACHE).toString(),this );
    composerL=new QLineEdit(file->tag(COMPOSER,audioFile::ONCACHE).toString(),this );
    genreL=new QLineEdit(file->tag(GENRE,audioFile::ONCACHE).toString(),this );
    yearL=new QSpinBox(this );
    trackL=new QSpinBox(this );

    yearL->setValue(file->tag(YEAR,audioFile::ONCACHE).toInt() );
    trackL->setValue(file->tag(TRACK,audioFile::ONCACHE).toInt() );

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
}

void editTrackContent::infoInit()
{
    infoW=new QWidget(this);
    QFormLayout *form = new QFormLayout();
    form->setLabelAlignment(Qt::AlignLeft);

    lengthF.setText("<b>"+prettyLength(file->tag(LENGTH).toInt() )+"</b>" );
    form->addRow(tr("length: "),&lengthF);

//      bitRate.setText("Bit rate:");
    bitRateF.setText("<b>"+file->tag(BITRATE).toString()+"</b>" );
    form->addRow(tr("Bit rate: "),&bitRateF);
//      gl->setHorizontalSpacing(0);
//      gl->addWidget(&bitRate,1,0);
//      gl->addWidget(&bitRateF,1,1,Qt::AlignLeft);

//      size.setText("Size:");
    sizeF.setText("<b>"+prettySize(file->size() )+"</b>" );
    form->addRow(tr("Size: "),&sizeF);
//      gl->addWidget(&size,2,0);
//      gl->addWidget(&sizeF,2,1);

//      format.setText("Format:"+file->format()+"<\b>");
    formatF.setText("<b>"+file->format()+"</b>" );
    form->addRow(tr("Format: "),&formatF);
//      gl->addWidget(&format,3,0);
//      gl->addWidget(&formatF,3,1);



//      gl->addWidget(&length,0,0);
//      gl->addWidget(&lengthF,0,1);

    infoW->setLayout(form);
}

void editTrackContent::save()
{
//     QList<int> tags,QList<QVariant> values
  
    if (titleL->text().compare(file->tag(TITLE,audioFile::ONCACHE | ~audioFile::TITLEFP ).toString() )!=0)
    {
        qDebug()<<"edit title";
        file->setTag(TITLE,titleL->text() );
    }

    if (albumL->text()!=file->tag(ALBUM).toString() )
    {
        qDebug()<<"edit album";
// 	qDebug()<<file->tag(ALBUM).toString()<<"	"<<albumL->text();
        file->setTag(ALBUM,albumL->text() );
    }

    if (artistL->text()!=file->tag(ARTIST).toString() )
    {
        qDebug()<<"edit artist";
        file->setTag(ARTIST,artistL->text() );
    }
    
    
    if (leadArtistL->text()!=file->tag(LEAD_ARTIST).toString() )
    {
        qDebug()<<"edit leadArtist";
        file->setTag(LEAD_ARTIST,leadArtistL->text() );
    }


    if (composerL->text()!=file->tag(COMPOSER).toString() )
    {
        qDebug()<<"edit composer";
        file->setTag(COMPOSER,composerL->text() );
    }
    
    if (genreL->text() != file->tag(GENRE).toString() )
    {
        qDebug()<<"edit genre";
        file->setTag(GENRE,genreL->text() );
    }

    if (commentL->toPlainText() != file->tag(COMMENT).toString() )
    {
        qDebug()<<"edit comment";
        file->setTag(COMMENT,commentL->toPlainText() );
    }
    
    if(yearL->value() != file->tag(YEAR).toInt() )
    {
	file->setTag(YEAR,QVariant(yearL->value() ) );
    }
    
    if(trackL->value() != file->tag(TRACK).toInt() )
    {
	file->setTag(TRACK,QVariant(trackL->value() ) );
    }
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

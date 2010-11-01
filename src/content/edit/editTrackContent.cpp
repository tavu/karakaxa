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
    file=audioFile::getAudioFile(url);

//       if(!file->getError().isNull)
//      {
// 	 return;
//      }
//
    path=new QLineEdit(file->getPath(),this);
    path->setContextMenuPolicy(Qt::NoContextMenu);
//      path.setText(file->getPath() );
//      path.setTextInteractionFlags(Qt::TextBrowserInteraction);
//      path.setWordWrap(true);
//      cw->setSize(SIZE);
    cw=new player::coverWidget(file->cover(),this);
    cw->setSize(SIZE);

    infoInit();
    tagInit();
    buttons=new QDialogButtonBox(QDialogButtonBox::Ok|QDialogButtonBox::Apply|QDialogButtonBox::Cancel,Qt::Horizontal,this);
    QHBoxLayout *hLayout=new QHBoxLayout();
    QVBoxLayout *vLayout=new QVBoxLayout();


    hLayout->addWidget(cw);
    hLayout->addWidget(infoW);

    vLayout->addLayout(hLayout);

    vLayout->addWidget(tagW);
    vLayout->addWidget(path);
    vLayout->addWidget(buttons);

    setLayout(vLayout);


    connect(buttons, SIGNAL(clicked(QAbstractButton* ) ), this, SLOT(clicked(QAbstractButton*) ));

}

QString editTrackContent::name() const
{
    return tr("Edit track");
}

editTrackContent::~editTrackContent()
{
//       delete file;
    audioFile::releaseAudioFile(file);

//      delete titleL;
//      delete albumL;
//      delete leadArtistL;
//      delete commentL;
//      delete composerL;
}

void editTrackContent::tagInit()
{

    tagW=new QWidget(this);
    QFormLayout *form = new QFormLayout();
    form->setLabelAlignment(Qt::AlignLeft);

    titleL=new QLineEdit(file->tag(TITLE,audioFile::DEFAULTF & ~audioFile::TITLEFP).toString(),this );
    albumL=new QLineEdit(file->tag(ALBUM,audioFile::ONFILE).toString(),this );
    leadArtistL=new QLineEdit(file->tag(LEAD_ARTIST).toString(),this );
    commentL=new QTextEdit(file->tag(COMMENT).toString(),this );
    composerL=new QLineEdit(file->tag(COMPOSER).toString(),this );
    genreL=new QLineEdit(file->tag(GENRE).toString(),this );
    yearL=new QSpinBox(this );
    trackL=new QSpinBox(this );

    yearL->setValue(file->tag(YEAR).toInt() );
    trackL->setValue(file->tag(TRACK).toInt() );

//      QFormLayout *form2 = new QFormLayout();
    QFormLayout *form3 = new QFormLayout();

//      form2->addRow(tr("Track: "),trackL);
    form3->addRow(tr("Year: "),yearL);
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
    using namespace player;


    if (titleL->text()!=file->tag(TITLE,audioFile::DEFAULTF & ~audioFile::TITLEFP ).toString() )
    {
        qDebug()<<"edit title";
        file->setTitle(titleL->text() );
    }

    if (albumL->text()!=file->tag(ALBUM).toString() )
    {
        qDebug()<<"edit album";
        file->setAlbum(albumL->text() );
    }

    if (leadArtistL->text().compare(file->tag(LEAD_ARTIST).toString() )!=0)
    {
        qDebug()<<"edit leadArtist";
        file->setLeadArtist(leadArtistL->text() );
    }

    if (composerL->text().compare(file->tag(COMPOSER).toString() )!=0)
    {
        qDebug()<<"edit composer";
        file->setComposer(composerL->text() );
    }

    if (genreL->text()!=file->tag(GENRE).toString() )
    {
        qDebug()<<"edit genre";
        file->setGenre(genreL->text() );
    }

    if (commentL->text().compare(file->tag(COMMENT).toString())!=0 )
    {
        qDebug()<<"edit comment";
        file->setComment(commentL->text() );
    }

    return;
}

void editTrackContent::clicked(QAbstractButton * button)
{
    if (buttons->buttonRole(button)==QDialogButtonBox::AcceptRole)
    {
        save();
        contentHandlr->removeContent(this);
    }
    if (buttons->buttonRole(button)==QDialogButtonBox::ApplyRole)
    {
        save();
    }
    if (buttons->buttonRole(button)==QDialogButtonBox::RejectRole)
    {
        contentHandlr->removeContent(this);

    }
}

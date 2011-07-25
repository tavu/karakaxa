#ifndef EDITTRACK_H
#define EDITTRACK_H

#include<QLabel>
#include <QLineEdit>
#include <QGridLayout>
#include<QTextEdit>
#include<QDialogButtonBox>
#include<core.h>
#include<views.h>
#include <QSpinBox>
#include<core.h>
class editTrackContent :public core::abstractContent
{
    Q_OBJECT
public:
    editTrackContent(QString url,QWidget *parent=0);
    ~editTrackContent();

    QString name() const;
    	
    QIcon icon() const	
    {	
	   return KIcon("document-edit");
    }

private:

    inline void  		tagInit();
    inline void  		infoInit();

    QWidget 			*infoW;
    QWidget 			*tagW;
    views::coverWidget 	*cw;


    audioFiles::audioFile *file;


    QLabel lengthF;
    QLabel bitRateF;
    QLabel sizeF;
    QLabel formatF;
    QLabel year;

    QLineEdit *path;


    QLineEdit *titleL;
    QLineEdit *albumL;
    QLineEdit *artistL;
    QLineEdit *leadArtistL;
    QTextEdit *commentL;
    QLineEdit *composerL;
    QLineEdit *genreL;
    QSpinBox *yearL;
    QSpinBox *trackL;

    QDialogButtonBox *buttons;

    views::ratingWidget *stars;

public slots:

    void save();
    void clicked(QAbstractButton * button);


};

class editTrackMenu :public core::abstractMenu
{
    Q_OBJECT
    
    public:
      editTrackMenu()
      {
	  act=new QAction(KIcon("document-edit"),tr("Edit track information"),this );
	  connect(act,SIGNAL(triggered(bool)),this,SLOT(activated()) );
      }
      
      bool canShow(QUrl &u ,bool multFiles)
      {
		if(core::isAudio(u.toLocalFile() ) )
		{
		    s=u.toLocalFile();
		    return true;
		}
		return false;
      }
      
      QAction* action()
      {
		return act;
      }
    
    private:
      QAction *act;
      QString s;
      
    public slots:
	void activated()
	{
	    editTrackContent *c=new editTrackContent(s);
	    core::contentHdl->addContent(c,true);
	}
	
};
#endif

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
class editTrackContent :public core::abstractContent
{
    Q_OBJECT
public:
    editTrackContent(QString url,QWidget *parent=0);
    ~editTrackContent();

    QString name() const;

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


public slots:

    void save();
    void clicked(QAbstractButton * button);


};
#endif

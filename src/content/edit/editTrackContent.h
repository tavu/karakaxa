#ifndef EDITTRACK_H
#define EDITTRACK_H

#include<player.h>
#include<audioFile.h>
#include<QLabel>
#include <QLineEdit>
#include <QGridLayout>
#include<QTextEdit>
#include<QDialogButtonBox>
#include<player.h>
#include <QSpinBox>
class editTrackContent :public abstractContent
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
    player::coverWidget 	*cw;


    audioFiles::audioFile *file;


    QLabel lengthF;
    QLabel bitRateF;
    QLabel sizeF;
    QLabel formatF;
    QLabel year;

    QLineEdit *path;

    player::starWidget *rating;
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

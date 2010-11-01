#ifndef CONFIGURECONTENT_H
#define CONFIGURECONTENT_H
#include<player.h>
#include<QFileDialog>
#include<QListView>
#include <QStringListModel>
#include<QGroupBox>
#include"scanTread.h"
#include<QLabel>
#include<QProgressBar>
#include <QCheckBox>
class configureContent :public abstractContent
{
    Q_OBJECT
public:
    configureContent(QWidget *parent=0);
    QString name() const;
private:
    QFileDialog 		*fDialog;
    QListView   		*listV;
    QStringListModel 	*model;
    QStringList		sList;
    QGroupBox 		*groupB;

    QPushButton 		*scanB;
    QPushButton 		*cancelB;
    QProgressBar 	*bar;
    QLabel		l;
    QLabel		info;
    scanTread 		*scThread;
    QCheckBox		*chBox;


    void libconfInit();


private slots:
    void addLibraryFolder();
    void scanDone();
    void scan();
    void prepare(const int num);

};
#endif

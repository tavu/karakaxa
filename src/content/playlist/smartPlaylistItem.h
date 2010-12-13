#ifndef SMARTPLAYLISTITEM_H
#define SMARTPLAYLISTITEM_H
#include <QTreeWidgetItem>
#include<player.h>
#include<QComboBox>
#include<QLineEdit>
#include<QSpinBox>
#include <QValidator>
#include <QCheckBox>
#include<QDomElement>
// #define MATCHTYPE 0
// #define TAGTYPE   1

class validator :public QValidator
{
public:
    QValidator::State validate ( QString & input, int & pos ) const;
};
using namespace player;
class smartPlaylistItem :public QObject, public QTreeWidgetItem
{
    Q_OBJECT
    public:
	enum Type
	{
	    MATCHTYPE=0,
	    TAGTYPE
	};

	smartPlaylistItem( QTreeWidgetItem * parent,Type t);
	smartPlaylistItem( QTreeWidget * parent);
    // 	  ~smartPlaylistItem();
    // 	  QVariant data ( int column, int role ) const;
    // 	  char type();
    // 	  void setTag();
    // 	  void setValue();
    // 	  void setFilde();
    //      private:

    // 	  char _type;

    // 	  QString getQuery();

    private:
	QComboBox *box1;
	QComboBox *box2;
	QLineEdit *lineE;
	QSpinBox   *spin;
	validator  *val;
	QCheckBox  *ch;

	void initTag();
	void initMatch();

    private slots:

	void setupFilde(int);
    public slots:
	QString getQuery();
	QDomElement xml();
    // 	  void setWidget();


};

#endif

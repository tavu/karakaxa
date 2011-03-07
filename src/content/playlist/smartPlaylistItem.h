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
#include <QSpinBox>

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

	smartPlaylistItem( QTreeWidgetItem * parent, Type t);
 	smartPlaylistItem( QTreeWidget * parent);
	void setXml(QDomElement e);
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
	QComboBox *tagSelector;
	QComboBox *equalSelector;
	QLineEdit *lineE;
// 	QSpinBox   *spin;
	QCheckBox  *ch;
	QSpinBox  *tagsSpin;

	void initTag();
	void initMatch();

    private slots:

	void setupFilde(int);
    public slots:
// 	QString getQuery();
	QDomElement xml();
    // 	  void setWidget();


};

#endif

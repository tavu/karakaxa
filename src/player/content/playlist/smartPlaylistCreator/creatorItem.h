#ifndef CREATORITEM_H
#define CREATORITEM_H
#include <QTreeWidgetItem>

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

class creatorItem :public QObject, public QTreeWidgetItem
{
    Q_OBJECT
    public:
	enum Type
	{
	    MATCHTYPE=0,
	    TAGTYPE
	};

	creatorItem(creatorItem * parent, Type t);
 	creatorItem(QDomDocument &docum,QTreeWidget * parent);
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
    
	QDomDocument document()
	{
	    return doc;
	}

    private:
	QComboBox *tagSelector;
	QComboBox *equalSelector;
	QLineEdit *lineE;
// 	QSpinBox   *spin;
	QCheckBox  *ch;
	QSpinBox  *tagsSpin;

	QDomDocument doc;
	
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

#ifndef QUERYGENERATION_H
#define QUERYGENERATION_H
#include<QString>
#include<../files/audioFile.h>
#include<QVector>
#include<QDebug>
// #include"../coreNamespace.h"
// using namespace core;
#include <QDomElement>

namespace core
{

class queryGrt :public QObject
{
    Q_OBJECT
    public:
	
      static const short int MATCHQ=0;
      static const short int TAGQ=1;
      
	enum equal
	{
	    EQUAL=0,
	    STARTS,
	    ENDS,
	    CONTAINS,
	    GREATER,
	    LESS
	};

	enum MATCH
	{
	    AND=0,
	    OR
	};
	
	class abstractQuery
	{
	    public:
		virtual QString text() const =0;
		virtual short int type() const =0;
		virtual bool isValid() const =0;
// 		virtual bool match(const audioFiles::audioFile &f) const =0;
		virtual abstractQuery * clone()=0;
// 		virtual QDomElement xml(QDomDocument &doc)=0;
		
	};
	
	class matchQuery :public abstractQuery
	{
	    public:
		matchQuery(MATCH m);
		~matchQuery();
		matchQuery(matchQuery *mq);
		
		short int type() const 
		{
		    return MATCHQ;
		}
		bool isValid() const;
		
		QString text() const;
		bool append(abstractQuery *q);
// 		bool match(const audioFiles::audioFile &f) const;
		abstractQuery * clone()
		{
		    return new matchQuery(this);
		}
		void clear();
		
	    private:
		bool valid;
		MATCH matchType;
		QList<abstractQuery*> queries;
		QString q;
	};
	
	class tagQuery :public abstractQuery
	{
	    public:
	      tagQuery();
	      tagQuery(int t,equal e,QVariant var,bool n=false);
	      tagQuery(tagQuery *t);
	      
	      short int type() const
	      {
		  return TAGQ;
	      }
	      bool isValid() const
	      {
		  return valid;
	      }
	      
	      bool isReverted() const
	      {
		  return revert;
	      }
	      
	      void setRevert(bool r)
	      {
		  revert=r;
	      }
	      
	      abstractQuery * clone()		
	      {
		  return new tagQuery(this);
	      }
// 	      QDomElement xml(QDomDocument &doc);
	      
	      void init(int t,equal e,QVariant var,bool n=false);
// 	      bool match(const audioFiles::audioFile &f);
	      QString text() const;
	    
	    private:
	      bool valid;
	      
	      int tag;
	      equal eq;
	      QVariant value;
	      bool revert;
	      QString q;
	};

	
	
    public:
	queryGrt(QObject *parent=0);
	queryGrt(core::queryGrt::abstractQuery* qe,QObject *parent=0);
	
	QString filter() const
	{
	    if(q==0)
	    {
		return QString();
	    }
	    return q->text();
	}
	
	const abstractQuery* query() const
	{
	    return q;
	}
	
	void setQuery(abstractQuery *qe)
	{
	    q=qe;
	    _needUpdate=true;
	}
	
	QString queryString() const
	{
	    if( q==0 || !q->isValid())
	    {
		return QString();
	    }
	    
	    return q->text().prepend("select distinct * from trackView where ");
	}
		
	QVector<audioFiles::audioFile*> result()
	{
	    return files;
	}
	
	audioFiles::audioFile* at(int n)
	{
	    if(n<0||n>=files.size() )
	    {
 		return 0;
	    }
	    
	    return files[n];
	}
	
	bool select();
// 	bool update();
	
	bool needUpdate()
	{
	    return _needUpdate;
	}
	
	int size()
	{
	    return files.size();
	}
	
    private:
	abstractQuery *q;
	QVector<audioFiles::audioFile*> files;
	bool _needUpdate;
	QMap<QString ,audioFiles::audioFile*> map;
	
    private slots:
	void setNeedUpdate()
	{
	    _needUpdate=true;
	}
	
	
    signals:
	void selectionMade();
	void inserted(audioFiles::audioFile,int pos);
	void removed(audioFiles::audioFile,int pos);
	

	
    public:
      
	struct album
	{
	  QString name;
	  int id;
	  QString cover;
	};
	typedef struct album album;

	//return all the albums
	static QList<album> albums();
	//return all the albums that has the files from q
	static QList<album> albums(abstractQuery *qe);
	
	//return all the albums from that artist and also contained in q
	static QList<album> albums(QString artist,abstractQuery *qe);

	//return all the album from that artists
	static QList<album> albums(QString artist);
	
	//return all tha artist
	static QStringList artists();
	//return all the artist that has the files from q
	static QStringList artists(const abstractQuery *qe);



    private:
	static QString tagToSql(int t);

};
};
#endif

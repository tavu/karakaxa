#ifndef QUERYGENERATION_H
#define QUERYGENERATION_H
#include<QString>
#include<../files/audioFile.h>
#include<QVector>
#include<QDebug>
// #include"../coreNamespace.h"
#include"album.h"
#include <QDomElement>
#include"queryThr.h"

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
	      virtual bool match(const audioFiles::audioFile &f) const =0;	
	      virtual abstractQuery * clone()=0; 
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

	 	bool match(const audioFiles::audioFile &f) const;
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
		      
		    void init(int t,equal e,QVariant var,bool n=false);
		    bool match(const audioFiles::audioFile &f) const;
		    QString text() const;
			    
		  private:
		    
		    bool valid;	    
		    int tag;	    
		    equal eq;	   
		    QVariant value;	   
		    bool revert;	   
		    QString q;	  
	};
    
    
	//class members
      
	queryGrt(QObject *parent=0);
	queryGrt(abstractQuery* qe,QObject *parent=0);
	
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
	    if(q!=0)
		delete q;
	    q=qe;
	    _needUpdate=true;
	}
	
	virtual QString queryString() const=0;
	virtual bool select()=0;
	
	bool needUpdate() const
	{
	    return _needUpdate;
	}
	
	static QString tagToSql(int t);
	
    protected:
	abstractQuery *q;
	bool _needUpdate;		
	
    protected slots:
	
	virtual void setNeedUpdate(const audioFiles::audioFile f);
      
	void setNeedUpdate()
	{
	    _needUpdate=true;
	}
	
    signals:
	void updateNeeded();

};




class filesQueryGrt :public queryGrt
{
    Q_OBJECT	
    public:
	filesQueryGrt(QObject *parent=0);
	filesQueryGrt(abstractQuery* qe,QObject *parent=0);	
	
		
	QString queryString() const
 	{
 	    if( q==0 || !q->isValid())
 	    {
 		return QString();
 	    }
 	    
 	    return q->text().prepend("select distinct * from trackView where ");
 	}
				
	QVector<audioFiles::audioFile> result()
	{
	    return thr.files;
	}
	
	//use this function after selectionMade signal
	audioFiles::audioFile at(int n)
	{
	    if(n<0||n>=thr.files.size() )
	    {
 		return audioFiles::audioFile();
	    }
	    
	    return thr.files[n];
	}
	
	bool select();
		
	int size()
	{
	    return thr.files.size();
	}
	
	int step()
	{
	    return thr.step;
	}
	
	void setStep(int n)
	{
	    thr.step=n;
	}
		
	
    private:
	queryThr thr;
	
    private slots:
	void selectionFinished();
	
    signals:
	void selectionCalled();
	void selectionMade();			
};

class tagQueryGrt :public queryGrt
{
    Q_OBJECT
    public:
	tagQueryGrt(QObject *parent=0) :queryGrt(parent),tag_(0)
	{
	}
	
	QString queryString() const;
	void setTag(int t)
	{
	    tag_=t;
	    _needUpdate=true;
	}
	
	int tag()
	{
	    return tag_;
	}
	
	bool select();
	QStringList result()
	{
	    return list;
	}
	
    private slots:
	void setNeedUpdate(const audioFiles::audioFile f);
	
    private:
	int tag_;
	QStringList list;
};

class artistQueryGrt :public queryGrt
{
    Q_OBJECT
    public:
	artistQueryGrt(QObject *parent=0) :queryGrt(parent)
	{
	}
	
	QString queryString() const;

	bool select();
	QStringList result()
	{
	    return list;
	}
	
    private slots:
	void setNeedUpdate(const audioFiles::audioFile f);
	
    private:
	QStringList list;
};

class albumQueryGrt :public queryGrt
{
    Q_OBJECT
    public:
	albumQueryGrt(QObject *parent=0) :queryGrt(parent)
	{
	}
	
	QString queryString() const;

	bool select();
	QList<albumEntry> result()
	{
	    return list;
	}
	
	void setArtist(const QString &a)
	{
	    artist_=a;
	    _needUpdate=true;	    
	}
	
	QString artist()
	{
	    return artist_;
	}
	
	QStringList albums()
	{
	    QStringList l;
	    l.reserve(list.size() );
	    foreach(albumEntry a,list)
	    {
		l.append(a.name);
	    }
	    return l;
	}
	
    private slots:
	void setNeedUpdate(const audioFiles::audioFile f);

    private:
	QList<albumEntry> list;
	QString artist_;
};


};
#endif

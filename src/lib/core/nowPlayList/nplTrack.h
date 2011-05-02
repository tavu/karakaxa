#ifndef NPLTRACK_H
#define NPLTRACK_H
// #include"../coreNamespace.h"
// #include"nplClass.h"
#include<QString>
#include"../files/tagsTable.h"
#include<QSharedPointer>

#define NPLAUDIOFILE	1
#define NPLSTREAM 	2


namespace core
{
    
class nplTrack;    
typedef QSharedPointer<core::nplTrack> nplPointer;
class nplTrack
{
    
    public:
	nplTrack();
	virtual ~nplTrack();
	virtual QVariant	artist();

	
	virtual QString 	title()=0 ;
	virtual QString 	path()=0 ;
	virtual int 		type()=0;
	virtual QVariant	tag(int t);
	virtual QString 	cover();
	virtual  bool 		isValid() const
	{
	    return ok;
	}
	virtual void 		play();
	virtual void 		finish();
	

  protected:
      bool ok;

      
  public:
      static nplPointer getNplTrack(const QString url);
      static nplPointer getNplTrack(const QUrl url);
};



};
#endif

#ifndef NPLTRACK_H
#define NPLTRACK_H
#include"../playerNamespace.h"
#include<QString>
#include"files/tagsTable.h"

#define NPLAUDIOFILE	1
#define NPLSTREAM 	2


namespace player
{
class nplTrack
{
    
    public:
	nplTrack();
	virtual ~nplTrack();
	virtual QVariant	artist()
	{
// 	    return QVariant();
	    return tag(ARTIST);
	}
	
	virtual QString 	title()=0 ;
	virtual QString 	path()=0 ;
	virtual int 		type()=0;
	virtual QVariant	tag(tagsEnum t);
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

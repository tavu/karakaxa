#ifndef NPLTRACK_H
#define NPLTRACK_H
#include"../playerNamespace.h"
#include<QString>

#define NPLAUDIOFILE	1
#define NPLSTREAM 	2

namespace player
{
class nplTrack
{
    
    public:
	nplTrack();
	virtual ~nplTrack();
	virtual QString 	title()=0 ;
	virtual QString 	path()=0 ;
	virtual int 		type()=0;
	virtual QVariant	tag(tagsEnum t);
	virtual QString 	cover();
	virtual  bool isValid() const
	{
	    return ok;
	}
	

  protected:
      bool ok;

      
  public:
      static nplPointer getNplTrack(const QString url);
};



};
#endif

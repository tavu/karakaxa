#ifndef NPLTRACK_H
#define NPLTRACK_H
#include"../playerNamespace.h"
#include<QString>
namespace player
{
class nplTrack
{
    public:
	nplTrack();
	virtual ~nplTrack();
	virtual QString 	title()=0 ;
	virtual QString 	path()=0 ;
	virtual QString 	type()=0;
	virtual QVariant	tag(tagsEnum t);
	
	virtual  bool isOk() const
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

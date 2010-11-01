#ifndef NPLTRACK_H
#define NPLTRACK_H

#include<QString>
namespace player
{
class nplTrack
{
public:
    nplTrack();
    virtual QString 	title()=0 ;
    virtual QString 	path()=0 ;
    virtual QString 	artist();
    virtual QString 	album()=0;
    virtual int	 	length();
    virtual int 		trackN() ;
    virtual QString 	type()=0;
    virtual  bool isOk() const
    {
        return ok;
    }

protected:
    bool ok;

};
};
#endif

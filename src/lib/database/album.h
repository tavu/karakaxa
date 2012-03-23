#ifndef ALBUM_H
#define ALBUM_H
#include<QString>
namespace database
{
  struct album
  {
	 QString 	name;
	 QString 	artist;
	 int 	    id;
	 QString 	cover; 
  };
  typedef struct album albumEntry; 
}
#endif
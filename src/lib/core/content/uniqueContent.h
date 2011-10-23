#ifndef UNIQUECONTENT_H
#define UNIQUECONTENT_H
#include"abstractContent.h"

/*
 * Uniqeu content are contets whitch we can have only one of that type loaded.
 * thats very usefull for the bookmarks.
 */
namespace core
{
  class uniqueContent :public abstractContent    
  {
      public:
	  uniqueContent(QWidget *parent=0):abstractContent(parent){};
	  virtual QString uniqueName() const=0;
  };
};
#endif
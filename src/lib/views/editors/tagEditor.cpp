#include"tagEditor.h"
#include"textEditor.h"
#include"ratingEditor.h"
#include"numberEditor.h"
#include"../../files/audioFiles.h"


views::tagEditor* views::tagEditor::getEditor(int tag,QWidget *parent)
{       
    using namespace audioFiles;
    switch (tag)
    {
	case ALBUM:
	{
	    return new textEditor(ALBUM,parent);
	}
	case TITLE:
	{
	    return new textEditor(ALBUM,parent);
	}
	case COMPOSER:
	{
	    return new textEditor(ALBUM,parent);
	}
	case GENRE:
	{
	    return new textEditor(ALBUM,parent);
	}
	case COMMENT:
	{
	    return new textEditor(ALBUM,parent);
	}
	case TRACK:
	{
	    return new numberEditor(TRACK,parent);
	}
	case YEAR:
	{
	    return new numberEditor(YEAR,parent);
	}
	case RATING:
	{
	    return new ratingEditor(parent);
	}
	case LEAD_ARTIST:
	{
	    return new textEditor(ALBUM,parent);
	}
	case ARTIST:
	{
	    return new textEditor(ALBUM,parent);
	}
	default:
	{
	    return 0;
	}
    }
  
}
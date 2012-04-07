#include"audioFilesSelf.h"
#include"tagsTable.h"

void audioFiles::init()
{
    qRegisterMetaType<audioFiles::tagChangesL>("audioFiles::tagChangesL");
    qRegisterMetaType<audioFiles::audioFile>("audioFiles::audioFile");    
    audioFiles::audioFilesSelf::_self=new audioFilesSelf;
}

void audioFiles::cleanUp()
{
    delete audioFilesSelf::_self;
}

audioFiles::audioFilesSelf* audioFiles::self()
{
    return audioFilesSelf::_self;
}

audioFiles::audioFilesSelf* audioFiles::audioFilesSelf::_self=0;

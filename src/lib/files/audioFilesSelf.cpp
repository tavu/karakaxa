#include"audioFilesSelf.h"

void audioFiles::init()
{
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

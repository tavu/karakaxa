#ifndef AUDIOFILESSELF_H
#define AUDIOFILESSELF_H
#include "audioFile.h"

namespace audioFiles
{
class audioFilesSelf :public QObject
{
    friend class audioFile;
    friend void init();
    friend audioFilesSelf* self();
    friend void cleanUp();

    Q_OBJECT
    public:
        audioFilesSelf(QObject *parent=0):QObject(parent){}

    private:
        void emitChanged(audioFile f)
        {
            emit changed(f);
        }
        static audioFilesSelf *_self;
        
    signals:
        void changed(audioFiles::audioFile f);
        
};

audioFilesSelf* self();
void init();
void cleanUp();

    
}

#endif


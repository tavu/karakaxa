#ifndef AUDIOFILESSELF_H
#define AUDIOFILESSELF_H
#include "audioFile.h"
#include <QEvent>

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
        audioFilesSelf(QObject *parent=0):QObject(parent)
        {      
        }

    private:
        void emitChanged(audioFile f);
        
        static audioFilesSelf *_self;
        
        void customEvent(QEvent* event);
        
        
        class chEvent :public QEvent
        {
            public:
                chEvent(audioFiles::audioFile f);
                
                audioFiles::audioFile file;
                    
        };
        
    signals:
        void changed(audioFiles::audioFile f);
};

audioFilesSelf* self();
void init();
void cleanUp();

    
}

#endif



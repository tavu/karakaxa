#ifndef FILEQUERYGRT_H
#define FILEQUERYGRT_H
#include "queryGeneration.h"

namespace database
{
    class filesQueryGrt :public queryGrt
    {
        Q_OBJECT
        public:
            filesQueryGrt(QObject *parent=0);
            filesQueryGrt(abstractQuery* qe,QObject *parent=0);


            QString queryString() const
            {
                if ( q==0 || !q->isValid())
                {
                    return QString();
                }

                return q->text().prepend("select distinct * from trackView where ");
            }

            QVector<audioFiles::audioFile> result()
            {
                return files;
            }

            //use this function after selectionMade signal
            audioFiles::audioFile at(int n)
            {
                if (n<0||n>=files.size() )
                {
                    return audioFiles::audioFile();
                }

                return files[n];
            }

            bool select();

            int size()
            {
                return files.size();
            }

            /*
            int step()
            {
                return thr.step;
            }

            void setStep(int n)
            {
                thr.step=n;
            }
			*/

        private:
//             queryThr thr;

			bool doSelect();

            void dbEvents(database::dbEventP e);
			
			QVector<audioFiles::audioFile> files;	
			QMap<QString ,audioFiles::audioFile> map;

//         private slots:
//             void selectionFinished();

        signals:
            void selectionCalled();
            void selectionMade();
    };


}

#endif

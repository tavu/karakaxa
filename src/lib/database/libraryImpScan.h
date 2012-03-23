#ifndef LIBRARYIMPORTERSCAN_H
#define LIBRARYIMPORTERSCAN_H
#include "libraryImporter.h"

namespace database
{
class libraryImpScan :public libraryImporter
{
    public:
        libraryImpScan(QObject *parent=0);

        inline void createTmpTable();
        void save();
};

}
#endif
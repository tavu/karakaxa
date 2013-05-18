#include"filesToDb.h"
#include<database/dbRecords/filesToDbImpl.h>
Basic::filesToDb* Basic::getFdb(QString path)
{
    return new database::filesToDbImpl(path);
    
}
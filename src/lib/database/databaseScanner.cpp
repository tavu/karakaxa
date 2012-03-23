#include"databaseScanner.h"
#include"database.h"

void database::databaseScanner::scan()
{
    db()->scan(this);
}


#include"databaseScanner.h"
#include"database.h"

void core::databaseScanner::scan()
{
    db->scan(this);
}


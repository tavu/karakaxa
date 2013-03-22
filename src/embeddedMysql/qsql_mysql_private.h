#include<QObject>
#include<QTextCodec>
#include<QVector>
#include <mysql/mysql.h>
#include<QVariant>



class QMYSQLDriverEmbedded;
class QMYSQLResult;
class QMYSQLDriverPrivate
{
public:
    QMYSQLDriverPrivate() : mysql(0),
#ifndef QT_NO_TEXTCODEC
        tc(QTextCodec::codecForLocale()),
#else
        tc(0),
#endif
        preparedQuerysEnabled(false) {}
    MYSQL *mysql;
    QTextCodec *tc;

    bool preparedQuerysEnabled;
};

class QMYSQLResultPrivate : public QObject
{
    Q_OBJECT
public:
    QMYSQLResultPrivate(const QMYSQLDriverEmbedded* dp, const QMYSQLResult* d);

    const QMYSQLDriverEmbedded* driver;
    MYSQL_RES *result;
    MYSQL_ROW row;
    const QMYSQLResult* q;

    int rowsAffected;

    bool bindInValues();
    void bindBlobs();

    bool hasBlobs;
    struct QMyField
    {
        QMyField()
            : outField(0), nullIndicator(false), bufLength(0ul),
              myField(0), type(QVariant::Invalid)
        {}
        char *outField;
        my_bool nullIndicator;
        ulong bufLength;
        MYSQL_FIELD *myField;
        QVariant::Type type;
    };

    QVector<QMyField> fields;

#if MYSQL_VERSION_ID >= 40108
    MYSQL_STMT* stmt;
    MYSQL_RES* meta;

    MYSQL_BIND *inBinds;
    MYSQL_BIND *outBinds;
#endif

    bool preparedQuery;

private Q_SLOTS:
    void driverDestroyed() { driver = NULL; }
};
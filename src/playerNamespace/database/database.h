#ifndef DATABASE_H
#define DATABASE_H
#include<QSqlDatabase>
#include<QSqlError>
#include<QSqlQuery>
#include<QVariant>
#include<QMessageBox>
#include<QObject>
#include "playerNamespace.h"
// #include"../nowPlayList/nplTrack.h"
namespace player
{
class database :public QObject
{
    Q_OBJECT
public:
    database();
    ~database();
    static QSqlDatabase getDatabase();
// 	  static QSqlQuery getLibraryFolders();
    static QStringList getLibraryFolders();


    const QString error();
    QSqlDatabase clone(const QString &s);
    QStringList getArtists(const QString &path);

    int trackViewHideValues();
    const QSqlQuery artist();
    const QSqlQuery artist(QString search);
    const QString trackTable();

    QSqlQuery albumQuery(QString artist);
    QSqlQuery albumQuery(QString artist,QString search);

    void update();
    static void toSqlSafe(QString &s);
private:


    static QSqlDatabase db;
    static bool createConnection();
    static bool isConnected;


signals:
    void changed();
};

}
#endif

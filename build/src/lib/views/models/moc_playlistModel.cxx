/****************************************************************************
** Meta object code from reading C++ file 'playlistModel.h'
**
** Created:
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../src/lib/views/models/playlistModel.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'playlistModel.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_views__playlistModel[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      33,   22,   21,   21, 0x09,
      60,   21,   21,   21, 0x09,
      78,   22,   21,   21, 0x09,
     105,   21,   21,   21, 0x09,
     139,  123,   21,   21, 0x09,
     168,   21,   21,   21, 0x09,
     184,   21,   21,   21, 0x09,
     197,   21,   21,   21, 0x09,
     213,   21,  208,   21, 0x09,
     230,  227,   21,   21, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_views__playlistModel[] = {
    "views::playlistModel\0\0first,size\0"
    "beginInsertTracks(int,int)\0endInsertTracks()\0"
    "beginRemoveTracks(int,int)\0endRemoveTracks()\0"
    "first,size,dest\0beginMoveTracks(int,int,int)\0"
    "endMoveTracks()\0beginClear()\0endClear()\0"
    "bool\0acceptDrops()\0on\0setAcceptDrops(bool)\0"
};

void views::playlistModel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        playlistModel *_t = static_cast<playlistModel *>(_o);
        switch (_id) {
        case 0: _t->beginInsertTracks((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: _t->endInsertTracks(); break;
        case 2: _t->beginRemoveTracks((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 3: _t->endRemoveTracks(); break;
        case 4: _t->beginMoveTracks((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 5: _t->endMoveTracks(); break;
        case 6: _t->beginClear(); break;
        case 7: _t->endClear(); break;
        case 8: { bool _r = _t->acceptDrops();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 9: _t->setAcceptDrops((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData views::playlistModel::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject views::playlistModel::staticMetaObject = {
    { &QAbstractListModel::staticMetaObject, qt_meta_stringdata_views__playlistModel,
      qt_meta_data_views__playlistModel, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &views::playlistModel::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *views::playlistModel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *views::playlistModel::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_views__playlistModel))
        return static_cast<void*>(const_cast< playlistModel*>(this));
    return QAbstractListModel::qt_metacast(_clname);
}

int views::playlistModel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QAbstractListModel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    }
    return _id;
}
QT_END_MOC_NAMESPACE

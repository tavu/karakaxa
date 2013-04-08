/****************************************************************************
** Meta object code from reading C++ file 'playlistItem.h'
**
** Created:
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../src/player/content/playlist/playlistItem.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'playlistItem.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_playlistFolder[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      18,   16,   15,   15, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_playlistFolder[] = {
    "playlistFolder\0\0e\0dbEvent(database::dbEventP)\0"
};

void playlistFolder::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        playlistFolder *_t = static_cast<playlistFolder *>(_o);
        switch (_id) {
        case 0: _t->dbEvent((*reinterpret_cast< database::dbEventP(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData playlistFolder::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject playlistFolder::staticMetaObject = {
    { &standardItem::staticMetaObject, qt_meta_stringdata_playlistFolder,
      qt_meta_data_playlistFolder, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &playlistFolder::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *playlistFolder::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *playlistFolder::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_playlistFolder))
        return static_cast<void*>(const_cast< playlistFolder*>(this));
    return standardItem::qt_metacast(_clname);
}

int playlistFolder::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = standardItem::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    }
    return _id;
}
QT_END_MOC_NAMESPACE

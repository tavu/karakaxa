/****************************************************************************
** Meta object code from reading C++ file 'filePlaylist.h'
**
** Created:
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../src/lib/core/playlist/filePlaylist.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'filePlaylist.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_core__filePlaylist[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      26,   20,   19,   19, 0x0a,
      54,   19,   49,   19, 0x0a,
      61,   19,   49,   19, 0x0a,
      73,   68,   49,   19, 0x0a,
      90,   19,   49,   19, 0x0a,
      98,   19,   49,   19, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_core__filePlaylist[] = {
    "core::filePlaylist\0\0pos,u\0"
    "insertUrl(int,QString)\0bool\0load()\0"
    "save()\0name\0rename(QString&)\0exist()\0"
    "create()\0"
};

void core::filePlaylist::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        filePlaylist *_t = static_cast<filePlaylist *>(_o);
        switch (_id) {
        case 0: _t->insertUrl((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 1: { bool _r = _t->load();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 2: { bool _r = _t->save();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 3: { bool _r = _t->rename((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 4: { bool _r = _t->exist();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 5: { bool _r = _t->create();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        default: ;
        }
    }
}

const QMetaObjectExtraData core::filePlaylist::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject core::filePlaylist::staticMetaObject = {
    { &playlist::staticMetaObject, qt_meta_stringdata_core__filePlaylist,
      qt_meta_data_core__filePlaylist, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &core::filePlaylist::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *core::filePlaylist::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *core::filePlaylist::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_core__filePlaylist))
        return static_cast<void*>(const_cast< filePlaylist*>(this));
    return playlist::qt_metacast(_clname);
}

int core::filePlaylist::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = playlist::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    return _id;
}
QT_END_MOC_NAMESPACE

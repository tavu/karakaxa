/****************************************************************************
** Meta object code from reading C++ file 'nplaylist.h'
**
** Created:
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../src/lib/core/nowPlayList/nplaylist.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'nplaylist.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_core__nplaylist[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      17,   16,   16,   16, 0x05,
      33,   16,   16,   16, 0x05,

 // slots: signature, parameters, type, tag, flags
      53,   16,   16,   16, 0x0a,
      72,   68,   16,   16, 0x0a,
      87,   16,   16,   16, 0x0a,
      96,   16,   16,   16, 0x08,
     112,   16,   16,   16, 0x08,
     128,  126,   16,   16, 0x08,
     156,  126,   16,   16, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_core__nplaylist[] = {
    "core::nplaylist\0\0cancelThreads()\0"
    "repeatChanged(bool)\0repeatToggle()\0"
    "pos\0duplicate(int)\0suffle()\0prepareToQuit()\0"
    "informTrack()\0,\0updateLengthInsert(int,int)\0"
    "updateLengthRemove(int,int)\0"
};

void core::nplaylist::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        nplaylist *_t = static_cast<nplaylist *>(_o);
        switch (_id) {
        case 0: _t->cancelThreads(); break;
        case 1: _t->repeatChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->repeatToggle(); break;
        case 3: _t->duplicate((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 4: _t->suffle(); break;
        case 5: _t->prepareToQuit(); break;
        case 6: _t->informTrack(); break;
        case 7: _t->updateLengthInsert((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 8: _t->updateLengthRemove((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData core::nplaylist::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject core::nplaylist::staticMetaObject = {
    { &playlist::staticMetaObject, qt_meta_stringdata_core__nplaylist,
      qt_meta_data_core__nplaylist, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &core::nplaylist::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *core::nplaylist::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *core::nplaylist::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_core__nplaylist))
        return static_cast<void*>(const_cast< nplaylist*>(this));
    return playlist::qt_metacast(_clname);
}

int core::nplaylist::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = playlist::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void core::nplaylist::cancelThreads()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void core::nplaylist::repeatChanged(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE

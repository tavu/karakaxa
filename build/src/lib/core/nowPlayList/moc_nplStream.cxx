/****************************************************************************
** Meta object code from reading C++ file 'nplStream.h'
**
** Created:
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../src/lib/core/nowPlayList/nplStream.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'nplStream.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_core__nplStream[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      35,   17,   16,   16, 0x09,
      72,   16,   16,   16, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_core__nplStream[] = {
    "core::nplStream\0\0newstate,oldstate\0"
    "stateCh(Phonon::State,Phonon::State)\0"
    "getMetaData()\0"
};

void core::nplStream::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        nplStream *_t = static_cast<nplStream *>(_o);
        switch (_id) {
        case 0: _t->stateCh((*reinterpret_cast< Phonon::State(*)>(_a[1])),(*reinterpret_cast< Phonon::State(*)>(_a[2]))); break;
        case 1: _t->getMetaData(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData core::nplStream::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject core::nplStream::staticMetaObject = {
    { &nplTrack::staticMetaObject, qt_meta_stringdata_core__nplStream,
      qt_meta_data_core__nplStream, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &core::nplStream::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *core::nplStream::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *core::nplStream::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_core__nplStream))
        return static_cast<void*>(const_cast< nplStream*>(this));
    return nplTrack::qt_metacast(_clname);
}

int core::nplStream::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = nplTrack::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE

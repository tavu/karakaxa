/****************************************************************************
** Meta object code from reading C++ file 'nplFile.h'
**
** Created:
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../src/lib/core/nowPlayList/nplFile.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'nplFile.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_core__nplFile[] = {

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
      15,   14,   14,   14, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_core__nplFile[] = {
    "core::nplFile\0\0emitCh()\0"
};

void core::nplFile::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        nplFile *_t = static_cast<nplFile *>(_o);
        switch (_id) {
        case 0: _t->emitCh(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData core::nplFile::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject core::nplFile::staticMetaObject = {
    { &nplTrack::staticMetaObject, qt_meta_stringdata_core__nplFile,
      qt_meta_data_core__nplFile, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &core::nplFile::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *core::nplFile::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *core::nplFile::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_core__nplFile))
        return static_cast<void*>(const_cast< nplFile*>(this));
    return nplTrack::qt_metacast(_clname);
}

int core::nplFile::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = nplTrack::qt_metacall(_c, _id, _a);
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

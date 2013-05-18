/****************************************************************************
** Meta object code from reading C++ file 'fileCache.h'
**
** Created:
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../src/lib/files/fileCache.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'fileCache.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_audioFiles__fileCache[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      23,   22,   22,   22, 0x05,
      56,   22,   22,   22, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_audioFiles__fileCache[] = {
    "audioFiles::fileCache\0\0"
    "changed(audioFiles::tagChangesL)\0"
    "doesExist(bool)\0"
};

void audioFiles::fileCache::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        fileCache *_t = static_cast<fileCache *>(_o);
        switch (_id) {
        case 0: _t->changed((*reinterpret_cast< audioFiles::tagChangesL(*)>(_a[1]))); break;
        case 1: _t->doesExist((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData audioFiles::fileCache::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject audioFiles::fileCache::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_audioFiles__fileCache,
      qt_meta_data_audioFiles__fileCache, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &audioFiles::fileCache::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *audioFiles::fileCache::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *audioFiles::fileCache::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_audioFiles__fileCache))
        return static_cast<void*>(const_cast< fileCache*>(this));
    return QObject::qt_metacast(_clname);
}

int audioFiles::fileCache::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void audioFiles::fileCache::changed(audioFiles::tagChangesL _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void audioFiles::fileCache::doesExist(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE

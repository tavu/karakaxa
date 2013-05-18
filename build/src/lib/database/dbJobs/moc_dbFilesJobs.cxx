/****************************************************************************
** Meta object code from reading C++ file 'dbFilesJobs.h'
**
** Created:
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../src/lib/database/dbJobs/dbFilesJobs.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'dbFilesJobs.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_database__removeFiles[] = {

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
      25,   23,   22,   22, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_database__removeFiles[] = {
    "database::removeFiles\0\0j\0jobDone(KJob*)\0"
};

void database::removeFiles::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        removeFiles *_t = static_cast<removeFiles *>(_o);
        switch (_id) {
        case 0: _t->jobDone((*reinterpret_cast< KJob*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData database::removeFiles::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject database::removeFiles::staticMetaObject = {
    { &dbThrJob::staticMetaObject, qt_meta_stringdata_database__removeFiles,
      qt_meta_data_database__removeFiles, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &database::removeFiles::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *database::removeFiles::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *database::removeFiles::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_database__removeFiles))
        return static_cast<void*>(const_cast< removeFiles*>(this));
    return dbThrJob::qt_metacast(_clname);
}

int database::removeFiles::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = dbThrJob::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    }
    return _id;
}
static const uint qt_meta_data_database__removePl[] = {

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
      22,   20,   19,   19, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_database__removePl[] = {
    "database::removePl\0\0j\0jobDone(KJob*)\0"
};

void database::removePl::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        removePl *_t = static_cast<removePl *>(_o);
        switch (_id) {
        case 0: _t->jobDone((*reinterpret_cast< KJob*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData database::removePl::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject database::removePl::staticMetaObject = {
    { &dbThrJob::staticMetaObject, qt_meta_stringdata_database__removePl,
      qt_meta_data_database__removePl, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &database::removePl::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *database::removePl::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *database::removePl::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_database__removePl))
        return static_cast<void*>(const_cast< removePl*>(this));
    return dbThrJob::qt_metacast(_clname);
}

int database::removePl::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = dbThrJob::qt_metacall(_c, _id, _a);
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

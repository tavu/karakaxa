/****************************************************************************
** Meta object code from reading C++ file 'albumQueryGrt.h'
**
** Created:
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../src/lib/database/queries/albumQueryGrt.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'albumQueryGrt.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_database__albumQueryGrt[] = {

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
      27,   25,   24,   24, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_database__albumQueryGrt[] = {
    "database::albumQueryGrt\0\0e\0"
    "dbEvents(dbEventP)\0"
};

void database::albumQueryGrt::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        albumQueryGrt *_t = static_cast<albumQueryGrt *>(_o);
        switch (_id) {
        case 0: _t->dbEvents((*reinterpret_cast< dbEventP(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData database::albumQueryGrt::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject database::albumQueryGrt::staticMetaObject = {
    { &queryGrt::staticMetaObject, qt_meta_stringdata_database__albumQueryGrt,
      qt_meta_data_database__albumQueryGrt, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &database::albumQueryGrt::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *database::albumQueryGrt::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *database::albumQueryGrt::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_database__albumQueryGrt))
        return static_cast<void*>(const_cast< albumQueryGrt*>(this));
    return queryGrt::qt_metacast(_clname);
}

int database::albumQueryGrt::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = queryGrt::qt_metacall(_c, _id, _a);
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
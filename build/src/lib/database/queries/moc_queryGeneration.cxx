/****************************************************************************
** Meta object code from reading C++ file 'queryGeneration.h'
**
** Created:
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../src/lib/database/queries/queryGeneration.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'queryGeneration.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_database__queryGrt[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      20,   19,   19,   19, 0x05,

 // slots: signature, parameters, type, tag, flags
      35,   19,   19,   19, 0x09,
      53,   51,   19,   19, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_database__queryGrt[] = {
    "database::queryGrt\0\0updateNeeded()\0"
    "setNeedUpdate()\0e\0dbEvents(database::dbEventP)\0"
};

void database::queryGrt::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        queryGrt *_t = static_cast<queryGrt *>(_o);
        switch (_id) {
        case 0: _t->updateNeeded(); break;
        case 1: _t->setNeedUpdate(); break;
        case 2: _t->dbEvents((*reinterpret_cast< database::dbEventP(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData database::queryGrt::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject database::queryGrt::staticMetaObject = {
    { &dbBase::staticMetaObject, qt_meta_stringdata_database__queryGrt,
      qt_meta_data_database__queryGrt, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &database::queryGrt::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *database::queryGrt::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *database::queryGrt::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_database__queryGrt))
        return static_cast<void*>(const_cast< queryGrt*>(this));
    return dbBase::qt_metacast(_clname);
}

int database::queryGrt::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = dbBase::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void database::queryGrt::updateNeeded()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE

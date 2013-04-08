/****************************************************************************
** Meta object code from reading C++ file 'dbJob.h'
**
** Created:
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../src/lib/database/dbJobs/dbJob.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'dbJob.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_database__dbJob[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      17,   16,   16,   16, 0x05,
      28,   16,   16,   16, 0x05,

 // slots: signature, parameters, type, tag, flags
      38,   16,   16,   16, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_database__dbJob[] = {
    "database::dbJob\0\0finished()\0started()\0"
    "cancel()\0"
};

void database::dbJob::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        dbJob *_t = static_cast<dbJob *>(_o);
        switch (_id) {
        case 0: _t->finished(); break;
        case 1: _t->started(); break;
        case 2: _t->cancel(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData database::dbJob::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject database::dbJob::staticMetaObject = {
    { &dbBase::staticMetaObject, qt_meta_stringdata_database__dbJob,
      qt_meta_data_database__dbJob, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &database::dbJob::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *database::dbJob::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *database::dbJob::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_database__dbJob))
        return static_cast<void*>(const_cast< dbJob*>(this));
    return dbBase::qt_metacast(_clname);
}

int database::dbJob::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void database::dbJob::finished()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void database::dbJob::started()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}
QT_END_MOC_NAMESPACE

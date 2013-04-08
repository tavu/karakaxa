/****************************************************************************
** Meta object code from reading C++ file 'database.h'
**
** Created:
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../src/lib/database/database.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'database.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_database__databaseConection[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: signature, parameters, type, tag, flags
      29,   28,   28,   28, 0x05,
      39,   28,   28,   28, 0x05,
      72,   70,   28,   28, 0x05,
     101,   28,   28,   28, 0x05,
     130,   28,   28,   28, 0x05,

 // slots: signature, parameters, type, tag, flags
     157,  155,   28,   28, 0x0a,
     179,   28,  172,   28, 0x0a,
     188,   28,  172,   28, 0x0a,
     199,  197,   28,   28, 0x0a,
     219,   28,   28,   28, 0x08,
     235,  233,   28,   28, 0x08,
     270,   28,   28,   28, 0x08,
     291,   28,   28,   28, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_database__databaseConection[] = {
    "database::databaseConection\0\0changed()\0"
    "updated(audioFiles::audioFile)\0,\0"
    "stateCanged(dbState,dbState)\0"
    "newEvent(database::dbEventP)\0"
    "newJob(database::dbJobP)\0j\0addJob(dbJobP)\0"
    "dbJobP\0rescan()\0update()\0e\0"
    "emitEvent(dbEventP)\0jobFinished()\0f\0"
    "emitUpdated(audioFiles::audioFile)\0"
    "editMultFilesStart()\0editMultFilesStop()\0"
};

void database::databaseConection::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        databaseConection *_t = static_cast<databaseConection *>(_o);
        switch (_id) {
        case 0: _t->changed(); break;
        case 1: _t->updated((*reinterpret_cast< audioFiles::audioFile(*)>(_a[1]))); break;
        case 2: _t->stateCanged((*reinterpret_cast< dbState(*)>(_a[1])),(*reinterpret_cast< dbState(*)>(_a[2]))); break;
        case 3: _t->newEvent((*reinterpret_cast< database::dbEventP(*)>(_a[1]))); break;
        case 4: _t->newJob((*reinterpret_cast< database::dbJobP(*)>(_a[1]))); break;
        case 5: _t->addJob((*reinterpret_cast< dbJobP(*)>(_a[1]))); break;
        case 6: { dbJobP _r = _t->rescan();
            if (_a[0]) *reinterpret_cast< dbJobP*>(_a[0]) = _r; }  break;
        case 7: { dbJobP _r = _t->update();
            if (_a[0]) *reinterpret_cast< dbJobP*>(_a[0]) = _r; }  break;
        case 8: _t->emitEvent((*reinterpret_cast< dbEventP(*)>(_a[1]))); break;
        case 9: _t->jobFinished(); break;
        case 10: _t->emitUpdated((*reinterpret_cast< audioFiles::audioFile(*)>(_a[1]))); break;
        case 11: _t->editMultFilesStart(); break;
        case 12: _t->editMultFilesStop(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData database::databaseConection::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject database::databaseConection::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_database__databaseConection,
      qt_meta_data_database__databaseConection, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &database::databaseConection::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *database::databaseConection::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *database::databaseConection::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_database__databaseConection))
        return static_cast<void*>(const_cast< databaseConection*>(this));
    return QObject::qt_metacast(_clname);
}

int database::databaseConection::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    }
    return _id;
}

// SIGNAL 0
void database::databaseConection::changed()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void database::databaseConection::updated(audioFiles::audioFile _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void database::databaseConection::stateCanged(dbState _t1, dbState _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void database::databaseConection::newEvent(database::dbEventP _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void database::databaseConection::newJob(database::dbJobP _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}
QT_END_MOC_NAMESPACE

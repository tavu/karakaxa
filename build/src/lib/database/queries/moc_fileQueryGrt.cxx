/****************************************************************************
** Meta object code from reading C++ file 'fileQueryGrt.h'
**
** Created:
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../src/lib/database/queries/fileQueryGrt.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'fileQueryGrt.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_database__filesQueryGrt[] = {

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
      25,   24,   24,   24, 0x05,
      43,   24,   24,   24, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_database__filesQueryGrt[] = {
    "database::filesQueryGrt\0\0selectionCalled()\0"
    "selectionMade()\0"
};

void database::filesQueryGrt::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        filesQueryGrt *_t = static_cast<filesQueryGrt *>(_o);
        switch (_id) {
        case 0: _t->selectionCalled(); break;
        case 1: _t->selectionMade(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData database::filesQueryGrt::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject database::filesQueryGrt::staticMetaObject = {
    { &queryGrt::staticMetaObject, qt_meta_stringdata_database__filesQueryGrt,
      qt_meta_data_database__filesQueryGrt, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &database::filesQueryGrt::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *database::filesQueryGrt::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *database::filesQueryGrt::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_database__filesQueryGrt))
        return static_cast<void*>(const_cast< filesQueryGrt*>(this));
    return queryGrt::qt_metacast(_clname);
}

int database::filesQueryGrt::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = queryGrt::qt_metacall(_c, _id, _a);
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
void database::filesQueryGrt::selectionCalled()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void database::filesQueryGrt::selectionMade()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}
QT_END_MOC_NAMESPACE

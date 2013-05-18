/****************************************************************************
** Meta object code from reading C++ file 'editMultFiles.h'
**
** Created:
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../src/lib/database/editMultFiles.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'editMultFiles.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_database__editMultFiles[] = {

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
      25,   24,   24,   24, 0x05,
      36,   24,   24,   24, 0x05,

 // slots: signature, parameters, type, tag, flags
      46,   24,   24,   24, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_database__editMultFiles[] = {
    "database::editMultFiles\0\0finished()\0"
    "started()\0finishedSlot()\0"
};

void database::editMultFiles::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        editMultFiles *_t = static_cast<editMultFiles *>(_o);
        switch (_id) {
        case 0: _t->finished(); break;
        case 1: _t->started(); break;
        case 2: _t->finishedSlot(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData database::editMultFiles::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject database::editMultFiles::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_database__editMultFiles,
      qt_meta_data_database__editMultFiles, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &database::editMultFiles::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *database::editMultFiles::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *database::editMultFiles::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_database__editMultFiles))
        return static_cast<void*>(const_cast< editMultFiles*>(this));
    return QObject::qt_metacast(_clname);
}

int database::editMultFiles::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
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
void database::editMultFiles::finished()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void database::editMultFiles::started()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}
QT_END_MOC_NAMESPACE

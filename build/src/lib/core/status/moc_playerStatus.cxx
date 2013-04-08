/****************************************************************************
** Meta object code from reading C++ file 'playerStatus.h'
**
** Created:
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../src/lib/core/status/playerStatus.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'playerStatus.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_core__playetStatus[] = {

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
      22,   20,   19,   19, 0x05,
      44,   20,   19,   19, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_core__playetStatus[] = {
    "core::playetStatus\0\0s\0errorMessage(QString)\0"
    "infoMessage(QString)\0"
};

void core::playetStatus::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        playetStatus *_t = static_cast<playetStatus *>(_o);
        switch (_id) {
        case 0: _t->errorMessage((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->infoMessage((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData core::playetStatus::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject core::playetStatus::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_core__playetStatus,
      qt_meta_data_core__playetStatus, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &core::playetStatus::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *core::playetStatus::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *core::playetStatus::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_core__playetStatus))
        return static_cast<void*>(const_cast< playetStatus*>(this));
    return QObject::qt_metacast(_clname);
}

int core::playetStatus::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void core::playetStatus::errorMessage(const QString & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void core::playetStatus::infoMessage(const QString & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE

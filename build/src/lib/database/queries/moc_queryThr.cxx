/****************************************************************************
** Meta object code from reading C++ file 'queryThr.h'
**
** Created:
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../src/lib/database/queries/queryThr.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'queryThr.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_database__queryThr[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      20,   19,   19,   19, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_database__queryThr[] = {
    "database::queryThr\0\0"
    "items(QVector<audioFiles::audioFile>)\0"
};

void database::queryThr::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        queryThr *_t = static_cast<queryThr *>(_o);
        switch (_id) {
        case 0: _t->items((*reinterpret_cast< QVector<audioFiles::audioFile>(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData database::queryThr::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject database::queryThr::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_database__queryThr,
      qt_meta_data_database__queryThr, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &database::queryThr::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *database::queryThr::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *database::queryThr::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_database__queryThr))
        return static_cast<void*>(const_cast< queryThr*>(this));
    return QThread::qt_metacast(_clname);
}

int database::queryThr::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    }
    return _id;
}

// SIGNAL 0
void database::queryThr::items(QVector<audioFiles::audioFile> _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE

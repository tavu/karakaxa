/****************************************************************************
** Meta object code from reading C++ file 'tagItem.h'
**
** Created:
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../../src/lib/views/models/libraryModel/tagItem.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'tagItem.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_views__tagItem[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      16,   15,   15,   15, 0x05,

 // slots: signature, parameters, type, tag, flags
      34,   32,   15,   15, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_views__tagItem[] = {
    "views::tagItem\0\0needUpdate(int)\0e\0"
    "dbEvents(database::dbEventP)\0"
};

void views::tagItem::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        tagItem *_t = static_cast<tagItem *>(_o);
        switch (_id) {
        case 0: _t->needUpdate((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->dbEvents((*reinterpret_cast< database::dbEventP(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData views::tagItem::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject views::tagItem::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_views__tagItem,
      qt_meta_data_views__tagItem, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &views::tagItem::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *views::tagItem::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *views::tagItem::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_views__tagItem))
        return static_cast<void*>(const_cast< tagItem*>(this));
    return QObject::qt_metacast(_clname);
}

int views::tagItem::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void views::tagItem::needUpdate(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE

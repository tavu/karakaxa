/****************************************************************************
** Meta object code from reading C++ file 'trackModel.h'
**
** Created:
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../src/lib/views/models/trackModel.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'trackModel.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_views__trackItem[] = {

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
      18,   17,   17,   17, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_views__trackItem[] = {
    "views::trackItem\0\0changed(audioFiles::tagChangesL)\0"
};

void views::trackItem::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        trackItem *_t = static_cast<trackItem *>(_o);
        switch (_id) {
        case 0: _t->changed((*reinterpret_cast< audioFiles::tagChangesL(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData views::trackItem::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject views::trackItem::staticMetaObject = {
    { &standardItem::staticMetaObject, qt_meta_stringdata_views__trackItem,
      qt_meta_data_views__trackItem, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &views::trackItem::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *views::trackItem::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *views::trackItem::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_views__trackItem))
        return static_cast<void*>(const_cast< trackItem*>(this));
    return standardItem::qt_metacast(_clname);
}

int views::trackItem::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = standardItem::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    }
    return _id;
}
static const uint qt_meta_data_views__trackModelItem[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      29,   23,   22,   22, 0x0a,
      52,   22,   22,   22, 0x0a,
      68,   63,   22,   22, 0x0a,
     106,   22,   22,   22, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_views__trackModelItem[] = {
    "views::trackModelItem\0\0f,pos\0"
    "addItem(audioFile,int)\0addItems()\0"
    ",pos\0removeItem(audioFiles::audioFile,int)\0"
    "clearSlot()\0"
};

void views::trackModelItem::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        trackModelItem *_t = static_cast<trackModelItem *>(_o);
        switch (_id) {
        case 0: _t->addItem((*reinterpret_cast< audioFile(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: _t->addItems(); break;
        case 2: _t->removeItem((*reinterpret_cast< audioFiles::audioFile(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 3: _t->clearSlot(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData views::trackModelItem::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject views::trackModelItem::staticMetaObject = {
    { &standardItem::staticMetaObject, qt_meta_stringdata_views__trackModelItem,
      qt_meta_data_views__trackModelItem, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &views::trackModelItem::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *views::trackModelItem::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *views::trackModelItem::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_views__trackModelItem))
        return static_cast<void*>(const_cast< trackModelItem*>(this));
    return standardItem::qt_metacast(_clname);
}

int views::trackModelItem::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = standardItem::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE

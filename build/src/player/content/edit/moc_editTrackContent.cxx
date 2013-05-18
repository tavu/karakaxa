/****************************************************************************
** Meta object code from reading C++ file 'editTrackContent.h'
**
** Created:
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../src/player/content/edit/editTrackContent.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'editTrackContent.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_editTrackContent[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      18,   17,   17,   17, 0x0a,
      32,   25,   17,   17, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_editTrackContent[] = {
    "editTrackContent\0\0save()\0button\0"
    "clicked(QAbstractButton*)\0"
};

void editTrackContent::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        editTrackContent *_t = static_cast<editTrackContent *>(_o);
        switch (_id) {
        case 0: _t->save(); break;
        case 1: _t->clicked((*reinterpret_cast< QAbstractButton*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData editTrackContent::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject editTrackContent::staticMetaObject = {
    { &core::abstractContent::staticMetaObject, qt_meta_stringdata_editTrackContent,
      qt_meta_data_editTrackContent, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &editTrackContent::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *editTrackContent::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *editTrackContent::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_editTrackContent))
        return static_cast<void*>(const_cast< editTrackContent*>(this));
    typedef core::abstractContent QMocSuperClass;
    return QMocSuperClass::qt_metacast(_clname);
}

int editTrackContent::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    typedef core::abstractContent QMocSuperClass;
    _id = QMocSuperClass::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}
static const uint qt_meta_data_editTrackMenu[] = {

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
      15,   14,   14,   14, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_editTrackMenu[] = {
    "editTrackMenu\0\0activated()\0"
};

void editTrackMenu::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        editTrackMenu *_t = static_cast<editTrackMenu *>(_o);
        switch (_id) {
        case 0: _t->activated(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData editTrackMenu::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject editTrackMenu::staticMetaObject = {
    { &core::abstractMenu::staticMetaObject, qt_meta_stringdata_editTrackMenu,
      qt_meta_data_editTrackMenu, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &editTrackMenu::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *editTrackMenu::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *editTrackMenu::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_editTrackMenu))
        return static_cast<void*>(const_cast< editTrackMenu*>(this));
    typedef core::abstractMenu QMocSuperClass;
    return QMocSuperClass::qt_metacast(_clname);
}

int editTrackMenu::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    typedef core::abstractMenu QMocSuperClass;
    _id = QMocSuperClass::qt_metacall(_c, _id, _a);
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

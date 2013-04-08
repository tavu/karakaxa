/****************************************************************************
** Meta object code from reading C++ file 'actionMenu.h'
**
** Created:
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../src/lib/views/actionMenu.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'actionMenu.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_views__actionMenu[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      26,   19,   18,   18, 0x08,
      57,   51,   18,   18, 0x08,
      87,   85,   18,   18, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_views__actionMenu[] = {
    "views::actionMenu\0\0repeat\0"
    "repeatPlaylistSlot(bool)\0state\0"
    "stateChanged(Phonon::State)\0v\0"
    "volumeC(qreal)\0"
};

void views::actionMenu::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        actionMenu *_t = static_cast<actionMenu *>(_o);
        switch (_id) {
        case 0: _t->repeatPlaylistSlot((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->stateChanged((*reinterpret_cast< Phonon::State(*)>(_a[1]))); break;
        case 2: _t->volumeC((*reinterpret_cast< qreal(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData views::actionMenu::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject views::actionMenu::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_views__actionMenu,
      qt_meta_data_views__actionMenu, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &views::actionMenu::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *views::actionMenu::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *views::actionMenu::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_views__actionMenu))
        return static_cast<void*>(const_cast< actionMenu*>(this));
    return QObject::qt_metacast(_clname);
}

int views::actionMenu::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
QT_END_MOC_NAMESPACE

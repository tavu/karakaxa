/****************************************************************************
** Meta object code from reading C++ file 'playingWidget.h'
**
** Created:
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../src/player/main/playingWidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'playingWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_playingWidget[] = {

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
      15,   14,   14,   14, 0x08,
      30,   28,   14,   14, 0x08,
      45,   14,   14,   14, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_playingWidget[] = {
    "playingWidget\0\0updateInfo()\0n\0"
    "setRating(int)\0getInfo()\0"
};

void playingWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        playingWidget *_t = static_cast<playingWidget *>(_o);
        switch (_id) {
        case 0: _t->updateInfo(); break;
        case 1: _t->setRating((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->getInfo(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData playingWidget::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject playingWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_playingWidget,
      qt_meta_data_playingWidget, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &playingWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *playingWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *playingWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_playingWidget))
        return static_cast<void*>(const_cast< playingWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int playingWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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

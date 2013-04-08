/****************************************************************************
** Meta object code from reading C++ file 'ratingWidget.h'
**
** Created:
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../src/lib/views/ratingWidget/ratingWidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ratingWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_views__ratingWidget[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       1,   19, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      21,   20,   20,   20, 0x05,

 // properties: name, type, flags
      44,   40, 0x02595103,

 // properties: notify_signal_id
       0,

       0        // eod
};

static const char qt_meta_stringdata_views__ratingWidget[] = {
    "views::ratingWidget\0\0ratingChanged(int)\0"
    "int\0rating\0"
};

void views::ratingWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ratingWidget *_t = static_cast<ratingWidget *>(_o);
        switch (_id) {
        case 0: _t->ratingChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData views::ratingWidget::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject views::ratingWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_views__ratingWidget,
      qt_meta_data_views__ratingWidget, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &views::ratingWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *views::ratingWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *views::ratingWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_views__ratingWidget))
        return static_cast<void*>(const_cast< ratingWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int views::ratingWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    }
#ifndef QT_NO_PROPERTIES
      else if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< int*>(_v) = rating(); break;
        }
        _id -= 1;
    } else if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: setRating(*reinterpret_cast< int*>(_v)); break;
        }
        _id -= 1;
    } else if (_c == QMetaObject::ResetProperty) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 1;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void views::ratingWidget::ratingChanged(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE

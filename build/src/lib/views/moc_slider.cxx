/****************************************************************************
** Meta object code from reading C++ file 'slider.h'
**
** Created:
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../src/lib/views/slider.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'slider.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_views__Slider[] = {

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
      15,   14,   14,   14, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_views__Slider[] = {
    "views::Slider\0\0sliderReleased(int)\0"
};

void views::Slider::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        Slider *_t = static_cast<Slider *>(_o);
        switch (_id) {
        case 0: _t->sliderReleased((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData views::Slider::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject views::Slider::staticMetaObject = {
    { &QSlider::staticMetaObject, qt_meta_stringdata_views__Slider,
      qt_meta_data_views__Slider, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &views::Slider::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *views::Slider::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *views::Slider::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_views__Slider))
        return static_cast<void*>(const_cast< Slider*>(this));
    return QSlider::qt_metacast(_clname);
}

int views::Slider::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QSlider::qt_metacall(_c, _id, _a);
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
void views::Slider::sliderReleased(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
static const uint qt_meta_data_views__sliderWidget[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      26,   21,   20,   20, 0x08,
      51,   20,   20,   20, 0x08,
      67,   20,   20,   20, 0x08,
      77,   21,   20,   20, 0x08,
     100,   20,   20,   20, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_views__sliderWidget[] = {
    "views::sliderWidget\0\0time\0"
    "totalTimeChanged(qint64)\0updateTime(int)\0"
    "seek(int)\0setSliderValue(qint64)\0"
    "trackChanged()\0"
};

void views::sliderWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        sliderWidget *_t = static_cast<sliderWidget *>(_o);
        switch (_id) {
        case 0: _t->totalTimeChanged((*reinterpret_cast< qint64(*)>(_a[1]))); break;
        case 1: _t->updateTime((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->seek((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->setSliderValue((*reinterpret_cast< qint64(*)>(_a[1]))); break;
        case 4: _t->trackChanged(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData views::sliderWidget::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject views::sliderWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_views__sliderWidget,
      qt_meta_data_views__sliderWidget, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &views::sliderWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *views::sliderWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *views::sliderWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_views__sliderWidget))
        return static_cast<void*>(const_cast< sliderWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int views::sliderWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    return _id;
}
QT_END_MOC_NAMESPACE

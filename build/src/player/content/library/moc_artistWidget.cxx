/****************************************************************************
** Meta object code from reading C++ file 'artistWidget.h'
**
** Created:
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../src/player/content/library/artistWidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'artistWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_artistWidget[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      16,   14,   13,   13, 0x05,

 // slots: signature, parameters, type, tag, flags
      40,   34,   13,   13, 0x08,
      69,   14,   13,   13, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_artistWidget[] = {
    "artistWidget\0\0s\0toArtist(QString)\0"
    "index\0artistActivated(QModelIndex)\0"
    "setSearch(QString)\0"
};

void artistWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        artistWidget *_t = static_cast<artistWidget *>(_o);
        switch (_id) {
        case 0: _t->toArtist((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->artistActivated((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 2: _t->setSearch((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData artistWidget::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject artistWidget::staticMetaObject = {
    { &QListView::staticMetaObject, qt_meta_stringdata_artistWidget,
      qt_meta_data_artistWidget, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &artistWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *artistWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *artistWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_artistWidget))
        return static_cast<void*>(const_cast< artistWidget*>(this));
    return QListView::qt_metacast(_clname);
}

int artistWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QListView::qt_metacall(_c, _id, _a);
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
void artistWidget::toArtist(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE

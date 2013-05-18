/****************************************************************************
** Meta object code from reading C++ file 'coverDownloaderWidget.h'
**
** Created:
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../src/lib/views/coverWidget/coverDownloaderWidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'coverDownloaderWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_views__coverDownloaderWidget[] = {

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
      30,   29,   29,   29, 0x08,
      54,   29,   29,   29, 0x08,
      63,   29,   29,   29, 0x08,
      71,   29,   29,   29, 0x08,
     101,   29,   29,   29, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_views__coverDownloaderWidget[] = {
    "views::coverDownloaderWidget\0\0"
    "newImage(views::imageP)\0search()\0"
    "clear()\0nameChanged(QAbstractButton*)\0"
    "changeLocation()\0"
};

void views::coverDownloaderWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        coverDownloaderWidget *_t = static_cast<coverDownloaderWidget *>(_o);
        switch (_id) {
        case 0: _t->newImage((*reinterpret_cast< views::imageP(*)>(_a[1]))); break;
        case 1: _t->search(); break;
        case 2: _t->clear(); break;
        case 3: _t->nameChanged((*reinterpret_cast< QAbstractButton*(*)>(_a[1]))); break;
        case 4: _t->changeLocation(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData views::coverDownloaderWidget::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject views::coverDownloaderWidget::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_views__coverDownloaderWidget,
      qt_meta_data_views__coverDownloaderWidget, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &views::coverDownloaderWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *views::coverDownloaderWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *views::coverDownloaderWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_views__coverDownloaderWidget))
        return static_cast<void*>(const_cast< coverDownloaderWidget*>(this));
    return QDialog::qt_metacast(_clname);
}

int views::coverDownloaderWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
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

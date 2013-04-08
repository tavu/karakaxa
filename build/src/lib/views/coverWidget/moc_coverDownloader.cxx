/****************************************************************************
** Meta object code from reading C++ file 'coverDownloader.h'
**
** Created:
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../src/lib/views/coverWidget/coverDownloader.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'coverDownloader.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_views__coverDownloader[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      24,   23,   23,   23, 0x05,

 // slots: signature, parameters, type, tag, flags
      48,   23,   23,   23, 0x0a,
      67,   23,   62,   23, 0x0a,
      82,   23,   23,   23, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_views__coverDownloader[] = {
    "views::coverDownloader\0\0newImage(views::imageP)\0"
    "fetchCovers()\0bool\0canFetchMore()\0"
    "clear()\0"
};

void views::coverDownloader::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        coverDownloader *_t = static_cast<coverDownloader *>(_o);
        switch (_id) {
        case 0: _t->newImage((*reinterpret_cast< views::imageP(*)>(_a[1]))); break;
        case 1: _t->fetchCovers(); break;
        case 2: { bool _r = _t->canFetchMore();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 3: _t->clear(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData views::coverDownloader::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject views::coverDownloader::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_views__coverDownloader,
      qt_meta_data_views__coverDownloader, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &views::coverDownloader::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *views::coverDownloader::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *views::coverDownloader::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_views__coverDownloader))
        return static_cast<void*>(const_cast< coverDownloader*>(this));
    return QObject::qt_metacast(_clname);
}

int views::coverDownloader::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void views::coverDownloader::newImage(views::imageP _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE

/****************************************************************************
** Meta object code from reading C++ file 'lfmCover.h'
**
** Created:
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/lastFm/lfmCover.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'lfmCover.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_lastFm__lfmCover[] = {

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
      18,   17,   17,   17, 0x08,
      51,   17,   17,   17, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_lastFm__lfmCover[] = {
    "lastFm::lfmCover\0\0albums(QList<lastFm::albumInfo>)\0"
    "answer()\0"
};

void lastFm::lfmCover::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        lfmCover *_t = static_cast<lfmCover *>(_o);
        switch (_id) {
        case 0: _t->albums((*reinterpret_cast< QList<lastFm::albumInfo>(*)>(_a[1]))); break;
        case 1: _t->answer(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData lastFm::lfmCover::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject lastFm::lfmCover::staticMetaObject = {
    { &views::coverDownloader::staticMetaObject, qt_meta_stringdata_lastFm__lfmCover,
      qt_meta_data_lastFm__lfmCover, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &lastFm::lfmCover::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *lastFm::lfmCover::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *lastFm::lfmCover::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_lastFm__lfmCover))
        return static_cast<void*>(const_cast< lfmCover*>(this));
    typedef views::coverDownloader QMocSuperClass;
    return QMocSuperClass::qt_metacast(_clname);
}

int lastFm::lfmCover::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    typedef views::coverDownloader QMocSuperClass;
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
QT_END_MOC_NAMESPACE

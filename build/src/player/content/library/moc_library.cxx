/****************************************************************************
** Meta object code from reading C++ file 'library.h'
**
** Created:
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../src/player/content/library/library.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'library.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_library[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      15,    9,    8,    8, 0x0a,
      44,    8,    8,    8, 0x0a,
      57,    8,    8,    8, 0x0a,
      69,    8,    8,    8, 0x0a,
      81,    8,    8,    8, 0x0a,
     105,  100,    8,    8, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_library[] = {
    "library\0\0index\0artistActivated(QModelIndex)\0"
    "goToArtist()\0goToAlbum()\0dbChanged()\0"
    "checkNeedUpdates()\0text\0search(QString)\0"
};

void library::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        library *_t = static_cast<library *>(_o);
        switch (_id) {
        case 0: _t->artistActivated((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 1: _t->goToArtist(); break;
        case 2: _t->goToAlbum(); break;
        case 3: _t->dbChanged(); break;
        case 4: _t->checkNeedUpdates(); break;
        case 5: _t->search((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData library::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject library::staticMetaObject = {
    { &core::abstractContent::staticMetaObject, qt_meta_stringdata_library,
      qt_meta_data_library, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &library::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *library::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *library::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_library))
        return static_cast<void*>(const_cast< library*>(this));
    typedef core::abstractContent QMocSuperClass;
    return QMocSuperClass::qt_metacast(_clname);
}

int library::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    typedef core::abstractContent QMocSuperClass;
    _id = QMocSuperClass::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    return _id;
}
QT_END_MOC_NAMESPACE

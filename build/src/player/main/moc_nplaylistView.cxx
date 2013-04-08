/****************************************************************************
** Meta object code from reading C++ file 'nplaylistView.h'
**
** Created:
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../src/player/main/nplaylistView.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'nplaylistView.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_nplaylistView[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      15,   14,   14,   14, 0x0a,
      40,   34,   14,   14, 0x0a,
      58,   14,   14,   14, 0x08,
      67,   14,   14,   14, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_nplaylistView[] = {
    "nplaylistView\0\0goToCurrentTrack()\0"
    "index\0play(QModelIndex)\0remove()\0"
    "duplicate()\0"
};

void nplaylistView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        nplaylistView *_t = static_cast<nplaylistView *>(_o);
        switch (_id) {
        case 0: _t->goToCurrentTrack(); break;
        case 1: _t->play((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 2: _t->remove(); break;
        case 3: _t->duplicate(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData nplaylistView::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject nplaylistView::staticMetaObject = {
    { &views::treeView::staticMetaObject, qt_meta_stringdata_nplaylistView,
      qt_meta_data_nplaylistView, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &nplaylistView::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *nplaylistView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *nplaylistView::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_nplaylistView))
        return static_cast<void*>(const_cast< nplaylistView*>(this));
    typedef views::treeView QMocSuperClass;
    return QMocSuperClass::qt_metacast(_clname);
}

int nplaylistView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    typedef views::treeView QMocSuperClass;
    _id = QMocSuperClass::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE

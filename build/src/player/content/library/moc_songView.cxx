/****************************************************************************
** Meta object code from reading C++ file 'songView.h'
**
** Created:
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../src/player/content/library/songView.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'songView.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_songView[] = {

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
      10,    9,    9,    9, 0x08,
      21,    9,    9,    9, 0x08,
      40,   34,    9,    9, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_songView[] = {
    "songView\0\0fileEdit()\0openEditor()\0"
    "index\0play(QModelIndex)\0"
};

void songView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        songView *_t = static_cast<songView *>(_o);
        switch (_id) {
        case 0: _t->fileEdit(); break;
        case 1: _t->openEditor(); break;
        case 2: _t->play((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData songView::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject songView::staticMetaObject = {
    { &views::treeView::staticMetaObject, qt_meta_stringdata_songView,
      qt_meta_data_songView, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &songView::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *songView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *songView::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_songView))
        return static_cast<void*>(const_cast< songView*>(this));
    typedef views::treeView QMocSuperClass;
    return QMocSuperClass::qt_metacast(_clname);
}

int songView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    typedef views::treeView QMocSuperClass;
    _id = QMocSuperClass::qt_metacall(_c, _id, _a);
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

/****************************************************************************
** Meta object code from reading C++ file 'treeViewHeader.h'
**
** Created:
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../src/lib/views/models/treeViewHeader.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'treeViewHeader.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_views__treeViewHeader[] = {

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
      23,   22,   22,   22, 0x09,
      43,   22,   22,   22, 0x09,
      59,   22,   22,   22, 0x09,
     107,   81,   22,   22, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_views__treeViewHeader[] = {
    "views::treeViewHeader\0\0hideClickedColumn()\0"
    "selectColumnW()\0toggleHideColumn(int)\0"
    "painter,rect,logicalIndex\0"
    "paintSection(QPainter*,QRect,int)\0"
};

void views::treeViewHeader::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        treeViewHeader *_t = static_cast<treeViewHeader *>(_o);
        switch (_id) {
        case 0: _t->hideClickedColumn(); break;
        case 1: _t->selectColumnW(); break;
        case 2: _t->toggleHideColumn((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->paintSection((*reinterpret_cast< QPainter*(*)>(_a[1])),(*reinterpret_cast< const QRect(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData views::treeViewHeader::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject views::treeViewHeader::staticMetaObject = {
    { &QHeaderView::staticMetaObject, qt_meta_stringdata_views__treeViewHeader,
      qt_meta_data_views__treeViewHeader, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &views::treeViewHeader::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *views::treeViewHeader::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *views::treeViewHeader::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_views__treeViewHeader))
        return static_cast<void*>(const_cast< treeViewHeader*>(this));
    return QHeaderView::qt_metacast(_clname);
}

int views::treeViewHeader::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QHeaderView::qt_metacall(_c, _id, _a);
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

/****************************************************************************
** Meta object code from reading C++ file 'treeView.h'
**
** Created:
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../src/lib/views/models/treeView.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'treeView.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_views__treeView[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      19,   17,   16,   16, 0x05,

 // slots: signature, parameters, type, tag, flags
      71,   64,   16,   16, 0x09,
     109,   92,   16,   16, 0x09,
     143,   16,   16,   16, 0x0a,
     151,   16,   16,   16, 0x0a,
     167,   16,   16,   16, 0x0a,
     202,  182,   16,   16, 0x0a,
     251,  239,   16,   16, 0x0a,
     314,  308,   16,   16, 0x0a,
     332,   92,   16,   16, 0x0a,
     370,   16,   16,   16, 0x0a,
     389,   92,   16,   16, 0x0a,
     424,   16,   16,   16, 0x0a,
     449,   16,   16,   16, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_views__treeView[] = {
    "views::treeView\0\0,\0"
    "showContextMenu(QModelIndex,QModelIndexList)\0"
    "editor\0commitData(QWidget*)\0"
    "parent,start,end\0rowsInserted(QModelIndex,int,int)\0"
    "reset()\0writeSettings()\0readSettings()\0"
    "topLeft,bottomRight\0"
    "dataChanged(QModelIndex,QModelIndex)\0"
    "editor,hint\0"
    "closeEditor(QWidget*,QAbstractItemDelegate::EndEditHint)\0"
    "index\0play(QModelIndex)\0"
    "updateStarWidget(QModelIndex,int,int)\0"
    "updateStarWidget()\0"
    "needExpanding(QModelIndex,int,int)\0"
    "itemClicked(QModelIndex)\0editCurrent()\0"
};

void views::treeView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        treeView *_t = static_cast<treeView *>(_o);
        switch (_id) {
        case 0: _t->showContextMenu((*reinterpret_cast< QModelIndex(*)>(_a[1])),(*reinterpret_cast< QModelIndexList(*)>(_a[2]))); break;
        case 1: _t->commitData((*reinterpret_cast< QWidget*(*)>(_a[1]))); break;
        case 2: _t->rowsInserted((*reinterpret_cast< const QModelIndex(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 3: _t->reset(); break;
        case 4: _t->writeSettings(); break;
        case 5: _t->readSettings(); break;
        case 6: _t->dataChanged((*reinterpret_cast< const QModelIndex(*)>(_a[1])),(*reinterpret_cast< const QModelIndex(*)>(_a[2]))); break;
        case 7: _t->closeEditor((*reinterpret_cast< QWidget*(*)>(_a[1])),(*reinterpret_cast< QAbstractItemDelegate::EndEditHint(*)>(_a[2]))); break;
        case 8: _t->play((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 9: _t->updateStarWidget((*reinterpret_cast< QModelIndex(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 10: _t->updateStarWidget(); break;
        case 11: _t->needExpanding((*reinterpret_cast< QModelIndex(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 12: _t->itemClicked((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 13: _t->editCurrent(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData views::treeView::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject views::treeView::staticMetaObject = {
    { &QTreeView::staticMetaObject, qt_meta_stringdata_views__treeView,
      qt_meta_data_views__treeView, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &views::treeView::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *views::treeView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *views::treeView::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_views__treeView))
        return static_cast<void*>(const_cast< treeView*>(this));
    return QTreeView::qt_metacast(_clname);
}

int views::treeView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTreeView::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    }
    return _id;
}

// SIGNAL 0
void views::treeView::showContextMenu(QModelIndex _t1, QModelIndexList _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE

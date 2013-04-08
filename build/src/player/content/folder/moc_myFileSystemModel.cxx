/****************************************************************************
** Meta object code from reading C++ file 'myFileSystemModel.h'
**
** Created:
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../src/player/content/folder/myFileSystemModel.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'myFileSystemModel.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_myFileSystemModel[] = {

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
      19,   18,   18,   18, 0x05,

 // slots: signature, parameters, type, tag, flags
      35,   29,   18,   18, 0x08,
      57,   18,   18,   18, 0x08,
      69,   18,   18,   18, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_myFileSystemModel[] = {
    "myFileSystemModel\0\0updated()\0items\0"
    "insert(KFileItemList)\0callReset()\0"
    "updateLibrary()\0"
};

void myFileSystemModel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        myFileSystemModel *_t = static_cast<myFileSystemModel *>(_o);
        switch (_id) {
        case 0: _t->updated(); break;
        case 1: _t->insert((*reinterpret_cast< const KFileItemList(*)>(_a[1]))); break;
        case 2: _t->callReset(); break;
        case 3: _t->updateLibrary(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData myFileSystemModel::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject myFileSystemModel::staticMetaObject = {
    { &KDirModel::staticMetaObject, qt_meta_stringdata_myFileSystemModel,
      qt_meta_data_myFileSystemModel, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &myFileSystemModel::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *myFileSystemModel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *myFileSystemModel::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_myFileSystemModel))
        return static_cast<void*>(const_cast< myFileSystemModel*>(this));
    return KDirModel::qt_metacast(_clname);
}

int myFileSystemModel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = KDirModel::qt_metacall(_c, _id, _a);
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
void myFileSystemModel::updated()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE

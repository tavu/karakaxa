/****************************************************************************
** Meta object code from reading C++ file 'folder.h'
**
** Created:
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../src/player/content/folder/folder.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'folder.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_folderContent[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      15,   14,   14,   14, 0x0a,
      24,   14,   14,   14, 0x0a,
      29,   14,   14,   14, 0x0a,
      36,   14,   14,   14, 0x0a,
      46,   14,   14,   14, 0x0a,
      60,   54,   14,   14, 0x0a,
      80,   14,   14,   14, 0x08,
      90,   14,   14,   14, 0x08,
     106,   14,   14,   14, 0x08,
     131,  120,   14,   14, 0x08,
     167,  120,   14,   14, 0x08,
     204,   14,   14,   14, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_folderContent[] = {
    "folderContent\0\0cd(KUrl)\0up()\0back()\0"
    "forward()\0newPl()\0index\0setDir(QModelIndex)\0"
    "cleanup()\0writeSettings()\0showUrl(KUrl)\0"
    "index,list\0plMenu(QModelIndex,QModelIndexList)\0"
    "folMenu(QModelIndex,QModelIndexList)\0"
    "edit()\0"
};

void folderContent::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        folderContent *_t = static_cast<folderContent *>(_o);
        switch (_id) {
        case 0: _t->cd((*reinterpret_cast< KUrl(*)>(_a[1]))); break;
        case 1: _t->up(); break;
        case 2: _t->back(); break;
        case 3: _t->forward(); break;
        case 4: _t->newPl(); break;
        case 5: _t->setDir((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 6: _t->cleanup(); break;
        case 7: _t->writeSettings(); break;
        case 8: _t->showUrl((*reinterpret_cast< KUrl(*)>(_a[1]))); break;
        case 9: _t->plMenu((*reinterpret_cast< QModelIndex(*)>(_a[1])),(*reinterpret_cast< QModelIndexList(*)>(_a[2]))); break;
        case 10: _t->folMenu((*reinterpret_cast< QModelIndex(*)>(_a[1])),(*reinterpret_cast< QModelIndexList(*)>(_a[2]))); break;
        case 11: _t->edit(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData folderContent::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject folderContent::staticMetaObject = {
    { &core::abstractContent::staticMetaObject, qt_meta_stringdata_folderContent,
      qt_meta_data_folderContent, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &folderContent::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *folderContent::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *folderContent::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_folderContent))
        return static_cast<void*>(const_cast< folderContent*>(this));
    typedef core::abstractContent QMocSuperClass;
    return QMocSuperClass::qt_metacast(_clname);
}

int folderContent::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    typedef core::abstractContent QMocSuperClass;
    _id = QMocSuperClass::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    }
    return _id;
}
static const uint qt_meta_data_folderContextMenu[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      19,   18,   18,   18, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_folderContextMenu[] = {
    "folderContextMenu\0\0cd()\0"
};

void folderContextMenu::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        folderContextMenu *_t = static_cast<folderContextMenu *>(_o);
        switch (_id) {
        case 0: _t->cd(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData folderContextMenu::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject folderContextMenu::staticMetaObject = {
    { &core::abstractMenu::staticMetaObject, qt_meta_stringdata_folderContextMenu,
      qt_meta_data_folderContextMenu, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &folderContextMenu::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *folderContextMenu::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *folderContextMenu::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_folderContextMenu))
        return static_cast<void*>(const_cast< folderContextMenu*>(this));
    typedef core::abstractMenu QMocSuperClass;
    return QMocSuperClass::qt_metacast(_clname);
}

int folderContextMenu::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    typedef core::abstractMenu QMocSuperClass;
    _id = QMocSuperClass::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    }
    return _id;
}
QT_END_MOC_NAMESPACE

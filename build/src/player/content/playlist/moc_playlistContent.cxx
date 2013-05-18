/****************************************************************************
** Meta object code from reading C++ file 'playlistContent.h'
**
** Created:
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../src/player/content/playlist/playlistContent.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'playlistContent.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_playlistContent[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      17,   16,   16,   16, 0x0a,
      24,   16,   16,   16, 0x0a,
      34,   16,   16,   16, 0x0a,
      46,   43,   16,   16, 0x0a,
      74,   16,   16,   16, 0x0a,
      90,   16,   16,   16, 0x0a,
     106,   16,   16,   16, 0x0a,
     120,   16,   16,   16, 0x0a,
     133,   16,   16,   16, 0x0a,
     152,   16,   16,   16, 0x0a,
     174,  168,   16,   16, 0x0a,
     214,  203,   16,   16, 0x0a,
     283,  278,  264,   16, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_playlistContent[] = {
    "playlistContent\0\0back()\0forward()\0"
    "search()\0in\0activationSlot(QModelIndex)\0"
    "addFolderSlot()\0createSmpSlot()\0"
    "editSmpSlot()\0removeSlot()\0"
    "renameFolderSlot()\0writeSettings()\0"
    "index\0contextMenuSlot(QModelIndex)\0"
    "index,list\0contextMenuForTracks(QModelIndex,QModelIndexList)\0"
    "standardItem*\0item\0head(standardItem*)\0"
};

void playlistContent::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        playlistContent *_t = static_cast<playlistContent *>(_o);
        switch (_id) {
        case 0: _t->back(); break;
        case 1: _t->forward(); break;
        case 2: _t->search(); break;
        case 3: _t->activationSlot((*reinterpret_cast< QModelIndex(*)>(_a[1]))); break;
        case 4: _t->addFolderSlot(); break;
        case 5: _t->createSmpSlot(); break;
        case 6: _t->editSmpSlot(); break;
        case 7: _t->removeSlot(); break;
        case 8: _t->renameFolderSlot(); break;
        case 9: _t->writeSettings(); break;
        case 10: _t->contextMenuSlot((*reinterpret_cast< QModelIndex(*)>(_a[1]))); break;
        case 11: _t->contextMenuForTracks((*reinterpret_cast< QModelIndex(*)>(_a[1])),(*reinterpret_cast< QModelIndexList(*)>(_a[2]))); break;
        case 12: { standardItem* _r = _t->head((*reinterpret_cast< standardItem*(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< standardItem**>(_a[0]) = _r; }  break;
        default: ;
        }
    }
}

const QMetaObjectExtraData playlistContent::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject playlistContent::staticMetaObject = {
    { &core::abstractContent::staticMetaObject, qt_meta_stringdata_playlistContent,
      qt_meta_data_playlistContent, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &playlistContent::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *playlistContent::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *playlistContent::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_playlistContent))
        return static_cast<void*>(const_cast< playlistContent*>(this));
    typedef core::abstractContent QMocSuperClass;
    return QMocSuperClass::qt_metacast(_clname);
}

int playlistContent::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    typedef core::abstractContent QMocSuperClass;
    _id = QMocSuperClass::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    }
    return _id;
}
QT_END_MOC_NAMESPACE

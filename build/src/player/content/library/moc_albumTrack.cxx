/****************************************************************************
** Meta object code from reading C++ file 'albumTrack.h'
**
** Created:
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../src/player/content/library/albumTrack.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'albumTrack.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_albumTrack[] = {

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
      12,   11,   11,   11, 0x0a,
      30,   28,   11,   11, 0x0a,
      66,   11,   11,   11, 0x0a,
      96,   85,   11,   11, 0x0a,
     146,  144,   11,   11, 0x0a,
     174,   11,   11,   11, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_albumTrack[] = {
    "albumTrack\0\0writeSettings()\0q\0"
    "setSearch(database::abstractQuery*)\0"
    "checkNeedUpdates()\0index,list\0"
    "showContexMenuSlot(QModelIndex,QModelIndexList)\0"
    "n\0albumActivated(QModelIndex)\0trackEdit()\0"
};

void albumTrack::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        albumTrack *_t = static_cast<albumTrack *>(_o);
        switch (_id) {
        case 0: _t->writeSettings(); break;
        case 1: _t->setSearch((*reinterpret_cast< database::abstractQuery*(*)>(_a[1]))); break;
        case 2: _t->checkNeedUpdates(); break;
        case 3: _t->showContexMenuSlot((*reinterpret_cast< QModelIndex(*)>(_a[1])),(*reinterpret_cast< QModelIndexList(*)>(_a[2]))); break;
        case 4: _t->albumActivated((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 5: _t->trackEdit(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData albumTrack::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject albumTrack::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_albumTrack,
      qt_meta_data_albumTrack, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &albumTrack::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *albumTrack::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *albumTrack::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_albumTrack))
        return static_cast<void*>(const_cast< albumTrack*>(this));
    return QWidget::qt_metacast(_clname);
}

int albumTrack::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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

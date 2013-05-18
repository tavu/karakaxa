/****************************************************************************
** Meta object code from reading C++ file 'playlist.h'
**
** Created:
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../src/lib/core/playlist/playlist.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'playlist.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_core__playlist[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      18,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      10,       // signalCount

 // signals: signature, parameters, type, tag, flags
      18,   16,   15,   15, 0x05,
      47,   16,   15,   15, 0x05,
      71,   16,   15,   15, 0x05,
     100,   16,   15,   15, 0x05,
     126,  123,   15,   15, 0x05,
     156,  123,   15,   15, 0x05,
     181,   15,   15,   15, 0x05,
     196,   15,   15,   15, 0x05,
     206,   15,   15,   15, 0x05,
     223,   15,   15,   15, 0x05,

 // slots: signature, parameters, type, tag, flags
     240,  234,   15,   15, 0x0a,
     269,  263,   15,   15, 0x0a,
     293,  289,   15,   15, 0x0a,
     313,  305,   15,   15, 0x0a,
     338,  329,   15,   15, 0x0a,
     365,  352,   15,   15, 0x0a,
     383,   15,   15,   15, 0x0a,
     391,   15,   15,   15, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_core__playlist[] = {
    "core::playlist\0\0,\0aboutToInsertTracks(int,int)\0"
    "tracksInserted(int,int)\0"
    "aboutToRemoveTracks(int,int)\0"
    "tracksRemoved(int,int)\0,,\0"
    "aboutToMoveTrack(int,int,int)\0"
    "tracksMoved(int,int,int)\0aboutToClear()\0"
    "cleared()\0aboutToShuffle()\0shuffled()\0"
    "pos,p\0insert(int,nplPointer)\0pos,l\0"
    "insert(int,nplList)\0pos\0remove(int)\0"
    "pos,num\0remove(int,int)\0pos,dest\0"
    "move(int,int)\0pos,num,dest\0move(int,int,int)\0"
    "clear()\0shuffle()\0"
};

void core::playlist::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        playlist *_t = static_cast<playlist *>(_o);
        switch (_id) {
        case 0: _t->aboutToInsertTracks((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: _t->tracksInserted((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 2: _t->aboutToRemoveTracks((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 3: _t->tracksRemoved((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 4: _t->aboutToMoveTrack((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 5: _t->tracksMoved((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 6: _t->aboutToClear(); break;
        case 7: _t->cleared(); break;
        case 8: _t->aboutToShuffle(); break;
        case 9: _t->shuffled(); break;
        case 10: _t->insert((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< nplPointer(*)>(_a[2]))); break;
        case 11: _t->insert((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< nplList(*)>(_a[2]))); break;
        case 12: _t->remove((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 13: _t->remove((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 14: _t->move((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 15: _t->move((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 16: _t->clear(); break;
        case 17: _t->shuffle(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData core::playlist::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject core::playlist::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_core__playlist,
      qt_meta_data_core__playlist, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &core::playlist::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *core::playlist::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *core::playlist::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_core__playlist))
        return static_cast<void*>(const_cast< playlist*>(this));
    return QObject::qt_metacast(_clname);
}

int core::playlist::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 18)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 18;
    }
    return _id;
}

// SIGNAL 0
void core::playlist::aboutToInsertTracks(int _t1, int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void core::playlist::tracksInserted(int _t1, int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void core::playlist::aboutToRemoveTracks(int _t1, int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void core::playlist::tracksRemoved(int _t1, int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void core::playlist::aboutToMoveTrack(int _t1, int _t2, int _t3)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void core::playlist::tracksMoved(int _t1, int _t2, int _t3)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void core::playlist::aboutToClear()
{
    QMetaObject::activate(this, &staticMetaObject, 6, 0);
}

// SIGNAL 7
void core::playlist::cleared()
{
    QMetaObject::activate(this, &staticMetaObject, 7, 0);
}

// SIGNAL 8
void core::playlist::aboutToShuffle()
{
    QMetaObject::activate(this, &staticMetaObject, 8, 0);
}

// SIGNAL 9
void core::playlist::shuffled()
{
    QMetaObject::activate(this, &staticMetaObject, 9, 0);
}
QT_END_MOC_NAMESPACE

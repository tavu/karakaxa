/****************************************************************************
** Meta object code from reading C++ file 'engine.h'
**
** Created:
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../src/lib/core/engine/engine.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'engine.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_core__soundEngine[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: signature, parameters, type, tag, flags
      25,   19,   18,   18, 0x05,
      53,   18,   18,   18, 0x05,
      75,   18,   18,   18, 0x05,

 // slots: signature, parameters, type, tag, flags
     100,   18,   18,   18, 0x08,
     112,  110,   18,   18, 0x08,
     159,   18,   18,   18, 0x08,
     195,  190,   18,   18, 0x08,
     222,   18,  217,   18, 0x0a,
     229,   18,  217,   18, 0x0a,
     242,  240,  217,   18, 0x0a,
     252,   18,  217,   18, 0x0a,
     259,   18,   18,   18, 0x0a,
     273,   18,   18,   18, 0x0a,
     286,   18,   18,   18, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_core__soundEngine[] = {
    "core::soundEngine\0\0state\0"
    "stateChanged(Phonon::State)\0"
    "trackChanged(QString)\0totalTimeChanged(qint64)\0"
    "getNext()\0,\0mediaStateChanged(Phonon::State,Phonon::State)\0"
    "newSource(Phonon::MediaSource)\0time\0"
    "totalTimeSlot(qint64)\0bool\0next()\0"
    "previous()\0n\0play(int)\0play()\0"
    "setMute(bool)\0muteToggle()\0playPause()\0"
};

void core::soundEngine::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        soundEngine *_t = static_cast<soundEngine *>(_o);
        switch (_id) {
        case 0: _t->stateChanged((*reinterpret_cast< Phonon::State(*)>(_a[1]))); break;
        case 1: _t->trackChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->totalTimeChanged((*reinterpret_cast< qint64(*)>(_a[1]))); break;
        case 3: _t->getNext(); break;
        case 4: _t->mediaStateChanged((*reinterpret_cast< Phonon::State(*)>(_a[1])),(*reinterpret_cast< Phonon::State(*)>(_a[2]))); break;
        case 5: _t->newSource((*reinterpret_cast< const Phonon::MediaSource(*)>(_a[1]))); break;
        case 6: _t->totalTimeSlot((*reinterpret_cast< qint64(*)>(_a[1]))); break;
        case 7: { bool _r = _t->next();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 8: { bool _r = _t->previous();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 9: { bool _r = _t->play((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 10: { bool _r = _t->play();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 11: _t->setMute((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 12: _t->muteToggle(); break;
        case 13: _t->playPause(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData core::soundEngine::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject core::soundEngine::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_core__soundEngine,
      qt_meta_data_core__soundEngine, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &core::soundEngine::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *core::soundEngine::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *core::soundEngine::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_core__soundEngine))
        return static_cast<void*>(const_cast< soundEngine*>(this));
    return QObject::qt_metacast(_clname);
}

int core::soundEngine::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
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
void core::soundEngine::stateChanged(Phonon::State _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void core::soundEngine::trackChanged(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void core::soundEngine::totalTimeChanged(qint64 _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_END_MOC_NAMESPACE

/****************************************************************************
** Meta object code from reading C++ file 'audioFile.h'
**
** Created:
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../src/lib/files/audioFile.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'audioFile.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_audioFiles__audioFile[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      23,   22,   22,   22, 0x05,
      56,   22,   22,   22, 0x05,

 // slots: signature, parameters, type, tag, flags
      70,   68,   22,   22, 0x09,
     107,   22,   22,   22, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_audioFiles__audioFile[] = {
    "audioFiles::audioFile\0\0"
    "changed(audioFiles::tagChangesL)\0"
    "invalided()\0l\0emitChanged(audioFiles::tagChangesL)\0"
    "invalidSlot()\0"
};

void audioFiles::audioFile::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        audioFile *_t = static_cast<audioFile *>(_o);
        switch (_id) {
        case 0: _t->changed((*reinterpret_cast< audioFiles::tagChangesL(*)>(_a[1]))); break;
        case 1: _t->invalided(); break;
        case 2: _t->emitChanged((*reinterpret_cast< audioFiles::tagChangesL(*)>(_a[1]))); break;
        case 3: _t->invalidSlot(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData audioFiles::audioFile::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject audioFiles::audioFile::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_audioFiles__audioFile,
      qt_meta_data_audioFiles__audioFile, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &audioFiles::audioFile::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *audioFiles::audioFile::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *audioFiles::audioFile::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_audioFiles__audioFile))
        return static_cast<void*>(const_cast< audioFile*>(this));
    return QObject::qt_metacast(_clname);
}

int audioFiles::audioFile::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
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
void audioFiles::audioFile::changed(audioFiles::tagChangesL _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void audioFiles::audioFile::invalided()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}
QT_END_MOC_NAMESPACE

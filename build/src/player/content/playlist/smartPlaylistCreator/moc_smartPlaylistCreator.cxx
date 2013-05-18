/****************************************************************************
** Meta object code from reading C++ file 'smartPlaylistCreator.h'
**
** Created:
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../../src/player/content/playlist/smartPlaylistCreator/smartPlaylistCreator.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'smartPlaylistCreator.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_smartPlaylistCreator[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      24,   22,   21,   21, 0x05,

 // slots: signature, parameters, type, tag, flags
      48,   21,   21,   21, 0x08,
      59,   21,   21,   21, 0x08,
      68,   21,   21,   21, 0x08,
      82,   77,   21,   21, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_smartPlaylistCreator[] = {
    "smartPlaylistCreator\0\0,\0closed(QString,QString)\0"
    "addMatch()\0addTag()\0remove()\0type\0"
    "addItem(creatorItem::Type)\0"
};

void smartPlaylistCreator::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        smartPlaylistCreator *_t = static_cast<smartPlaylistCreator *>(_o);
        switch (_id) {
        case 0: _t->closed((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 1: _t->addMatch(); break;
        case 2: _t->addTag(); break;
        case 3: _t->remove(); break;
        case 4: _t->addItem((*reinterpret_cast< creatorItem::Type(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData smartPlaylistCreator::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject smartPlaylistCreator::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_smartPlaylistCreator,
      qt_meta_data_smartPlaylistCreator, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &smartPlaylistCreator::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *smartPlaylistCreator::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *smartPlaylistCreator::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_smartPlaylistCreator))
        return static_cast<void*>(const_cast< smartPlaylistCreator*>(this));
    return QDialog::qt_metacast(_clname);
}

int smartPlaylistCreator::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void smartPlaylistCreator::closed(QString _t1, QString _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE

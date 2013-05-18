/****************************************************************************
** Meta object code from reading C++ file 'statusBar.h'
**
** Created:
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../src/lib/views/statusBar/statusBar.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'statusBar.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_views__statusBar[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      25,   18,   17,   17, 0x0a,
      52,   50,   17,   17, 0x2a,
      73,   17,   17,   17, 0x08,
      92,   88,   17,   17, 0x08,
     117,   17,   17,   17, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_views__statusBar[] = {
    "views::statusBar\0\0s,time\0"
    "showMessage(QString,int)\0s\0"
    "showMessage(QString)\0setTrackTime()\0"
    "job\0addJob(database::dbJobP)\0jobDone()\0"
};

void views::statusBar::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        statusBar *_t = static_cast<statusBar *>(_o);
        switch (_id) {
        case 0: _t->showMessage((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: _t->showMessage((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->setTrackTime(); break;
        case 3: _t->addJob((*reinterpret_cast< database::dbJobP(*)>(_a[1]))); break;
        case 4: _t->jobDone(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData views::statusBar::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject views::statusBar::staticMetaObject = {
    { &QStatusBar::staticMetaObject, qt_meta_stringdata_views__statusBar,
      qt_meta_data_views__statusBar, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &views::statusBar::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *views::statusBar::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *views::statusBar::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_views__statusBar))
        return static_cast<void*>(const_cast< statusBar*>(this));
    return QStatusBar::qt_metacast(_clname);
}

int views::statusBar::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QStatusBar::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    return _id;
}
QT_END_MOC_NAMESPACE

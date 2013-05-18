/****************************************************************************
** Meta object code from reading C++ file 'albumWidget.h'
**
** Created:
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../src/player/content/library/albumWidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'albumWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_albumWidget[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      13,   12,   12,   12, 0x05,
      25,   12,   12,   12, 0x05,

 // slots: signature, parameters, type, tag, flags
      37,   12,   12,   12, 0x0a,
      47,   12,   12,   12, 0x0a,
      57,   12,   12,   12, 0x0a,
      75,   73,   12,   12, 0x0a,
      97,   12,   12,   12, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_albumWidget[] = {
    "albumWidget\0\0scrolledR()\0scrolledL()\0"
    "scrollR()\0scrollL()\0updateEditors()\0"
    "m\0setModel(albumModel*)\0updateScroolBar()\0"
};

void albumWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        albumWidget *_t = static_cast<albumWidget *>(_o);
        switch (_id) {
        case 0: _t->scrolledR(); break;
        case 1: _t->scrolledL(); break;
        case 2: _t->scrollR(); break;
        case 3: _t->scrollL(); break;
        case 4: _t->updateEditors(); break;
        case 5: _t->setModel((*reinterpret_cast< albumModel*(*)>(_a[1]))); break;
        case 6: _t->updateScroolBar(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData albumWidget::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject albumWidget::staticMetaObject = {
    { &QListView::staticMetaObject, qt_meta_stringdata_albumWidget,
      qt_meta_data_albumWidget, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &albumWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *albumWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *albumWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_albumWidget))
        return static_cast<void*>(const_cast< albumWidget*>(this));
    return QListView::qt_metacast(_clname);
}

int albumWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QListView::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void albumWidget::scrolledR()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void albumWidget::scrolledL()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}
QT_END_MOC_NAMESPACE

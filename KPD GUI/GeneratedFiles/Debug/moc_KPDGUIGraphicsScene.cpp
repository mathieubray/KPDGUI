/****************************************************************************
** Meta object code from reading C++ file 'KPDGUIGraphicsScene.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../KPDGUIGraphicsScene.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'KPDGUIGraphicsScene.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_KPDGUIGraphicsScene_t {
    QByteArrayData data[13];
    char stringdata[170];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_KPDGUIGraphicsScene_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_KPDGUIGraphicsScene_t qt_meta_stringdata_KPDGUIGraphicsScene = {
    {
QT_MOC_LITERAL(0, 0, 19),
QT_MOC_LITERAL(1, 20, 10),
QT_MOC_LITERAL(2, 31, 0),
QT_MOC_LITERAL(3, 32, 1),
QT_MOC_LITERAL(4, 34, 8),
QT_MOC_LITERAL(5, 43, 13),
QT_MOC_LITERAL(6, 57, 13),
QT_MOC_LITERAL(7, 71, 8),
QT_MOC_LITERAL(8, 80, 10),
QT_MOC_LITERAL(9, 91, 17),
QT_MOC_LITERAL(10, 109, 19),
QT_MOC_LITERAL(11, 129, 20),
QT_MOC_LITERAL(12, 150, 19)
    },
    "KPDGUIGraphicsScene\0deleteNode\0\0i\0"
    "editNode\0screenChanged\0mouseReleased\0"
    "holdNode\0unholdNode\0holdMultipleNodes\0"
    "unholdMultipleNodes\0clusterMultipleNodes\0"
    "deleteMultipleNodes"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_KPDGUIGraphicsScene[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   74,    2, 0x06 /* Public */,
       4,    1,   77,    2, 0x06 /* Public */,
       5,    0,   80,    2, 0x06 /* Public */,
       6,    0,   81,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    0,   82,    2, 0x08 /* Private */,
       7,    0,   83,    2, 0x08 /* Private */,
       8,    0,   84,    2, 0x08 /* Private */,
       1,    0,   85,    2, 0x08 /* Private */,
       9,    0,   86,    2, 0x08 /* Private */,
      10,    0,   87,    2, 0x08 /* Private */,
      11,    0,   88,    2, 0x08 /* Private */,
      12,    0,   89,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void KPDGUIGraphicsScene::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        KPDGUIGraphicsScene *_t = static_cast<KPDGUIGraphicsScene *>(_o);
        switch (_id) {
        case 0: _t->deleteNode((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->editNode((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->screenChanged(); break;
        case 3: _t->mouseReleased(); break;
        case 4: _t->editNode(); break;
        case 5: _t->holdNode(); break;
        case 6: _t->unholdNode(); break;
        case 7: _t->deleteNode(); break;
        case 8: _t->holdMultipleNodes(); break;
        case 9: _t->unholdMultipleNodes(); break;
        case 10: _t->clusterMultipleNodes(); break;
        case 11: _t->deleteMultipleNodes(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (KPDGUIGraphicsScene::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&KPDGUIGraphicsScene::deleteNode)) {
                *result = 0;
            }
        }
        {
            typedef void (KPDGUIGraphicsScene::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&KPDGUIGraphicsScene::editNode)) {
                *result = 1;
            }
        }
        {
            typedef void (KPDGUIGraphicsScene::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&KPDGUIGraphicsScene::screenChanged)) {
                *result = 2;
            }
        }
        {
            typedef void (KPDGUIGraphicsScene::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&KPDGUIGraphicsScene::mouseReleased)) {
                *result = 3;
            }
        }
    }
}

const QMetaObject KPDGUIGraphicsScene::staticMetaObject = {
    { &QGraphicsScene::staticMetaObject, qt_meta_stringdata_KPDGUIGraphicsScene.data,
      qt_meta_data_KPDGUIGraphicsScene,  qt_static_metacall, 0, 0}
};


const QMetaObject *KPDGUIGraphicsScene::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *KPDGUIGraphicsScene::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_KPDGUIGraphicsScene.stringdata))
        return static_cast<void*>(const_cast< KPDGUIGraphicsScene*>(this));
    return QGraphicsScene::qt_metacast(_clname);
}

int KPDGUIGraphicsScene::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGraphicsScene::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 12;
    }
    return _id;
}

// SIGNAL 0
void KPDGUIGraphicsScene::deleteNode(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void KPDGUIGraphicsScene::editNode(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void KPDGUIGraphicsScene::screenChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}

// SIGNAL 3
void KPDGUIGraphicsScene::mouseReleased()
{
    QMetaObject::activate(this, &staticMetaObject, 3, 0);
}
QT_END_MOC_NAMESPACE

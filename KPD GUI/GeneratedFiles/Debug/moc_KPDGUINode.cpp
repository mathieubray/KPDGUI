/****************************************************************************
** Meta object code from reading C++ file 'KPDGUINode.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../KPDGUINode.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'KPDGUINode.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_KPDGUINode_t {
    QByteArrayData data[15];
    char stringdata[190];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_KPDGUINode_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_KPDGUINode_t qt_meta_stringdata_KPDGUINode = {
    {
QT_MOC_LITERAL(0, 0, 10),
QT_MOC_LITERAL(1, 11, 14),
QT_MOC_LITERAL(2, 26, 0),
QT_MOC_LITERAL(3, 27, 1),
QT_MOC_LITERAL(4, 29, 8),
QT_MOC_LITERAL(5, 38, 20),
QT_MOC_LITERAL(6, 59, 21),
QT_MOC_LITERAL(7, 81, 4),
QT_MOC_LITERAL(8, 86, 10),
QT_MOC_LITERAL(9, 97, 11),
QT_MOC_LITERAL(10, 109, 8),
QT_MOC_LITERAL(11, 118, 16),
QT_MOC_LITERAL(12, 135, 22),
QT_MOC_LITERAL(13, 158, 15),
QT_MOC_LITERAL(14, 174, 15)
    },
    "KPDGUINode\0nodeWasClicked\0\0i\0selected\0"
    "nodeSelectionChanged\0nodeHoldStatusChanged\0"
    "held\0nodeEdited\0nodeEntered\0nodeLeft\0"
    "updateVisibility\0KPDGUIDisplaySettings*\0"
    "displaySettings\0selectIfVisible"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_KPDGUINode[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   54,    2, 0x06 /* Public */,
       5,    2,   59,    2, 0x06 /* Public */,
       6,    2,   64,    2, 0x06 /* Public */,
       8,    1,   69,    2, 0x06 /* Public */,
       9,    1,   72,    2, 0x06 /* Public */,
      10,    1,   75,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      11,    1,   78,    2, 0x0a /* Public */,
      14,    0,   81,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Bool,    3,    4,
    QMetaType::Void, QMetaType::Int, QMetaType::Bool,    3,    4,
    QMetaType::Void, QMetaType::Int, QMetaType::Bool,    3,    7,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 12,   13,
    QMetaType::Void,

       0        // eod
};

void KPDGUINode::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        KPDGUINode *_t = static_cast<KPDGUINode *>(_o);
        switch (_id) {
        case 0: _t->nodeWasClicked((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 1: _t->nodeSelectionChanged((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 2: _t->nodeHoldStatusChanged((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 3: _t->nodeEdited((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->nodeEntered((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->nodeLeft((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->updateVisibility((*reinterpret_cast< KPDGUIDisplaySettings*(*)>(_a[1]))); break;
        case 7: _t->selectIfVisible(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (KPDGUINode::*_t)(int , bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&KPDGUINode::nodeWasClicked)) {
                *result = 0;
            }
        }
        {
            typedef void (KPDGUINode::*_t)(int , bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&KPDGUINode::nodeSelectionChanged)) {
                *result = 1;
            }
        }
        {
            typedef void (KPDGUINode::*_t)(int , bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&KPDGUINode::nodeHoldStatusChanged)) {
                *result = 2;
            }
        }
        {
            typedef void (KPDGUINode::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&KPDGUINode::nodeEdited)) {
                *result = 3;
            }
        }
        {
            typedef void (KPDGUINode::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&KPDGUINode::nodeEntered)) {
                *result = 4;
            }
        }
        {
            typedef void (KPDGUINode::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&KPDGUINode::nodeLeft)) {
                *result = 5;
            }
        }
    }
}

const QMetaObject KPDGUINode::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_KPDGUINode.data,
      qt_meta_data_KPDGUINode,  qt_static_metacall, 0, 0}
};


const QMetaObject *KPDGUINode::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *KPDGUINode::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_KPDGUINode.stringdata))
        return static_cast<void*>(const_cast< KPDGUINode*>(this));
    if (!strcmp(_clname, "QGraphicsItemGroup"))
        return static_cast< QGraphicsItemGroup*>(const_cast< KPDGUINode*>(this));
    return QObject::qt_metacast(_clname);
}

int KPDGUINode::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void KPDGUINode::nodeWasClicked(int _t1, bool _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void KPDGUINode::nodeSelectionChanged(int _t1, bool _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void KPDGUINode::nodeHoldStatusChanged(int _t1, bool _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void KPDGUINode::nodeEdited(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void KPDGUINode::nodeEntered(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void KPDGUINode::nodeLeft(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}
QT_END_MOC_NAMESPACE

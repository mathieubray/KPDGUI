/****************************************************************************
** Meta object code from reading C++ file 'KPDGUINode.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../KPDGUINode.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'KPDGUINode.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_KPDGUINode_t {
    QByteArrayData data[8];
    char stringdata0[109];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_KPDGUINode_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_KPDGUINode_t qt_meta_stringdata_KPDGUINode = {
    {
QT_MOC_LITERAL(0, 0, 10), // "KPDGUINode"
QT_MOC_LITERAL(1, 11, 16), // "updateVisibility"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 22), // "KPDGUIDisplaySettings*"
QT_MOC_LITERAL(4, 52, 15), // "displaySettings"
QT_MOC_LITERAL(5, 68, 11), // "clusterNode"
QT_MOC_LITERAL(6, 80, 13), // "highlightNode"
QT_MOC_LITERAL(7, 94, 14) // "clearHighlight"

    },
    "KPDGUINode\0updateVisibility\0\0"
    "KPDGUIDisplaySettings*\0displaySettings\0"
    "clusterNode\0highlightNode\0clearHighlight"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_KPDGUINode[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   34,    2, 0x0a /* Public */,
       5,    0,   37,    2, 0x0a /* Public */,
       6,    0,   38,    2, 0x0a /* Public */,
       7,    0,   39,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void KPDGUINode::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        KPDGUINode *_t = static_cast<KPDGUINode *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->updateVisibility((*reinterpret_cast< KPDGUIDisplaySettings*(*)>(_a[1]))); break;
        case 1: _t->clusterNode(); break;
        case 2: _t->highlightNode(); break;
        case 3: _t->clearHighlight(); break;
        default: ;
        }
    }
}

const QMetaObject KPDGUINode::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_KPDGUINode.data,
      qt_meta_data_KPDGUINode,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *KPDGUINode::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *KPDGUINode::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_KPDGUINode.stringdata0))
        return static_cast<void*>(const_cast< KPDGUINode*>(this));
    return QObject::qt_metacast(_clname);
}

int KPDGUINode::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE

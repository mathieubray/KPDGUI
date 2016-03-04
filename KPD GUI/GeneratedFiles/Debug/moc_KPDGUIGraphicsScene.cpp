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
    QByteArrayData data[20];
    char stringdata[311];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_KPDGUIGraphicsScene_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_KPDGUIGraphicsScene_t qt_meta_stringdata_KPDGUIGraphicsScene = {
    {
QT_MOC_LITERAL(0, 0, 19),
QT_MOC_LITERAL(1, 20, 18),
QT_MOC_LITERAL(2, 39, 0),
QT_MOC_LITERAL(3, 40, 1),
QT_MOC_LITERAL(4, 42, 27),
QT_MOC_LITERAL(5, 70, 26),
QT_MOC_LITERAL(6, 97, 21),
QT_MOC_LITERAL(7, 119, 18),
QT_MOC_LITERAL(8, 138, 10),
QT_MOC_LITERAL(9, 149, 8),
QT_MOC_LITERAL(10, 158, 13),
QT_MOC_LITERAL(11, 172, 13),
QT_MOC_LITERAL(12, 186, 8),
QT_MOC_LITERAL(13, 195, 10),
QT_MOC_LITERAL(14, 206, 17),
QT_MOC_LITERAL(15, 224, 19),
QT_MOC_LITERAL(16, 244, 20),
QT_MOC_LITERAL(17, 265, 19),
QT_MOC_LITERAL(18, 285, 9),
QT_MOC_LITERAL(19, 295, 15)
    },
    "KPDGUIGraphicsScene\0addAssociatedDonor\0"
    "\0i\0highlightRelevantStructures\0"
    "highlightRelevantSolutions\0"
    "selectAllVisibleNodes\0clearAllHighlights\0"
    "deleteNode\0editNode\0screenChanged\0"
    "mouseReleased\0holdNode\0unholdNode\0"
    "holdMultipleNodes\0unholdMultipleNodes\0"
    "clusterMultipleNodes\0deleteMultipleNodes\0"
    "selectAll\0clearHighlights"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_KPDGUIGraphicsScene[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      22,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       9,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,  124,    2, 0x06 /* Public */,
       4,    1,  127,    2, 0x06 /* Public */,
       5,    1,  130,    2, 0x06 /* Public */,
       6,    0,  133,    2, 0x06 /* Public */,
       7,    0,  134,    2, 0x06 /* Public */,
       8,    1,  135,    2, 0x06 /* Public */,
       9,    1,  138,    2, 0x06 /* Public */,
      10,    0,  141,    2, 0x06 /* Public */,
      11,    0,  142,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       1,    0,  143,    2, 0x08 /* Private */,
       4,    0,  144,    2, 0x08 /* Private */,
       5,    0,  145,    2, 0x08 /* Private */,
       9,    0,  146,    2, 0x08 /* Private */,
      12,    0,  147,    2, 0x08 /* Private */,
      13,    0,  148,    2, 0x08 /* Private */,
       8,    0,  149,    2, 0x08 /* Private */,
      14,    0,  150,    2, 0x08 /* Private */,
      15,    0,  151,    2, 0x08 /* Private */,
      16,    0,  152,    2, 0x08 /* Private */,
      17,    0,  153,    2, 0x08 /* Private */,
      18,    0,  154,    2, 0x08 /* Private */,
      19,    0,  155,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void,
    QMetaType::Void,
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
        case 0: _t->addAssociatedDonor((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->highlightRelevantStructures((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->highlightRelevantSolutions((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->selectAllVisibleNodes(); break;
        case 4: _t->clearAllHighlights(); break;
        case 5: _t->deleteNode((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->editNode((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->screenChanged(); break;
        case 8: _t->mouseReleased(); break;
        case 9: _t->addAssociatedDonor(); break;
        case 10: _t->highlightRelevantStructures(); break;
        case 11: _t->highlightRelevantSolutions(); break;
        case 12: _t->editNode(); break;
        case 13: _t->holdNode(); break;
        case 14: _t->unholdNode(); break;
        case 15: _t->deleteNode(); break;
        case 16: _t->holdMultipleNodes(); break;
        case 17: _t->unholdMultipleNodes(); break;
        case 18: _t->clusterMultipleNodes(); break;
        case 19: _t->deleteMultipleNodes(); break;
        case 20: _t->selectAll(); break;
        case 21: _t->clearHighlights(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (KPDGUIGraphicsScene::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&KPDGUIGraphicsScene::addAssociatedDonor)) {
                *result = 0;
            }
        }
        {
            typedef void (KPDGUIGraphicsScene::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&KPDGUIGraphicsScene::highlightRelevantStructures)) {
                *result = 1;
            }
        }
        {
            typedef void (KPDGUIGraphicsScene::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&KPDGUIGraphicsScene::highlightRelevantSolutions)) {
                *result = 2;
            }
        }
        {
            typedef void (KPDGUIGraphicsScene::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&KPDGUIGraphicsScene::selectAllVisibleNodes)) {
                *result = 3;
            }
        }
        {
            typedef void (KPDGUIGraphicsScene::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&KPDGUIGraphicsScene::clearAllHighlights)) {
                *result = 4;
            }
        }
        {
            typedef void (KPDGUIGraphicsScene::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&KPDGUIGraphicsScene::deleteNode)) {
                *result = 5;
            }
        }
        {
            typedef void (KPDGUIGraphicsScene::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&KPDGUIGraphicsScene::editNode)) {
                *result = 6;
            }
        }
        {
            typedef void (KPDGUIGraphicsScene::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&KPDGUIGraphicsScene::screenChanged)) {
                *result = 7;
            }
        }
        {
            typedef void (KPDGUIGraphicsScene::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&KPDGUIGraphicsScene::mouseReleased)) {
                *result = 8;
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
        if (_id < 22)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 22;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 22)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 22;
    }
    return _id;
}

// SIGNAL 0
void KPDGUIGraphicsScene::addAssociatedDonor(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void KPDGUIGraphicsScene::highlightRelevantStructures(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void KPDGUIGraphicsScene::highlightRelevantSolutions(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void KPDGUIGraphicsScene::selectAllVisibleNodes()
{
    QMetaObject::activate(this, &staticMetaObject, 3, 0);
}

// SIGNAL 4
void KPDGUIGraphicsScene::clearAllHighlights()
{
    QMetaObject::activate(this, &staticMetaObject, 4, 0);
}

// SIGNAL 5
void KPDGUIGraphicsScene::deleteNode(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void KPDGUIGraphicsScene::editNode(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void KPDGUIGraphicsScene::screenChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 7, 0);
}

// SIGNAL 8
void KPDGUIGraphicsScene::mouseReleased()
{
    QMetaObject::activate(this, &staticMetaObject, 8, 0);
}
QT_END_MOC_NAMESPACE

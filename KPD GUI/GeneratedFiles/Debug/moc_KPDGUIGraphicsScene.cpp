/****************************************************************************
** Meta object code from reading C++ file 'KPDGUIGraphicsScene.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../KPDGUIGraphicsScene.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'KPDGUIGraphicsScene.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_KPDGUIGraphicsScene_t {
    QByteArrayData data[14];
    char stringdata0[167];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_KPDGUIGraphicsScene_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_KPDGUIGraphicsScene_t qt_meta_stringdata_KPDGUIGraphicsScene = {
    {
QT_MOC_LITERAL(0, 0, 19), // "KPDGUIGraphicsScene"
QT_MOC_LITERAL(1, 20, 22), // "updateVisibilitySignal"
QT_MOC_LITERAL(2, 43, 0), // ""
QT_MOC_LITERAL(3, 44, 17), // "addNewDonorSignal"
QT_MOC_LITERAL(4, 62, 16), // "KPDGUICandidate*"
QT_MOC_LITERAL(5, 79, 9), // "candidate"
QT_MOC_LITERAL(6, 89, 18), // "selectionClustered"
QT_MOC_LITERAL(7, 108, 1), // "x"
QT_MOC_LITERAL(8, 110, 1), // "y"
QT_MOC_LITERAL(9, 112, 4), // "edit"
QT_MOC_LITERAL(10, 117, 18), // "addAdditionalDonor"
QT_MOC_LITERAL(11, 136, 12), // "changeStatus"
QT_MOC_LITERAL(12, 149, 7), // "cluster"
QT_MOC_LITERAL(13, 157, 9) // "selectAll"

    },
    "KPDGUIGraphicsScene\0updateVisibilitySignal\0"
    "\0addNewDonorSignal\0KPDGUICandidate*\0"
    "candidate\0selectionClustered\0x\0y\0edit\0"
    "addAdditionalDonor\0changeStatus\0cluster\0"
    "selectAll"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_KPDGUIGraphicsScene[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   54,    2, 0x06 /* Public */,
       3,    1,   55,    2, 0x06 /* Public */,
       6,    2,   58,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       9,    0,   63,    2, 0x08 /* Private */,
      10,    0,   64,    2, 0x08 /* Private */,
      11,    0,   65,    2, 0x08 /* Private */,
      12,    0,   66,    2, 0x08 /* Private */,
      13,    0,   67,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 4,    5,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    7,    8,

 // slots: parameters
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
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->updateVisibilitySignal(); break;
        case 1: _t->addNewDonorSignal((*reinterpret_cast< KPDGUICandidate*(*)>(_a[1]))); break;
        case 2: _t->selectionClustered((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 3: _t->edit(); break;
        case 4: _t->addAdditionalDonor(); break;
        case 5: _t->changeStatus(); break;
        case 6: _t->cluster(); break;
        case 7: _t->selectAll(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< KPDGUICandidate* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (KPDGUIGraphicsScene::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&KPDGUIGraphicsScene::updateVisibilitySignal)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (KPDGUIGraphicsScene::*_t)(KPDGUICandidate * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&KPDGUIGraphicsScene::addNewDonorSignal)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (KPDGUIGraphicsScene::*_t)(int , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&KPDGUIGraphicsScene::selectionClustered)) {
                *result = 2;
                return;

            }
        }
    }
}

const QMetaObject KPDGUIGraphicsScene::staticMetaObject = {
    { &QGraphicsScene::staticMetaObject, qt_meta_stringdata_KPDGUIGraphicsScene.data,
      qt_meta_data_KPDGUIGraphicsScene,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *KPDGUIGraphicsScene::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *KPDGUIGraphicsScene::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_KPDGUIGraphicsScene.stringdata0))
        return static_cast<void*>(const_cast< KPDGUIGraphicsScene*>(this));
    return QGraphicsScene::qt_metacast(_clname);
}

int KPDGUIGraphicsScene::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGraphicsScene::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void KPDGUIGraphicsScene::updateVisibilitySignal()
{

    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);

}

// SIGNAL 1
void KPDGUIGraphicsScene::addNewDonorSignal(KPDGUICandidate * _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2

void KPDGUIGraphicsScene::selectionClustered(int _t1, int _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);

}
QT_END_MOC_NAMESPACE

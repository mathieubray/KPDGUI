/****************************************************************************
** Meta object code from reading C++ file 'KPDGUIArrow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../KPDGUIArrow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'KPDGUIArrow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_KPDGUIArrow_t {
    QByteArrayData data[10];
    char stringdata[152];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_KPDGUIArrow_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_KPDGUIArrow_t qt_meta_stringdata_KPDGUIArrow = {
    {
QT_MOC_LITERAL(0, 0, 11),
QT_MOC_LITERAL(1, 12, 22),
QT_MOC_LITERAL(2, 35, 0),
QT_MOC_LITERAL(3, 36, 20),
QT_MOC_LITERAL(4, 57, 2),
QT_MOC_LITERAL(5, 60, 8),
QT_MOC_LITERAL(6, 69, 16),
QT_MOC_LITERAL(7, 86, 22),
QT_MOC_LITERAL(8, 109, 15),
QT_MOC_LITERAL(9, 125, 26)
    },
    "KPDGUIArrow\0selectArrowInMatchList\0\0"
    "changeArrowSelection\0id\0selected\0"
    "updateVisibility\0KPDGUIDisplaySettings*\0"
    "displaySettings\0endDisplayAsPartOfSolution"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_KPDGUIArrow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   34,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    2,   37,    2, 0x0a /* Public */,
       6,    1,   42,    2, 0x0a /* Public */,
       9,    0,   45,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Bool,    2,

 // slots: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Bool,    4,    5,
    QMetaType::Void, 0x80000000 | 7,    8,
    QMetaType::Void,

       0        // eod
};

void KPDGUIArrow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        KPDGUIArrow *_t = static_cast<KPDGUIArrow *>(_o);
        switch (_id) {
        case 0: _t->selectArrowInMatchList((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->changeArrowSelection((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 2: _t->updateVisibility((*reinterpret_cast< KPDGUIDisplaySettings*(*)>(_a[1]))); break;
        case 3: _t->endDisplayAsPartOfSolution(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (KPDGUIArrow::*_t)(bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&KPDGUIArrow::selectArrowInMatchList)) {
                *result = 0;
            }
        }
    }
}

const QMetaObject KPDGUIArrow::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_KPDGUIArrow.data,
      qt_meta_data_KPDGUIArrow,  qt_static_metacall, 0, 0}
};


const QMetaObject *KPDGUIArrow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *KPDGUIArrow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_KPDGUIArrow.stringdata))
        return static_cast<void*>(const_cast< KPDGUIArrow*>(this));
    if (!strcmp(_clname, "QGraphicsLineItem"))
        return static_cast< QGraphicsLineItem*>(const_cast< KPDGUIArrow*>(this));
    return QObject::qt_metacast(_clname);
}

int KPDGUIArrow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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

// SIGNAL 0
void KPDGUIArrow::selectArrowInMatchList(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE

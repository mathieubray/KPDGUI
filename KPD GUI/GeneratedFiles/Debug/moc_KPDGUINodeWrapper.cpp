/****************************************************************************
** Meta object code from reading C++ file 'KPDGUINodeWrapper.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../KPDGUINodeWrapper.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'KPDGUINodeWrapper.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_KPDGUINodeWrapper_t {
    QByteArrayData data[7];
    char stringdata0[90];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_KPDGUINodeWrapper_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_KPDGUINodeWrapper_t qt_meta_stringdata_KPDGUINodeWrapper = {
    {
QT_MOC_LITERAL(0, 0, 17), // "KPDGUINodeWrapper"
QT_MOC_LITERAL(1, 18, 11), // "editActions"
QT_MOC_LITERAL(2, 30, 0), // ""
QT_MOC_LITERAL(3, 31, 13), // "highlightNode"
QT_MOC_LITERAL(4, 45, 16), // "QTreeWidgetItem*"
QT_MOC_LITERAL(5, 62, 16), // "updateSelections"
QT_MOC_LITERAL(6, 79, 10) // "updateText"

    },
    "KPDGUINodeWrapper\0editActions\0\0"
    "highlightNode\0QTreeWidgetItem*\0"
    "updateSelections\0updateText"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_KPDGUINodeWrapper[] = {

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
       1,    0,   34,    2, 0x0a /* Public */,
       3,    1,   35,    2, 0x0a /* Public */,
       5,    0,   38,    2, 0x0a /* Public */,
       6,    0,   39,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 4,    2,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void KPDGUINodeWrapper::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        KPDGUINodeWrapper *_t = static_cast<KPDGUINodeWrapper *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->editActions(); break;
        case 1: _t->highlightNode((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1]))); break;
        case 2: _t->updateSelections(); break;
        case 3: _t->updateText(); break;
        default: ;
        }
    }
}

const QMetaObject KPDGUINodeWrapper::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_KPDGUINodeWrapper.data,
      qt_meta_data_KPDGUINodeWrapper,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *KPDGUINodeWrapper::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *KPDGUINodeWrapper::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_KPDGUINodeWrapper.stringdata0))
        return static_cast<void*>(const_cast< KPDGUINodeWrapper*>(this));
    if (!strcmp(_clname, "QTreeWidgetItem"))
        return static_cast< QTreeWidgetItem*>(const_cast< KPDGUINodeWrapper*>(this));
    return QObject::qt_metacast(_clname);
}

int KPDGUINodeWrapper::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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

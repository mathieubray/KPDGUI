/****************************************************************************
** Meta object code from reading C++ file 'KPDGUIRecord.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../KPDGUIRecord.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'KPDGUIRecord.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_KPDGUIRecord_t {
    QByteArrayData data[7];
    char stringdata0[87];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_KPDGUIRecord_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_KPDGUIRecord_t qt_meta_stringdata_KPDGUIRecord = {
    {
QT_MOC_LITERAL(0, 0, 12), // "KPDGUIRecord"
QT_MOC_LITERAL(1, 13, 31), // "takeAdditionalDeleteNodeActions"
QT_MOC_LITERAL(2, 45, 0), // ""
QT_MOC_LITERAL(3, 46, 11), // "KPDGUINode*"
QT_MOC_LITERAL(4, 58, 4), // "node"
QT_MOC_LITERAL(5, 63, 20), // "deleteNodeFromRecord"
QT_MOC_LITERAL(6, 84, 2) // "id"

    },
    "KPDGUIRecord\0takeAdditionalDeleteNodeActions\0"
    "\0KPDGUINode*\0node\0deleteNodeFromRecord\0"
    "id"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_KPDGUIRecord[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   24,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    1,   27,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    6,

       0        // eod
};

void KPDGUIRecord::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        KPDGUIRecord *_t = static_cast<KPDGUIRecord *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->takeAdditionalDeleteNodeActions((*reinterpret_cast< KPDGUINode*(*)>(_a[1]))); break;
        case 1: _t->deleteNodeFromRecord((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< KPDGUINode* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (KPDGUIRecord::*_t)(KPDGUINode * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&KPDGUIRecord::takeAdditionalDeleteNodeActions)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject KPDGUIRecord::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_KPDGUIRecord.data,
      qt_meta_data_KPDGUIRecord,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *KPDGUIRecord::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *KPDGUIRecord::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_KPDGUIRecord.stringdata0))
        return static_cast<void*>(const_cast< KPDGUIRecord*>(this));
    return QObject::qt_metacast(_clname);
}

int KPDGUIRecord::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void KPDGUIRecord::takeAdditionalDeleteNodeActions(KPDGUINode * _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE

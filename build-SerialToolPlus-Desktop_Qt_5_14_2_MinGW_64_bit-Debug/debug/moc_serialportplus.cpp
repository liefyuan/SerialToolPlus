/****************************************************************************
** Meta object code from reading C++ file 'serialportplus.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../SerialToolPlus/serialportplus.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'serialportplus.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_serialportplus_t {
    QByteArrayData data[13];
    char stringdata0[105];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_serialportplus_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_serialportplus_t qt_meta_stringdata_serialportplus = {
    {
QT_MOC_LITERAL(0, 0, 14), // "serialportplus"
QT_MOC_LITERAL(1, 15, 10), // "sigStarted"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 7), // "sigStop"
QT_MOC_LITERAL(4, 35, 6), // "status"
QT_MOC_LITERAL(5, 42, 11), // "sigReceived"
QT_MOC_LITERAL(6, 54, 4), // "data"
QT_MOC_LITERAL(7, 59, 9), // "startPort"
QT_MOC_LITERAL(8, 69, 8), // "Settings"
QT_MOC_LITERAL(9, 78, 4), // "sets"
QT_MOC_LITERAL(10, 83, 8), // "stopPort"
QT_MOC_LITERAL(11, 92, 8), // "sendData"
QT_MOC_LITERAL(12, 101, 3) // "arr"

    },
    "serialportplus\0sigStarted\0\0sigStop\0"
    "status\0sigReceived\0data\0startPort\0"
    "Settings\0sets\0stopPort\0sendData\0arr"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_serialportplus[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   44,    2, 0x06 /* Public */,
       3,    1,   45,    2, 0x06 /* Public */,
       5,    1,   48,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    1,   51,    2, 0x0a /* Public */,
      10,    0,   54,    2, 0x0a /* Public */,
      11,    1,   55,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    4,
    QMetaType::Void, QMetaType::QByteArray,    6,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 8,    9,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QByteArray,   12,

       0        // eod
};

void serialportplus::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<serialportplus *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sigStarted(); break;
        case 1: _t->sigStop((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->sigReceived((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 3: _t->startPort((*reinterpret_cast< Settings(*)>(_a[1]))); break;
        case 4: _t->stopPort(); break;
        case 5: _t->sendData((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (serialportplus::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&serialportplus::sigStarted)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (serialportplus::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&serialportplus::sigStop)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (serialportplus::*)(QByteArray );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&serialportplus::sigReceived)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject serialportplus::staticMetaObject = { {
    QMetaObject::SuperData::link<QSerialPort::staticMetaObject>(),
    qt_meta_stringdata_serialportplus.data,
    qt_meta_data_serialportplus,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *serialportplus::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *serialportplus::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_serialportplus.stringdata0))
        return static_cast<void*>(this);
    return QSerialPort::qt_metacast(_clname);
}

int serialportplus::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QSerialPort::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void serialportplus::sigStarted()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void serialportplus::sigStop(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void serialportplus::sigReceived(QByteArray _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE

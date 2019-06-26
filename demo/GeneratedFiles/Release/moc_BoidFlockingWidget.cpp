/****************************************************************************
** Meta object code from reading C++ file 'BoidFlockingWidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.10.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../flocking/BoidFlockingWidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'BoidFlockingWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.10.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_BoidFlockingWidget_t {
    QByteArrayData data[7];
    char stringdata0[87];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_BoidFlockingWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_BoidFlockingWidget_t qt_meta_stringdata_BoidFlockingWidget = {
    {
QT_MOC_LITERAL(0, 0, 18), // "BoidFlockingWidget"
QT_MOC_LITERAL(1, 19, 11), // "setMaxSpeed"
QT_MOC_LITERAL(2, 31, 0), // ""
QT_MOC_LITERAL(3, 32, 1), // "v"
QT_MOC_LITERAL(4, 34, 11), // "setMaxForce"
QT_MOC_LITERAL(5, 46, 23), // "setMinNeighbordDistance"
QT_MOC_LITERAL(6, 70, 16) // "setMinSeparation"

    },
    "BoidFlockingWidget\0setMaxSpeed\0\0v\0"
    "setMaxForce\0setMinNeighbordDistance\0"
    "setMinSeparation"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_BoidFlockingWidget[] = {

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
       4,    1,   37,    2, 0x0a /* Public */,
       5,    1,   40,    2, 0x0a /* Public */,
       6,    1,   43,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,

       0        // eod
};

void BoidFlockingWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        BoidFlockingWidget *_t = static_cast<BoidFlockingWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->setMaxSpeed((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->setMaxForce((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->setMinNeighbordDistance((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->setMinSeparation((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject BoidFlockingWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_BoidFlockingWidget.data,
      qt_meta_data_BoidFlockingWidget,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *BoidFlockingWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *BoidFlockingWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_BoidFlockingWidget.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int BoidFlockingWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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
QT_WARNING_POP
QT_END_MOC_NAMESPACE

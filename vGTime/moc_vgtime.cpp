/****************************************************************************
** Meta object code from reading C++ file 'vgtime.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.9)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "vgtime.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'vgtime.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.9. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_vGTime_t {
    QByteArrayData data[6];
    char stringdata0[49];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_vGTime_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_vGTime_t qt_meta_stringdata_vGTime = {
    {
QT_MOC_LITERAL(0, 0, 6), // "vGTime"
QT_MOC_LITERAL(1, 7, 11), // "update_time"
QT_MOC_LITERAL(2, 19, 0), // ""
QT_MOC_LITERAL(3, 20, 11), // "update_size"
QT_MOC_LITERAL(4, 32, 5), // "_size"
QT_MOC_LITERAL(5, 38, 10) // "UpdateSkin"

    },
    "vGTime\0update_time\0\0update_size\0_size\0"
    "UpdateSkin"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_vGTime[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   29,    2, 0x0a /* Public */,
       3,    1,   30,    2, 0x0a /* Public */,
       5,    0,   33,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QSize,    4,
    QMetaType::Void,

       0        // eod
};

void vGTime::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        vGTime *_t = static_cast<vGTime *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->update_time(); break;
        case 1: _t->update_size((*reinterpret_cast< QSize(*)>(_a[1]))); break;
        case 2: _t->UpdateSkin(); break;
        default: ;
        }
    }
}

const QMetaObject vGTime::staticMetaObject = {
    { &vGAppWidBase::staticMetaObject, qt_meta_stringdata_vGTime.data,
      qt_meta_data_vGTime,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *vGTime::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *vGTime::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_vGTime.stringdata0))
        return static_cast<void*>(this);
    return vGAppWidBase::qt_metacast(_clname);
}

int vGTime::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = vGAppWidBase::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE

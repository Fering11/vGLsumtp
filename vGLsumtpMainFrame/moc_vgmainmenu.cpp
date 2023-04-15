/****************************************************************************
** Meta object code from reading C++ file 'vgmainmenu.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.9)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "vgmainmenu.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'vgmainmenu.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.9. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_vGMainMenu_Private_t {
    QByteArrayData data[2];
    char stringdata0[30];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_vGMainMenu_Private_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_vGMainMenu_Private_t qt_meta_stringdata_vGMainMenu_Private = {
    {
QT_MOC_LITERAL(0, 0, 18), // "vGMainMenu_Private"
QT_MOC_LITERAL(1, 19, 10) // "front_show"

    },
    "vGMainMenu_Private\0front_show"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_vGMainMenu_Private[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       1,   14, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // properties: name, type, flags
       1, QMetaType::Int, 0x00095003,

       0        // eod
};

void vGMainMenu_Private::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{

#ifndef QT_NO_PROPERTIES
    if (_c == QMetaObject::ReadProperty) {
        vGMainMenu_Private *_t = static_cast<vGMainMenu_Private *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< qint32*>(_v) = _t->front_show(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        vGMainMenu_Private *_t = static_cast<vGMainMenu_Private *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->set_front_show(*reinterpret_cast< qint32*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObject vGMainMenu_Private::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_vGMainMenu_Private.data,
      qt_meta_data_vGMainMenu_Private,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *vGMainMenu_Private::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *vGMainMenu_Private::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_vGMainMenu_Private.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int vGMainMenu_Private::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    
#ifndef QT_NO_PROPERTIES
   if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 1;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}
struct qt_meta_stringdata_vGMainMenu_t {
    QByteArrayData data[14];
    char stringdata0[144];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_vGMainMenu_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_vGMainMenu_t qt_meta_stringdata_vGMainMenu = {
    {
QT_MOC_LITERAL(0, 0, 10), // "vGMainMenu"
QT_MOC_LITERAL(1, 11, 13), // "ReleaseWindow"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 13), // "vGAppWidBase*"
QT_MOC_LITERAL(4, 40, 7), // "_object"
QT_MOC_LITERAL(5, 48, 12), // "LaunchWidget"
QT_MOC_LITERAL(6, 61, 10), // "UpdateSkin"
QT_MOC_LITERAL(7, 72, 12), // "UpdateLayout"
QT_MOC_LITERAL(8, 85, 6), // "Action"
QT_MOC_LITERAL(9, 92, 7), // "_action"
QT_MOC_LITERAL(10, 100, 9), // "_new_size"
QT_MOC_LITERAL(11, 110, 11), // "ac_turnLeft"
QT_MOC_LITERAL(12, 122, 12), // "ac_turnRight"
QT_MOC_LITERAL(13, 135, 8) // "ac_enter"

    },
    "vGMainMenu\0ReleaseWindow\0\0vGAppWidBase*\0"
    "_object\0LaunchWidget\0UpdateSkin\0"
    "UpdateLayout\0Action\0_action\0_new_size\0"
    "ac_turnLeft\0ac_turnRight\0ac_enter"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_vGMainMenu[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   54,    2, 0x0a /* Public */,
       5,    1,   57,    2, 0x0a /* Public */,
       6,    0,   60,    2, 0x0a /* Public */,
       7,    2,   61,    2, 0x0a /* Public */,
       7,    1,   66,    2, 0x2a /* Public | MethodCloned */,
      11,    0,   69,    2, 0x0a /* Public */,
      12,    0,   70,    2, 0x0a /* Public */,
      13,    0,   71,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 8, QMetaType::QSize,    9,   10,
    QMetaType::Void, 0x80000000 | 8,    9,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void vGMainMenu::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        vGMainMenu *_t = static_cast<vGMainMenu *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->ReleaseWindow((*reinterpret_cast< vGAppWidBase*(*)>(_a[1]))); break;
        case 1: _t->LaunchWidget((*reinterpret_cast< vGAppWidBase*(*)>(_a[1]))); break;
        case 2: _t->UpdateSkin(); break;
        case 3: _t->UpdateLayout((*reinterpret_cast< Action(*)>(_a[1])),(*reinterpret_cast< QSize(*)>(_a[2]))); break;
        case 4: _t->UpdateLayout((*reinterpret_cast< Action(*)>(_a[1]))); break;
        case 5: _t->ac_turnLeft(); break;
        case 6: _t->ac_turnRight(); break;
        case 7: _t->ac_enter(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< vGAppWidBase* >(); break;
            }
            break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< vGAppWidBase* >(); break;
            }
            break;
        }
    }
}

const QMetaObject vGMainMenu::staticMetaObject = {
    { &vGMenuBase::staticMetaObject, qt_meta_stringdata_vGMainMenu.data,
      qt_meta_data_vGMainMenu,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *vGMainMenu::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *vGMainMenu::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_vGMainMenu.stringdata0))
        return static_cast<void*>(this);
    return vGMenuBase::qt_metacast(_clname);
}

int vGMainMenu::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = vGMenuBase::qt_metacall(_c, _id, _a);
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
QT_WARNING_POP
QT_END_MOC_NAMESPACE

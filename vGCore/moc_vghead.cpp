/****************************************************************************
** Meta object code from reading C++ file 'vghead.hpp'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.9)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "vghead.hpp"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'vghead.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.9. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_vGImageLabel_t {
    QByteArrayData data[1];
    char stringdata0[13];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_vGImageLabel_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_vGImageLabel_t qt_meta_stringdata_vGImageLabel = {
    {
QT_MOC_LITERAL(0, 0, 12) // "vGImageLabel"

    },
    "vGImageLabel"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_vGImageLabel[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

void vGImageLabel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObject vGImageLabel::staticMetaObject = {
    { &QLabel::staticMetaObject, qt_meta_stringdata_vGImageLabel.data,
      qt_meta_data_vGImageLabel,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *vGImageLabel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *vGImageLabel::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_vGImageLabel.stringdata0))
        return static_cast<void*>(this);
    return QLabel::qt_metacast(_clname);
}

int vGImageLabel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QLabel::qt_metacall(_c, _id, _a);
    return _id;
}
struct qt_meta_stringdata_vGMenuBase_t {
    QByteArrayData data[19];
    char stringdata0[199];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_vGMenuBase_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_vGMenuBase_t qt_meta_stringdata_vGMenuBase = {
    {
QT_MOC_LITERAL(0, 0, 10), // "vGMenuBase"
QT_MOC_LITERAL(1, 11, 11), // "update_skin"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 13), // "ReleaseWindow"
QT_MOC_LITERAL(4, 38, 13), // "vGAppWidBase*"
QT_MOC_LITERAL(5, 52, 7), // "_object"
QT_MOC_LITERAL(6, 60, 12), // "LaunchWidget"
QT_MOC_LITERAL(7, 73, 10), // "UpdateSkin"
QT_MOC_LITERAL(8, 84, 12), // "UpdateLayout"
QT_MOC_LITERAL(9, 97, 6), // "Action"
QT_MOC_LITERAL(10, 104, 7), // "_action"
QT_MOC_LITERAL(11, 112, 9), // "_new_size"
QT_MOC_LITERAL(12, 122, 11), // "setDuration"
QT_MOC_LITERAL(13, 134, 3), // "_ms"
QT_MOC_LITERAL(14, 138, 14), // "setEasingCurve"
QT_MOC_LITERAL(15, 153, 18), // "QEasingCurve::Type"
QT_MOC_LITERAL(16, 172, 5), // "_type"
QT_MOC_LITERAL(17, 178, 10), // "allOpacity"
QT_MOC_LITERAL(18, 189, 9) // "ebOpacity"

    },
    "vGMenuBase\0update_skin\0\0ReleaseWindow\0"
    "vGAppWidBase*\0_object\0LaunchWidget\0"
    "UpdateSkin\0UpdateLayout\0Action\0_action\0"
    "_new_size\0setDuration\0_ms\0setEasingCurve\0"
    "QEasingCurve::Type\0_type\0allOpacity\0"
    "ebOpacity"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_vGMenuBase[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       2,   76, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   54,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    1,   55,    2, 0x0a /* Public */,
       6,    1,   58,    2, 0x0a /* Public */,
       7,    0,   61,    2, 0x0a /* Public */,
       8,    2,   62,    2, 0x0a /* Public */,
       8,    1,   67,    2, 0x2a /* Public | MethodCloned */,
      12,    1,   70,    2, 0x0a /* Public */,
      14,    1,   73,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 4,    5,
    QMetaType::Void, 0x80000000 | 4,    5,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 9, QMetaType::QSize,   10,   11,
    QMetaType::Void, 0x80000000 | 9,   10,
    QMetaType::Void, QMetaType::UShort,   13,
    QMetaType::Void, 0x80000000 | 15,   16,

 // properties: name, type, flags
      17, QMetaType::QReal, 0x00095103,
      18, QMetaType::QReal, 0x00095103,

       0        // eod
};

void vGMenuBase::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        vGMenuBase *_t = static_cast<vGMenuBase *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->update_skin(); break;
        case 1: _t->ReleaseWindow((*reinterpret_cast< vGAppWidBase*(*)>(_a[1]))); break;
        case 2: _t->LaunchWidget((*reinterpret_cast< vGAppWidBase*(*)>(_a[1]))); break;
        case 3: _t->UpdateSkin(); break;
        case 4: _t->UpdateLayout((*reinterpret_cast< Action(*)>(_a[1])),(*reinterpret_cast< QSize(*)>(_a[2]))); break;
        case 5: _t->UpdateLayout((*reinterpret_cast< Action(*)>(_a[1]))); break;
        case 6: _t->setDuration((*reinterpret_cast< quint16(*)>(_a[1]))); break;
        case 7: _t->setEasingCurve((*reinterpret_cast< QEasingCurve::Type(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< vGAppWidBase* >(); break;
            }
            break;
        case 2:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< vGAppWidBase* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (vGMenuBase::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&vGMenuBase::update_skin)) {
                *result = 0;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        vGMenuBase *_t = static_cast<vGMenuBase *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< qreal*>(_v) = _t->allOpacity(); break;
        case 1: *reinterpret_cast< qreal*>(_v) = _t->ebOpacity(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        vGMenuBase *_t = static_cast<vGMenuBase *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setAllOpacity(*reinterpret_cast< qreal*>(_v)); break;
        case 1: _t->setEbOpacity(*reinterpret_cast< qreal*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

const QMetaObject vGMenuBase::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_vGMenuBase.data,
      qt_meta_data_vGMenuBase,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *vGMenuBase::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *vGMenuBase::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_vGMenuBase.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int vGMenuBase::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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
#ifndef QT_NO_PROPERTIES
   else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 2;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void vGMenuBase::update_skin()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
struct qt_meta_stringdata_vGAppWidBase_t {
    QByteArrayData data[7];
    char stringdata0[65];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_vGAppWidBase_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_vGAppWidBase_t qt_meta_stringdata_vGAppWidBase = {
    {
QT_MOC_LITERAL(0, 0, 12), // "vGAppWidBase"
QT_MOC_LITERAL(1, 13, 8), // "CloseApp"
QT_MOC_LITERAL(2, 22, 0), // ""
QT_MOC_LITERAL(3, 23, 13), // "vGAppWidBase*"
QT_MOC_LITERAL(4, 37, 4), // "_app"
QT_MOC_LITERAL(5, 42, 11), // "update_skin"
QT_MOC_LITERAL(6, 54, 10) // "UpdateSkin"

    },
    "vGAppWidBase\0CloseApp\0\0vGAppWidBase*\0"
    "_app\0update_skin\0UpdateSkin"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_vGAppWidBase[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   29,    2, 0x06 /* Public */,
       5,    0,   32,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    0,   33,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void vGAppWidBase::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        vGAppWidBase *_t = static_cast<vGAppWidBase *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->CloseApp((*reinterpret_cast< vGAppWidBase*(*)>(_a[1]))); break;
        case 1: _t->update_skin(); break;
        case 2: _t->UpdateSkin(); break;
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
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (vGAppWidBase::*_t)(vGAppWidBase * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&vGAppWidBase::CloseApp)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (vGAppWidBase::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&vGAppWidBase::update_skin)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject vGAppWidBase::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_vGAppWidBase.data,
      qt_meta_data_vGAppWidBase,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *vGAppWidBase::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *vGAppWidBase::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_vGAppWidBase.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int vGAppWidBase::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void vGAppWidBase::CloseApp(vGAppWidBase * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void vGAppWidBase::update_skin()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}
struct qt_meta_stringdata_vGApp_t {
    QByteArrayData data[1];
    char stringdata0[6];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_vGApp_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_vGApp_t qt_meta_stringdata_vGApp = {
    {
QT_MOC_LITERAL(0, 0, 5) // "vGApp"

    },
    "vGApp"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_vGApp[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

void vGApp::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObject vGApp::staticMetaObject = {
    { &QApplication::staticMetaObject, qt_meta_stringdata_vGApp.data,
      qt_meta_data_vGApp,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *vGApp::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *vGApp::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_vGApp.stringdata0))
        return static_cast<void*>(this);
    return QApplication::qt_metacast(_clname);
}

int vGApp::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QApplication::qt_metacall(_c, _id, _a);
    return _id;
}
struct qt_meta_stringdata_vGMessageBox_t {
    QByteArrayData data[13];
    char stringdata0[94];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_vGMessageBox_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_vGMessageBox_t qt_meta_stringdata_vGMessageBox = {
    {
QT_MOC_LITERAL(0, 0, 12), // "vGMessageBox"
QT_MOC_LITERAL(1, 13, 14), // "close_ac_start"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 6), // "resize"
QT_MOC_LITERAL(4, 36, 4), // "_new"
QT_MOC_LITERAL(5, 41, 7), // "setText"
QT_MOC_LITERAL(6, 49, 5), // "_text"
QT_MOC_LITERAL(7, 55, 7), // "setFont"
QT_MOC_LITERAL(8, 63, 5), // "_font"
QT_MOC_LITERAL(9, 69, 7), // "setTime"
QT_MOC_LITERAL(10, 77, 5), // "_time"
QT_MOC_LITERAL(11, 83, 4), // "show"
QT_MOC_LITERAL(12, 88, 5) // "close"

    },
    "vGMessageBox\0close_ac_start\0\0resize\0"
    "_new\0setText\0_text\0setFont\0_font\0"
    "setTime\0_time\0show\0close"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_vGMessageBox[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   49,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    1,   50,    2, 0x0a /* Public */,
       5,    1,   53,    2, 0x0a /* Public */,
       7,    1,   56,    2, 0x0a /* Public */,
       9,    1,   59,    2, 0x0a /* Public */,
      11,    0,   62,    2, 0x0a /* Public */,
      12,    0,   63,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::QSize,    4,
    QMetaType::Void, QMetaType::QString,    6,
    QMetaType::Void, QMetaType::QFont,    8,
    QMetaType::Void, QMetaType::UShort,   10,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void vGMessageBox::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        vGMessageBox *_t = static_cast<vGMessageBox *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->close_ac_start(); break;
        case 1: _t->resize((*reinterpret_cast< QSize(*)>(_a[1]))); break;
        case 2: _t->setText((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: _t->setFont((*reinterpret_cast< const QFont(*)>(_a[1]))); break;
        case 4: _t->setTime((*reinterpret_cast< const quint16(*)>(_a[1]))); break;
        case 5: _t->show(); break;
        case 6: _t->close(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (vGMessageBox::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&vGMessageBox::close_ac_start)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject vGMessageBox::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_vGMessageBox.data,
      qt_meta_data_vGMessageBox,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *vGMessageBox::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *vGMessageBox::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_vGMessageBox.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int vGMessageBox::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void vGMessageBox::close_ac_start()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE

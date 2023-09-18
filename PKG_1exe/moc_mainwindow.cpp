/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[19];
    char stringdata0[352];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 22), // "on_RGBScrollBarChanged"
QT_MOC_LITERAL(2, 34, 0), // ""
QT_MOC_LITERAL(3, 35, 23), // "on_CMYKScrollBarChanged"
QT_MOC_LITERAL(4, 59, 22), // "on_XYZScrollBarChanged"
QT_MOC_LITERAL(5, 82, 22), // "on_LABScrollBarChanged"
QT_MOC_LITERAL(6, 105, 22), // "on_HSVScrollBarChanged"
QT_MOC_LITERAL(7, 128, 22), // "on_HSLScrollBarChanged"
QT_MOC_LITERAL(8, 151, 18), // "LineEditRGBChanged"
QT_MOC_LITERAL(9, 170, 3), // "str"
QT_MOC_LITERAL(10, 174, 18), // "LineEditXYZChanged"
QT_MOC_LITERAL(11, 193, 19), // "LineEditCMYKChanged"
QT_MOC_LITERAL(12, 213, 18), // "LineEditLABChanged"
QT_MOC_LITERAL(13, 232, 18), // "LineEditHSVChanged"
QT_MOC_LITERAL(14, 251, 18), // "LineEditHSLChanged"
QT_MOC_LITERAL(15, 270, 23), // "on_lineEdit_textChanged"
QT_MOC_LITERAL(16, 294, 4), // "arg1"
QT_MOC_LITERAL(17, 299, 21), // "on_pushButton_clicked"
QT_MOC_LITERAL(18, 321, 30) // "on_comboBox_currentTextChanged"

    },
    "MainWindow\0on_RGBScrollBarChanged\0\0"
    "on_CMYKScrollBarChanged\0on_XYZScrollBarChanged\0"
    "on_LABScrollBarChanged\0on_HSVScrollBarChanged\0"
    "on_HSLScrollBarChanged\0LineEditRGBChanged\0"
    "str\0LineEditXYZChanged\0LineEditCMYKChanged\0"
    "LineEditLABChanged\0LineEditHSVChanged\0"
    "LineEditHSLChanged\0on_lineEdit_textChanged\0"
    "arg1\0on_pushButton_clicked\0"
    "on_comboBox_currentTextChanged"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      15,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   89,    2, 0x08 /* Private */,
       3,    1,   92,    2, 0x08 /* Private */,
       4,    1,   95,    2, 0x08 /* Private */,
       5,    1,   98,    2, 0x08 /* Private */,
       6,    1,  101,    2, 0x08 /* Private */,
       7,    1,  104,    2, 0x08 /* Private */,
       8,    1,  107,    2, 0x08 /* Private */,
      10,    1,  110,    2, 0x08 /* Private */,
      11,    1,  113,    2, 0x08 /* Private */,
      12,    1,  116,    2, 0x08 /* Private */,
      13,    1,  119,    2, 0x08 /* Private */,
      14,    1,  122,    2, 0x08 /* Private */,
      15,    1,  125,    2, 0x08 /* Private */,
      17,    0,  128,    2, 0x08 /* Private */,
      18,    1,  129,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::QString,    9,
    QMetaType::Void, QMetaType::QString,    9,
    QMetaType::Void, QMetaType::QString,    9,
    QMetaType::Void, QMetaType::QString,    9,
    QMetaType::Void, QMetaType::QString,    9,
    QMetaType::Void, QMetaType::QString,    9,
    QMetaType::Void, QMetaType::QString,   16,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   16,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_RGBScrollBarChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->on_CMYKScrollBarChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->on_XYZScrollBarChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->on_LABScrollBarChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->on_HSVScrollBarChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->on_HSLScrollBarChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->LineEditRGBChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 7: _t->LineEditXYZChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 8: _t->LineEditCMYKChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 9: _t->LineEditLABChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 10: _t->LineEditHSVChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 11: _t->LineEditHSLChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 12: _t->on_lineEdit_textChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 13: _t->on_pushButton_clicked(); break;
        case 14: _t->on_comboBox_currentTextChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MainWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_MainWindow.data,
    qt_meta_data_MainWindow,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 15)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 15;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 15)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 15;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE

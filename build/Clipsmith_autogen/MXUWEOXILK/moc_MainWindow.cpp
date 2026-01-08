/****************************************************************************
** Meta object code from reading C++ file 'MainWindow.hpp'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.4.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../src/gui/MainWindow.hpp"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MainWindow.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.4.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
namespace {
struct qt_meta_stringdata_MainWindow_t {
    uint offsetsAndSizes[40];
    char stringdata0[11];
    char stringdata1[13];
    char stringdata2[1];
    char stringdata3[5];
    char stringdata4[20];
    char stringdata5[34];
    char stringdata6[7];
    char stringdata7[16];
    char stringdata8[20];
    char stringdata9[17];
    char stringdata10[5];
    char stringdata11[19];
    char stringdata12[15];
    char stringdata13[19];
    char stringdata14[16];
    char stringdata15[15];
    char stringdata16[17];
    char stringdata17[12];
    char stringdata18[11];
    char stringdata19[8];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_MainWindow_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
        QT_MOC_LITERAL(0, 10),  // "MainWindow"
        QT_MOC_LITERAL(11, 12),  // "onNewContent"
        QT_MOC_LITERAL(24, 0),  // ""
        QT_MOC_LITERAL(25, 4),  // "text"
        QT_MOC_LITERAL(30, 19),  // "onTrayIconActivated"
        QT_MOC_LITERAL(50, 33),  // "QSystemTrayIcon::ActivationRe..."
        QT_MOC_LITERAL(84, 6),  // "reason"
        QT_MOC_LITERAL(91, 15),  // "onSearchChanged"
        QT_MOC_LITERAL(107, 19),  // "onItemDoubleClicked"
        QT_MOC_LITERAL(127, 16),  // "QListWidgetItem*"
        QT_MOC_LITERAL(144, 4),  // "item"
        QT_MOC_LITERAL(149, 18),  // "onSelectionChanged"
        QT_MOC_LITERAL(168, 14),  // "actionPrettify"
        QT_MOC_LITERAL(183, 18),  // "actionBase64Decode"
        QT_MOC_LITERAL(202, 15),  // "actionCleanText"
        QT_MOC_LITERAL(218, 14),  // "actionCopyItem"
        QT_MOC_LITERAL(233, 16),  // "actionDeleteItem"
        QT_MOC_LITERAL(250, 11),  // "refreshList"
        QT_MOC_LITERAL(262, 10),  // "showWindow"
        QT_MOC_LITERAL(273, 7)   // "quitApp"
    },
    "MainWindow",
    "onNewContent",
    "",
    "text",
    "onTrayIconActivated",
    "QSystemTrayIcon::ActivationReason",
    "reason",
    "onSearchChanged",
    "onItemDoubleClicked",
    "QListWidgetItem*",
    "item",
    "onSelectionChanged",
    "actionPrettify",
    "actionBase64Decode",
    "actionCleanText",
    "actionCopyItem",
    "actionDeleteItem",
    "refreshList",
    "showWindow",
    "quitApp"
};
#undef QT_MOC_LITERAL
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_MainWindow[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   92,    2, 0x08,    1 /* Private */,
       4,    1,   95,    2, 0x08,    3 /* Private */,
       7,    1,   98,    2, 0x08,    5 /* Private */,
       8,    1,  101,    2, 0x08,    7 /* Private */,
      11,    0,  104,    2, 0x08,    9 /* Private */,
      12,    0,  105,    2, 0x08,   10 /* Private */,
      13,    0,  106,    2, 0x08,   11 /* Private */,
      14,    0,  107,    2, 0x08,   12 /* Private */,
      15,    0,  108,    2, 0x08,   13 /* Private */,
      16,    0,  109,    2, 0x08,   14 /* Private */,
      17,    0,  110,    2, 0x08,   15 /* Private */,
      18,    0,  111,    2, 0x08,   16 /* Private */,
      19,    0,  112,    2, 0x08,   17 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, 0x80000000 | 5,    6,
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, 0x80000000 | 9,   10,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject MainWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_MainWindow.offsetsAndSizes,
    qt_meta_data_MainWindow,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_MainWindow_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<MainWindow, std::true_type>,
        // method 'onNewContent'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'onTrayIconActivated'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QSystemTrayIcon::ActivationReason, std::false_type>,
        // method 'onSearchChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'onItemDoubleClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QListWidgetItem *, std::false_type>,
        // method 'onSelectionChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'actionPrettify'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'actionBase64Decode'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'actionCleanText'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'actionCopyItem'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'actionDeleteItem'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'refreshList'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'showWindow'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'quitApp'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->onNewContent((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 1: _t->onTrayIconActivated((*reinterpret_cast< std::add_pointer_t<QSystemTrayIcon::ActivationReason>>(_a[1]))); break;
        case 2: _t->onSearchChanged((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 3: _t->onItemDoubleClicked((*reinterpret_cast< std::add_pointer_t<QListWidgetItem*>>(_a[1]))); break;
        case 4: _t->onSelectionChanged(); break;
        case 5: _t->actionPrettify(); break;
        case 6: _t->actionBase64Decode(); break;
        case 7: _t->actionCleanText(); break;
        case 8: _t->actionCopyItem(); break;
        case 9: _t->actionDeleteItem(); break;
        case 10: _t->refreshList(); break;
        case 11: _t->showWindow(); break;
        case 12: _t->quitApp(); break;
        default: ;
        }
    }
}

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
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 13;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE

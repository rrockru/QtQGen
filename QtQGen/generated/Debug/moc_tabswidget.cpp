/****************************************************************************
** Meta object code from reading C++ file 'tabswidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.0.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "StdAfx.h"
#include "..\..\src\tabswidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'tabswidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.0.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Ui__TabsWidget_t {
    QByteArrayData data[3];
    char stringdata[28];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_Ui__TabsWidget_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_Ui__TabsWidget_t qt_meta_stringdata_Ui__TabsWidget = {
    {
QT_MOC_LITERAL(0, 0, 14),
QT_MOC_LITERAL(1, 15, 10),
QT_MOC_LITERAL(2, 26, 0)
    },
    "Ui::TabsWidget\0OnCloseTab\0\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Ui__TabsWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   19,    2, 0x08,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    2,

       0        // eod
};

void Ui::TabsWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        TabsWidget *_t = static_cast<TabsWidget *>(_o);
        switch (_id) {
        case 0: _t->OnCloseTab((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject Ui::TabsWidget::staticMetaObject = {
    { &QTabWidget::staticMetaObject, qt_meta_stringdata_Ui__TabsWidget.data,
      qt_meta_data_Ui__TabsWidget,  qt_static_metacall, 0, 0}
};


const QMetaObject *Ui::TabsWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Ui::TabsWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Ui__TabsWidget.stringdata))
        return static_cast<void*>(const_cast< TabsWidget*>(this));
    return QTabWidget::qt_metacast(_clname);
}

int Ui::TabsWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTabWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 1;
    }
    return _id;
}
QT_END_MOC_NAMESPACE

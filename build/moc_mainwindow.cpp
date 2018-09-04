/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../include/mainwindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MainWindow[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      41,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      18,   12,   11,   11, 0x0a,
      50,   12,   11,   11, 0x0a,
      89,   12,   11,   11, 0x0a,
     124,   12,   11,   11, 0x0a,
     161,   12,   11,   11, 0x0a,
     193,   12,   11,   11, 0x0a,
     226,   12,   11,   11, 0x0a,
     256,   12,   11,   11, 0x0a,
     287,   12,   11,   11, 0x0a,
     318,   12,   11,   11, 0x0a,
     348,   12,   11,   11, 0x0a,
     385,   12,   11,   11, 0x0a,
     419,   12,   11,   11, 0x0a,
     452,   12,   11,   11, 0x0a,
     487,   12,   11,   11, 0x0a,
     517,   11,   11,   11, 0x0a,
     530,   11,   11,   11, 0x0a,
     549,   11,   11,   11, 0x08,
     581,   11,   11,   11, 0x08,
     613,   11,   11,   11, 0x08,
     647,   11,   11,   11, 0x08,
     674,   11,   11,   11, 0x08,
     704,   11,   11,   11, 0x08,
     733,   11,   11,   11, 0x08,
     762,   11,   11,   11, 0x08,
     796,   11,   11,   11, 0x08,
     828,   11,   11,   11, 0x08,
     852,   11,   11,   11, 0x08,
     881,   11,   11,   11, 0x08,
     914,  909,   11,   11, 0x08,
     953,   11,   11,   11, 0x08,
    1000,   11,   11,   11, 0x08,
    1041,   11,   11,   11, 0x08,
    1082,   11,   11,   11, 0x08,
    1131,   11,   11,   11, 0x08,
    1180, 1174,   11,   11, 0x08,
    1213,   11,   11,   11, 0x08,
    1235,   11,   11,   11, 0x08,
    1258,   11,   11,   11, 0x08,
    1280,   11,   11,   11, 0x08,
    1295,   11,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_MainWindow[] = {
    "MainWindow\0\0value\0slot_slider_MinDisparitySG(int)\0"
    "slot_slider_NumberOfDisparitiesSG(int)\0"
    "slot_slider_UniquenessRatioSG(int)\0"
    "slot_slider_SpeckleWindowSizeSG(int)\0"
    "slot_slider_SpeckleRangeSG(int)\0"
    "slot_slider_SADWindowSizeSG(int)\0"
    "slot_slider_PreFilterCap(int)\0"
    "slot_slider_PreFilterSize(int)\0"
    "slot_slider_SADWindowSize(int)\0"
    "slot_slider_MinDisparity(int)\0"
    "slot_slider_NumberOfDisparities(int)\0"
    "slot_slider_TextureThreshold(int)\0"
    "slot_slider_UniquenessRatio(int)\0"
    "slot_slider_SpeckleWindowSize(int)\0"
    "slot_slider_SpeckleRange(int)\0"
    "slot_reset()\0slot_auto_update()\0"
    "on_BackgroundCheckBox_clicked()\0"
    "on_ShowCameraCheckBox_clicked()\0"
    "on_FollowCameraCheckBox_clicked()\0"
    "on_AddPoseButton_clicked()\0"
    "on_DeletePoseButton_clicked()\0"
    "on_ShowPosesButton_clicked()\0"
    "on_SaveVideoButton_clicked()\0"
    "on_LocalImageModeButton_clicked()\0"
    "on_RealTimeModeButton_clicked()\0"
    "on_ExitButton_clicked()\0"
    "on_ResetViewButton_clicked()\0"
    "on_RecordCheckBox_clicked()\0arg1\0"
    "on_DisparityModeBox_activated(QString)\0"
    "on_Slider_NumberOfDisparities_sliderReleased()\0"
    "on_Slider_PreFilterSize_sliderReleased()\0"
    "on_Slider_SADWindowSize_sliderReleased()\0"
    "on_Slider_NumberOfDisparitiesSG_sliderReleased()\0"
    "on_Slider_SADWindowSizeSG_sliderReleased()\0"
    "index\0on_tabWidget_currentChanged(int)\0"
    "DetectNewCalibParam()\0DetectNewStereoImage()\0"
    "DetectNewCameraPose()\0DetectNewMap()\0"
    "DetectNewCamImage()\0"
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        MainWindow *_t = static_cast<MainWindow *>(_o);
        switch (_id) {
        case 0: _t->slot_slider_MinDisparitySG((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->slot_slider_NumberOfDisparitiesSG((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->slot_slider_UniquenessRatioSG((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->slot_slider_SpeckleWindowSizeSG((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->slot_slider_SpeckleRangeSG((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->slot_slider_SADWindowSizeSG((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->slot_slider_PreFilterCap((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->slot_slider_PreFilterSize((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->slot_slider_SADWindowSize((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: _t->slot_slider_MinDisparity((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 10: _t->slot_slider_NumberOfDisparities((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 11: _t->slot_slider_TextureThreshold((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 12: _t->slot_slider_UniquenessRatio((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 13: _t->slot_slider_SpeckleWindowSize((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 14: _t->slot_slider_SpeckleRange((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 15: _t->slot_reset(); break;
        case 16: _t->slot_auto_update(); break;
        case 17: _t->on_BackgroundCheckBox_clicked(); break;
        case 18: _t->on_ShowCameraCheckBox_clicked(); break;
        case 19: _t->on_FollowCameraCheckBox_clicked(); break;
        case 20: _t->on_AddPoseButton_clicked(); break;
        case 21: _t->on_DeletePoseButton_clicked(); break;
        case 22: _t->on_ShowPosesButton_clicked(); break;
        case 23: _t->on_SaveVideoButton_clicked(); break;
        case 24: _t->on_LocalImageModeButton_clicked(); break;
        case 25: _t->on_RealTimeModeButton_clicked(); break;
        case 26: _t->on_ExitButton_clicked(); break;
        case 27: _t->on_ResetViewButton_clicked(); break;
        case 28: _t->on_RecordCheckBox_clicked(); break;
        case 29: _t->on_DisparityModeBox_activated((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 30: _t->on_Slider_NumberOfDisparities_sliderReleased(); break;
        case 31: _t->on_Slider_PreFilterSize_sliderReleased(); break;
        case 32: _t->on_Slider_SADWindowSize_sliderReleased(); break;
        case 33: _t->on_Slider_NumberOfDisparitiesSG_sliderReleased(); break;
        case 34: _t->on_Slider_SADWindowSizeSG_sliderReleased(); break;
        case 35: _t->on_tabWidget_currentChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 36: _t->DetectNewCalibParam(); break;
        case 37: _t->DetectNewStereoImage(); break;
        case 38: _t->DetectNewCameraPose(); break;
        case 39: _t->DetectNewMap(); break;
        case 40: _t->DetectNewCamImage(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData MainWindow::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow,
      qt_meta_data_MainWindow, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MainWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 41)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 41;
    }
    return _id;
}
QT_END_MOC_NAMESPACE

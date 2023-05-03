#ifndef VGTIME_H
#define VGTIME_H

#include "vGTime_global.h"
#include <QWidget>
#include <QTimer>

namespace Ui {
class vGTime;
}

class vGTime : public vGAppWidBase
{
    using Parent = vGAppWidBase;
    Q_OBJECT

public:
    explicit vGTime(vGMenuBase *parent,vGPlugin*);
    ~vGTime();
    
    static QByteArray GetSvg();
public slots:
    //更新时间
    void update_time();
    //更新大小
    //输入当前窗口大小，自适应更改
    void update_size(QSize _size);
    virtual void UpdateSkin();

protected:
    void timerEvent(QTimerEvent* event);
    void resizeEvent(QResizeEvent* event);
private:
    int timer_id_;
    Ui::vGTime *ui;
};

class FrGTime : public FrPluginWidgetPr
{
    using Parent = FrPluginWidgetPr;
    Q_OBJECT

public:
    explicit FrGTime(vGMenuBase* parent, FrPluginPr*);
    ~FrGTime();

    static QByteArray GetSvg();
public slots:
    //更新时间
    void update_time();
    //更新大小
    //输入当前窗口大小，自适应更改
    void update_size(QSize _size);
    virtual void UpdateSkins();

protected:
    void timerEvent(QTimerEvent* event);
    void resizeEvent(QResizeEvent* event);
private:
    int timer_id_;
    Ui::vGTime* ui;
};

class FrTime :public FrPluginPr {
public:
    void initialize();
    //详情看父类
    void create();

};

class FrTimeApp :public FrPlugin {
    Q_OBJECT
public:
    FrTimeApp();
    ~FrTimeApp();
    bool initialize();
    bool event(QEvent* _e);
    
};
class FrTimeWidget :public FrPluginWidget {
    Q_OBJECT
public:
    FrTimeWidget(vGMenuBase* _menu, FrPlugin* _plugin);
    void keyPressEvent(QKeyEvent* event);
};


#endif // VGTIME_H

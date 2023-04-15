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

#endif // VGTIME_H

#ifndef VGSETTING_H
#define VGSETTING_H

#include "vGSetting_global.h"
#include "vghead.hpp"
#include "FrPlugin.hpp"
namespace Ui {
class vGSetting;
}

class vGSetting : public vGAppWidBase
{
    Q_OBJECT

public:
    explicit vGSetting(vGMenuBase*parent,vGPlugin*);
    ~vGSetting();
    static QByteArray GetSvg();
public slots:
    void UpdateSkin()override;
private:
    Ui::vGSetting *ui;
};
//:/core/icon

class FrSettingApp :public FrPlugin {
    Q_OBJECT
public:
    FrSettingApp();
    ~FrSettingApp();
    bool initialize();
    bool event(QEvent* _e);

};
class FrSettingWidget :public FrPluginWidget {
    Q_OBJECT
public:
    FrSettingWidget(vGMenuBase* _menu, FrPlugin* _plugin);

protected:
    void keyPressEvent(QKeyEvent* event);
};


#endif // VGSETTING_H

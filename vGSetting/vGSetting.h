#ifndef VGSETTING_H
#define VGSETTING_H

#include "vGSetting_global.h"

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
#endif // VGSETTING_H

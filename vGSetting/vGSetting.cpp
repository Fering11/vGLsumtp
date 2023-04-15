#include "vGSetting.h"
#include "ui_vGSetting.h"
#define qctr(s)  (QCoreApplication::tr(s))
VGSETTING_EXPORT vGAppWidBase* get_object(vGMenuBase* _parent,vGPlugin*_plugin) {
    Q_INIT_RESOURCE(vGSetting);
    return reinterpret_cast<vGAppWidBase*>(new vGSetting(_parent, _plugin));
}
//一般不会显式删除
VGSETTING_EXPORT void destory_object(vGAppWidBase* _app) {
    delete reinterpret_cast<vGSetting*>(_app);
}
VGSETTING_EXPORT void get_info(vGPluginInfo* _info) {
    _info->package = "app.setting.sys";
    _info->app_name = qctr("Setting");
    _info->version = QU8("0.0.1");
    _info->description = qctr("Provide System Setting");
    (_info->logo) = Svg2Pixmap(vGSetting::GetSvg(), vGp->Config().base().win_size());
}
vGSetting::vGSetting(vGMenuBase*parent, vGPlugin* _plugin) :
    vGAppWidBase(parent, _plugin),
    ui(new Ui::vGSetting)
{
    ui->setupUi(this);
    this->setObjectName("vGSetting");
    connect(ui->btn,&QPushButton::pressed,this,[this](){
    QMessageBox::information(this,"hello ","vGSetting exit");
    this->close();
    });

}

vGSetting::~vGSetting()
{
    delete ui;
}

QByteArray vGSetting::GetSvg()
{
    QFile file(QU8(":/icon/icon_1")); //TODO 重载获取logo函数
    file.open(QIODevice::ReadOnly);
    auto xml_data = file.readAll();
    if (!xml_data.isEmpty()) {
        QDomDocument doc;
        doc.setContent(xml_data);
        auto svg_elem = doc.documentElement();
        if (!svg_elem.isNull()) {
            //设置颜色与主题颜色一致
            SetAllTag(svg_elem, "path", "fill", vGp->Skin().menu.logo.name());
            return doc.toByteArray();
        }
    }
    return xml_data; //data or null
}

void vGSetting::UpdateSkin(){
    //更新一下图片颜色
    
    this->_info()->logo = Svg2Pixmap(GetSvg(), vGp->Config().base().win_size());
    vGAppWidBase::UpdateSkin();
}
#include "vGSetting.h"
#include "ui_vGSetting.h"
#define qctr(s)  (QCoreApplication::tr(s))


bool GetProperty(FrPluginProperty* _property) {
    if (_property) {
        _property->description = "Provide System Setting";
        _property->name = "Setting";
        _property->package = "app.setting.app";
        _property->version = "0.0.1";
        _property->logo = Svg2Pixmap(vGSetting::GetSvg(), vGp->Config().base().win_size());
        return true;
    }
    else {
        vGlog->warn("vGTime GetProperty is not allow nullptr");
    }
    return false;
}

FrPlugin* GetInstance() {
    FrSettingApp* result = new FrSettingApp();
    return result;
}


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
//###############################
FrSettingApp::FrSettingApp():
    FrPlugin()
{
    vGlog->info("FrSettingApp constructed");
}

FrSettingApp::~FrSettingApp()
{
    vGlog->info("FrSettingApp destrcuted");

}

bool FrSettingApp::initialize(){
    widget_ = new FrSettingWidget(vGp->menu(), this);
    vGlog->info("FrSettingApp start");
    return false;
}

bool FrSettingApp::event(QEvent* _e)
{
    vGlog->info("FrSettingApp Event:{}", _e->type());
    return FrPlugin::event(_e);
}

FrSettingWidget::FrSettingWidget(vGMenuBase* _menu, FrPlugin* _plugin):
    FrPluginWidget(_menu,_plugin){
    QPushButton* btn = new QPushButton(this);
    btn->setGeometry(50, 50, 150, 200);
    btn->setText("Setting!");
    connect(btn, &QPushButton::pressed, this, [this]() {
        vGp->postEvent(plugin(), new QEvent(QEvent::Enter));
        });
}

void FrSettingWidget::keyPressEvent(QKeyEvent* event){
    switch (event->key())
    {
    case Qt::Key_Escape: {
        //返回
        this->hide();
        break;
    }
    default:
        break;
    }

}

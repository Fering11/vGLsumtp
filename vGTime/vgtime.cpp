#include "vgtime.h"
#include "ui_vgtime.h"

//全局FrTime实例
FrTime _g_ex_frtime;

FrPlugin* GetInstance() {
    return reinterpret_cast<FrPlugin*>(std::addressof(_g_ex_frtime));
}

#define qctr (QCoreApplication::tr)


vGTime::vGTime(vGMenuBase*parent,vGPlugin* _pl) :
    vGAppWidBase(parent,_pl),
    ui(new Ui::vGTime)
{
    ui->setupUi(this);

    this->setObjectName("vGTime");
    
    //启动计时器
    timer_id_ = startTimer(1000);
}

vGTime::~vGTime()
{
    delete ui;
}
QByteArray vGTime::GetSvg()
{
    QFile file(QU8(":/core/icon")); //TODO 重载获取logo函数
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
void vGTime::update_size(QSize _size)
{
    QFont font;
    font.setPointSize(_size.width() / 6);
    ui->lab_time->setFont(font);
    font.setPointSize(_size.width() / 8);
    ui->lab_date->setFont(font);
}
void vGTime::UpdateSkin()
{
    _info()->logo = Svg2Pixmap(vGTime::GetSvg(), vGp->Config().base().win_size());
    Parent::UpdateSkin();
}
void vGTime::timerEvent(QTimerEvent* _event)
{
    if (_event->timerId() == timer_id_) {
        update_time();
    } else {
        Parent::timerEvent(_event);
    }
}
void vGTime::resizeEvent(QResizeEvent* event)
{
    update_size(event->size());
}
void vGTime::update_time() {
    auto dt = QDateTime::currentDateTime();
    ui->lab_time->setText(dt.toString("hh:mm:ss"));
    ui->lab_date->setText(dt.toString("yyyy/MM/dd"));
}
// vGAppWidBase * (*)(vGMenuBase*);
//_t = void (*)(vGAppWidBase*);
vGAppWidBase* get_object(vGMenuBase* _parent,vGPlugin* _pl) {
    Q_INIT_RESOURCE(vGTime);
    return reinterpret_cast<vGAppWidBase*>(new vGTime(_parent, _pl));
}
void destory_object(vGAppWidBase* _parent) {
    delete reinterpret_cast<vGAppWidBase*>(_parent);
}
void get_info(vGPluginInfo* _info) {
    _info->package = "app.clock.sys";
    _info->app_name = qctr("clock");
   _info->description = qctr("show now time");
   _info->version = qctr("1.0.0");
   _info->logo = Svg2Pixmap(vGTime::GetSvg(), vGp->Config().base().win_size());
}
// //////////////////////////
///
///
void FrTime::initialize(){
    package_ = "app.clock.sys";
    name_ = qctr("clock");
    description_ = qctr("show now time");
    version_ = "1.0.0";
    logo_ = Svg2Pixmap(vGTime::GetSvg(), vGp->Config().base().win_size());
}

void FrTime::release(){

}

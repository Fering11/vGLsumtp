#include "vgtime.h"
#include "ui_vgtime.h"

//全局FrTime实例
FrTime _g_ex_frtime;

bool GetProperty(FrPluginProperty* _property){
    if (_property) {
        _property->description = "Time Control";
        _property->name = "Time";
        _property->package = "www.time.app";
        _property->version = "0.0.1";
        return true;
    }
    else {
        vGlog->warn("vGTime GetProperty is not allow nullptr");
    }
    return false;
}

FrPlugin* GetInstance() {

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

void FrTime::create()
{
    widget_ = new FrGTime(vGp->menu(), this);
}

FrGTime::FrGTime(vGMenuBase* _parent, FrPluginPr* _p):
    Parent(_parent,_p){
    ui->setupUi(this);

    this->setObjectName("FrTime");

    //启动计时器
    timer_id_ = startTimer(500);
    update_time();
    vgTrace("{} constructed", __FUNCTION__);
}

FrGTime::~FrGTime(){
    vgTrace("{} destructed", __FUNCTION__);
    delete ui;
}

void FrGTime::update_size(QSize _size){
    QFont font;
    font.setPointSize(_size.width() / 6);
    ui->lab_time->setFont(font);
    font.setPointSize(_size.width() / 8);
    ui->lab_date->setFont(font);
}

void FrGTime::UpdateSkins(){
    logo() = Svg2Pixmap(vGTime::GetSvg(), vGp->Config().base().win_size());
    Parent::UpdateSkins();
}
void FrGTime::timerEvent(QTimerEvent* _event)
{
    if (_event->timerId() == timer_id_) {
        update_time();
    }
    else {
        Parent::timerEvent(_event);
    }
}
void FrGTime::resizeEvent(QResizeEvent* event)
{
    update_size(event->size());
}
void FrGTime::update_time() {
    auto dt = QDateTime::currentDateTime();
    ui->lab_time->setText(dt.toString("hh:mm:ss"));
    ui->lab_date->setText(dt.toString("yyyy/MM/dd"));
}